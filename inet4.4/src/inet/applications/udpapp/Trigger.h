/*
 * Trigger.h
 *
 *  Created on: Oct 11, 2022
 *      Author: jamie
 */

#ifndef HEADERS_TRIGGER_H_
#define HEADERS_TRIGGER_H_

#include <omnetpp.h>
#include <omnetpp/platdep/sockets.h>
#include <sys/socket.h>
#include <chrono>


#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "customApp/GeneralMsg_m.h"
#include "inet/common/socket/SocketTag_m.h"

namespace inet{

class Trigger: public cSimpleModule{
    private:
        cMessage *event;
        Packet* createPacket(char* message,int senderID);
        char* getArduSimMessage(int numReceivedBytes);
        int getSenderID(char* data);

        void setArdusimListener(int port);
        int listenToArduSim(long usec);
        SOCKET ardusimListingSocket;
        int SIZE_MSG_BUFFER = 1000;
        char recvBuffer[1000];

    public:
          virtual ~Trigger();

    protected:
      virtual void initialize() override;
      virtual void handleMessage(cMessage *msg) override;

};
}
#endif /* HEADERS_TRIGGER_H_ */
