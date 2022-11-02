/*
 * Trigger.cc
 *
 *  Created on: Oct 11, 2022
 *      Author: jamie
 */
#include "Trigger.h"

namespace inet{

Define_Module(Trigger);


Trigger::~Trigger(){}

void Trigger::initialize(){
    event = new cMessage("event");

    setArdusimListener(9000);
    scheduleAt(simTime()+1.0, event);
}

void Trigger::setArdusimListener(int port){
    ardusimListingSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (ardusimListingSocket == INVALID_SOCKET){
        throw cRuntimeError("DroneApp: cannot create ardusimListingSocket");
    }

    sockaddr_in sinInterface;
    sinInterface.sin_family = AF_INET;
    sinInterface.sin_addr.s_addr = INADDR_ANY;
    sinInterface.sin_port = htons(port);
    if (bind(ardusimListingSocket, (sockaddr *)&sinInterface, sizeof(sockaddr_in)) == SOCKET_ERROR){
        throw cRuntimeError("DroneApp: ardusimSocket bind() failed");
    }
}

int Trigger::listenToArduSim(long usec){
    fd_set readFDs, writeFDs, exceptFDs;
    FD_ZERO(&readFDs);
    FD_ZERO(&writeFDs);
    FD_ZERO(&exceptFDs);

    FD_SET(ardusimListingSocket, &readFDs);
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = usec;


    if (select(FD_SETSIZE, &readFDs, &writeFDs, &exceptFDs, &timeout) > 0) {
        // Something happened on one of the sockets defined by FD_SET() check which one
        if(FD_ISSET(ardusimListingSocket, &readFDs)){
            // something happend at the udpSocket
            struct sockaddr_in cliaddr;
            memset(&cliaddr, 0, sizeof(cliaddr));
            socklen_t len = sizeof(cliaddr);
            int nBytes = recvfrom(ardusimListingSocket, (char *)recvBuffer, SIZE_MSG_BUFFER,MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
            if(nBytes >= SIZE_MSG_BUFFER){
                EV_WARN << "msg buffer is full, increase size!" << endl;
            }
            return nBytes;
        }
    }
    return 0;
}

char* Trigger::getArduSimMessage(int numReceivedBytes){
    int lastIndexOfMsg;
    for(int i=numReceivedBytes;i>0;i--){
        if(recvBuffer[i] == '}'){
            lastIndexOfMsg = i;
            break;
        }
    }
    int numchar = lastIndexOfMsg + 1;
    char* msg = new char[numchar + 1];
    strncpy(msg,recvBuffer,numchar);
    msg[numchar] = '\0';
    return msg;
}

int Trigger::getSenderID(char* data){
    char* pch;
    pch = strstr(data,"senderID\":"); // cuts the msg to receiverID:x", ....

    if(pch != nullptr){

        char* pch2;
        pch2 = strstr(pch,":"); //cuts to :x", ....
        if(pch2 != nullptr){
            int length1 = strlen(pch2);

            char* pch3;
            pch3 = strstr(pch2,",");
            if(pch3 != nullptr){
                int length2 = strlen(pch3);

                char sender[length1-length2];
                for(int i=1;i<(length1-length2);i++){
                 sender[i-1] = pch2[i];
                }
                sender[length1-length2-1] = '\0';

                int senderID = atoi(sender);
                return senderID;
            }
        }
    }
    return -1;
}

void Trigger::handleMessage(cMessage *msg){
    int bytesReceived = listenToArduSim(1);
    if(bytesReceived){
        //const auto time = std::chrono::system_clock::now();
        //std::cout << "start " << std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count() << endl;
        char* data = getArduSimMessage(bytesReceived);
        int senderID = getSenderID(data);
        Packet* packet = createPacket(data,senderID);
        send(packet,"out",senderID);
    }

    scheduleAt(simTime()+0.01, event);
}

Packet* Trigger::createPacket(char* message, int senderID ){
    Packet *packet = new Packet("ardusimToOmnet");
    packet->addTag<SocketInd>()->setSocketId(senderID);
    const auto& payload = makeShared<GeneralMsg>();
    payload->setSender(senderID);
    payload->setChunkLength(B(1000));
    payload->setPayload(message);
    packet->insertAtBack(payload);
    return packet;
}



}
