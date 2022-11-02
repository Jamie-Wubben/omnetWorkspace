/*
 * RealTime.cc
 *
 *  Created on: Jun 22, 2022
 *      Author: jamie
 */

#include "../headers/RealTime.h"

Define_Module(RealTime);

RealTime::~RealTime(){
    cancelAndDelete(rtEvent);
}

void RealTime::initialize(){
    rtEvent = new cMessage("rtEvent");
    rtScheduler = check_and_cast<UDPsocketRTScheduler *>(getSimulation()->getScheduler());
    rtScheduler->setInterfaceModule(this, rtEvent, msgBuffer, SIZE_MSG_BUFFER, &numReceivedBytes);
}

void RealTime::handleMessage(cMessage *msg){
    if (msg == rtEvent){
        EV_WARN << "received a msg on the real time keeper, this is not wanted" << endl;
        delete msg;
    }
}

