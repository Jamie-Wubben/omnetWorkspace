//=========================================================================
//  CSOCKETRTSCHEDULER.CC - part of
//
//                  OMNeT++/OMNEST
//           Discrete System Simulation in C++
//
//=========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 2005-2015 Andras Varga

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include "../headers/UDPsocketRTScheduler.h"

Register_Class(UDPsocketRTScheduler);

Register_GlobalConfigOption(CFGID_UDPSOCKETRTSCHEDULER_PORT, "socketrtscheduler-port", CFG_INT, "4242", "When cSocketRTScheduler is selected as scheduler class: the port number cSocketRTScheduler listens on.");

#define MAXLINE 1024

inline std::ostream& operator<<(std::ostream& out, const timeval& tv)
{
    return out << (unsigned long)tv.tv_sec << "s" << tv.tv_usec << "us";
}

//---

std::string UDPsocketRTScheduler::str() const
{
    return "socket RT scheduler";
}

void UDPsocketRTScheduler::startRun()
{
    if (initsocketlibonce() != 0)
        throw cRuntimeError("cSocketRTScheduler: Cannot initialize socket library");

    baseTime = opp_get_monotonic_clock_usecs();

    module = nullptr;
    notificationMsg = nullptr;
    recvBuffer = nullptr;
    recvBufferSize = 0;
    numBytesPtr = nullptr;

    port = getEnvir()->getConfig()->getAsInt(CFGID_UDPSOCKETRTSCHEDULER_PORT);
    setupListener();
}

void UDPsocketRTScheduler::setupListener()
{
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == INVALID_SOCKET)
        throw cRuntimeError("cSocketRTScheduler: cannot create socket");

    // Setting this option makes it possible to kill the sample and restart
    // it right away without having to change the port it is listening on.
    // Not using SO_REUSEADDR as per: https://stackoverflow.com/a/34812994
    // Correction: There is no SO_REUSEPORT on Windows, so SO_REUSEADDR it is.
    int enable = 1;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&enable, sizeof(int)) < 0)
        throw cRuntimeError("cSocketRTScheduler: cannot set socket option");

    sockaddr_in sinInterface;
    sinInterface.sin_family = AF_INET;
    sinInterface.sin_addr.s_addr = INADDR_ANY;
    sinInterface.sin_port = htons(port);
    if (bind(udpSocket, (sockaddr *)&sinInterface, sizeof(sockaddr_in)) == SOCKET_ERROR)
        throw cRuntimeError("cSocketRTScheduler: socket bind() failed");

    listen(udpSocket, SOMAXCONN);
}

void UDPsocketRTScheduler::endRun()
{
}

void UDPsocketRTScheduler::executionResumed()
{
    baseTime = opp_get_monotonic_clock_usecs();
    baseTime = baseTime - simTime().inUnit(SIMTIME_US);
}

void UDPsocketRTScheduler::setInterfaceModule(cModule *mod, cMessage *notifMsg, char *buf, int bufSize, int *nBytesPtr)
{
    if (module)
        throw cRuntimeError("cSocketRTScheduler: setInterfaceModule() already called");
    if (!mod || !notifMsg || !buf || !bufSize || !nBytesPtr)
        throw cRuntimeError("cSocketRTScheduler: setInterfaceModule(): arguments must be non-nullptr");

    module = mod;
    notificationMsg = notifMsg;
    recvBuffer = buf;
    recvBufferSize = bufSize;
    numBytesPtr = nBytesPtr;
    *numBytesPtr = 0;
}

bool UDPsocketRTScheduler::receiveWithTimeout(long usec)
{
    // prepare sets for select()
    fd_set readFDs, writeFDs, exceptFDs;
    FD_ZERO(&readFDs);
    FD_ZERO(&writeFDs);
    FD_ZERO(&exceptFDs);

    FD_SET(udpSocket, &readFDs);

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = usec;

    if (select(FD_SETSIZE, &readFDs, &writeFDs, &exceptFDs, &timeout) > 0) {
        // Something happened on one of the sockets defined by FD_SET() check which one
        if(FD_ISSET(udpSocket, &readFDs)){
            // something happend at the udpSocket
            struct sockaddr_in cliaddr;
            memset(&cliaddr, 0, sizeof(cliaddr));
            socklen_t len = sizeof(cliaddr);

            int nBytes = recvfrom(udpSocket, (char *)recvBuffer, recvBufferSize,MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);
            recvBuffer[nBytes] = '\0';

            //EV << "cSocketRTScheduler: received " << nBytes << " bytes\n";
            (*numBytesPtr) += nBytes;

            int64_t currentTime = opp_get_monotonic_clock_usecs();
            simtime_t eventTime(currentTime - baseTime, SIMTIME_US);
            ASSERT(eventTime >= simTime());
            notificationMsg->setArrival(module->getId(), -1, eventTime);
            getSimulation()->getFES()->insert(notificationMsg);
            return true;
        }
    }
    return false;
}

int UDPsocketRTScheduler::receiveUntil(int64_t targetTime)
{
    // if there's more than 200ms to wait, wait in 100ms chunks
    // in order to keep UI responsiveness by invoking getEnvir()->idle()
    int64_t currentTime = opp_get_monotonic_clock_usecs();
    while (targetTime - currentTime >= 200000)
    {
        if (receiveWithTimeout(100000))  // 100ms
            return 1;

        // update simtime before calling envir's idle()
        currentTime = opp_get_monotonic_clock_usecs();
        simtime_t eventTime(currentTime - baseTime, SIMTIME_US);
        ASSERT(eventTime >= simTime());
        sim->setSimTime(eventTime);
        if (getEnvir()->idle())
            return -1;
        currentTime = opp_get_monotonic_clock_usecs();
    }

    // difference is now at most 100ms, do it at once
    long remaining = targetTime - currentTime;
    if (remaining > 0)
        if (receiveWithTimeout(remaining))
            return 1;

    return 0;
}

cEvent *UDPsocketRTScheduler::guessNextEvent()
{
    return sim->getFES()->peekFirst();
}

cEvent *UDPsocketRTScheduler::takeNextEvent()
{
    // assert that we've been configured
    if (!module)
        throw cRuntimeError("cSocketRTScheduler: setInterfaceModule() not called: it must be called from a module's initialize() function");

    // calculate target time
    int64_t targetTime;
    cEvent *event = sim->getFES()->peekFirst();
    if (!event) {
        // if there are no events, wait until something comes from outside
        // TBD: obey simtimelimit, cpu-time-limit
        // This way targetTime will always be "as far in the future as possible", considering
        // how integer overflows work in conjunction with comparisons in C++ (in practice...)
        targetTime = opp_get_monotonic_clock_usecs() + INT64_MAX;
    }
    else {
        // use time of next event
        simtime_t eventSimtime = event->getArrivalTime();
        targetTime = baseTime + eventSimtime.inUnit(SIMTIME_US);
    }

    // if needed, wait until that time arrives
    int64_t currentTime = opp_get_monotonic_clock_usecs();
    if (targetTime > currentTime) {
        int status = receiveUntil(targetTime);
        if (status == -1)
            return nullptr;  // interrupted by user
        if (status == 1)
            event = sim->getFES()->peekFirst();  // received something
    }
    else {
        float lack = (currentTime - targetTime)/1000;
        if(lack > 50){
            EV_WARN << "Behind real time with: " << lack << " ms" << endl;
            std::cout << "Behind real time with: " << lack << " ms" << endl;
        }

        // we're behind -- customized versions of this class may
        // alert if we're too much behind, whatever that means
    }

    // remove event from FES and return it
    cEvent *tmp = sim->getFES()->removeFirst();
    ASSERT(tmp == event);
    return event;
}

void UDPsocketRTScheduler::putBackEvent(cEvent *event)
{
    sim->getFES()->putBackFirst(event);
}

void UDPsocketRTScheduler::sendBytes(const char *buf, size_t numBytes){}





