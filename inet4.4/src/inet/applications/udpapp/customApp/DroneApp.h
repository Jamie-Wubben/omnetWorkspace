//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004,2011 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef __INET_DRONEAPP_H
#define __INET_DRONEAPP_H

#include <vector>

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include <omnetpp/platdep/sockets.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <omnetpp.h>
#include <iostream>
#include <fstream>
#include "inet/common/ModuleAccess.h"
#include "inet/mobility/contract/IMobility.h"
#include <chrono>


#include "inet/applications/base/ApplicationPacket_m.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))
namespace inet {

/**
 * UDP application. See NED for more info.
 */
class INET_API DroneApp : public ApplicationBase, public UdpSocket::ICallback
{
    private:
        cMessage *event;
        int SIZE_MSG_BUFFER = 1000;
        char recvBuffer[1000];
        Packet* createPacket(const char* message);
    protected:
        UdpSocket internalSocket;
        L3Address multicastGroup;


        int sockfd;
        struct sockaddr_in servaddr;

        //START operations
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }
        virtual void initialize(int stage) override;
        virtual void handleStartOperation(LifecycleOperation *operation) override;
        void setArdusimTalker(int port);

        //RUNNING operations
        virtual void handleMessageWhenUp(cMessage *msg) override;
        virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
        bool isReceiver(Packet *packet);
        virtual void refreshDisplay(){};

        //STOP operations
        virtual void finish() override;
        virtual void handleStopOperation(LifecycleOperation *operation) override;
        virtual void socketClosed(UdpSocket *socket) override;

        //ERROR operations
        virtual void handleCrashOperation(LifecycleOperation *operation) override;
        virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override;


    public:
        DroneApp() {}
        ~DroneApp();
        };

} // namespace inet

#endif
