//
// Copyright (C) 2005 Emin Ilker Cetinbas
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
//
// Author: Emin Ilker Cetinbas (niw3_at_yahoo_d0t_com)
//

#include "inet/mobility/single/LinearMobility.h"

#include "inet/common/INETMath.h"

namespace inet {

Define_Module(LinearMobility);

LinearMobility::LinearMobility()
{
}

LinearMobility::~LinearMobility(){

}

void LinearMobility::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);

    EV_TRACE << "initializing LinearMobility stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        stationary = false;
        int port = 8000 + getParentModule()->getIndex();
        setArdusimListener(port);
    }

}

void LinearMobility::move()
{
    int bytesReceived = listenToArduSim(1);

    if(bytesReceived > 0){
        char* msg = new char;
        memcpy(msg,recvBuffer,bytesReceived);
        const char delimiter[2] = ",";
        char *token;

        token = strtok(msg,delimiter);
        int i=0;
        int coordinates[3];
        while(token != NULL){
            coordinates[i] = atoi(token);
            token = strtok(NULL,delimiter);
            i++;
        }
        lastPosition.x = coordinates[0];
        lastPosition.y = coordinates[1];
        lastPosition.z = coordinates[2];
    }
}

void LinearMobility::setArdusimListener(int port){
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
int LinearMobility::listenToArduSim(long usec){
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
} // namespace inet
