/*
 * RealTime.h
 *
 *  Created on: Jun 22, 2022
 *      Author: jamie
 */

#ifndef HEADERS_REALTIME_H_
#define HEADERS_REALTIME_H_

#include <omnetpp.h>
#include "UDPsocketRTScheduler.h"
using namespace omnetpp;

#define SIZE_MSG_BUFFER 1000
class RealTime: public cSimpleModule{
    private:
        cMessage *rtEvent = nullptr;
        UDPsocketRTScheduler *rtScheduler;

        char msgBuffer[SIZE_MSG_BUFFER];
        int numReceivedBytes;

    public:
      virtual ~RealTime();

    protected:
      virtual void initialize() override;
      virtual void handleMessage(cMessage *msg) override;
};

#endif /* HEADERS_REALTIME_H_ */



