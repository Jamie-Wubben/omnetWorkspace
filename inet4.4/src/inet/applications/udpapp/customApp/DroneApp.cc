//ICMP error msg https://erg.abdn.ac.uk/users/gorry/course/inet-pages/icmp-code.html


#include "../customApp/DroneApp.h"

#include "../customApp/GeneralMsg_m.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"

namespace inet {

Define_Module(DroneApp);

// START operations
void DroneApp::initialize(int stage)
{
    event = new cMessage("trigger");
    ApplicationBase::initialize(stage);

}

void DroneApp::setArdusimTalker(int port){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr("158.42.55.99"); //INADDR_ANY; //
}
void DroneApp::handleStartOperation(LifecycleOperation *operation)
{
    int index = getParentModule()->getIndex();
    internalSocket.setOutputGate(gate("socketOut"));
    internalSocket.bind(2000);
    internalSocket.setBroadcast(true);
    internalSocket.joinMulticastGroup(Ipv4Address("224.0.0.9"));
    internalSocket.setCallback(this);


    setArdusimTalker(10000+index); // + index
    scheduleAt(simTime()+1.0, event);
}

Packet* DroneApp::createPacket(const char* message){
    Packet *packet = new Packet("omnetInternal");
    const auto& payload = makeShared<GeneralMsg>();
    payload->setSender(getParentModule()->getIndex());
    payload->setChunkLength(B(1000));
    payload->setPayload(message);
    packet->insertAtBack(payload);
    return packet;
}



// RUNNING operations
void DroneApp::handleMessageWhenUp(cMessage *msg){

    if(!strcmp(msg->getName(), "trigger")){
        //pass
    }else if(!strcmp(msg->getName(),"omnetInternal")){
        internalSocket.processMessage(msg);
    }else if(!strcmp(msg->getName(), "ardusimToOmnet")){
        Packet *packet = check_and_cast<Packet *>(msg);
        const char* payload = packet->peekData<GeneralMsg>()->getPayload();
        Packet *omnetPacket = createPacket(payload);
        internalSocket.sendTo(omnetPacket,Ipv4Address("224.0.0.9"),2000);
    }
}

bool DroneApp::isReceiver(Packet *packet){
    const auto& payload = packet->peekData<GeneralMsg>();
    const char* s1 = payload->getPayload();
    char str[200];
    strcpy(str,s1);

    char* pch;
    pch = strstr(str,"receiverID\":"); // cuts the msg to receiverID:x", ....

    if(pch != nullptr){
        char* pch2;
        pch2 = strstr(pch,":"); //cuts to :x", ....
        if(pch != nullptr){
            int length1 = strlen(pch2);

            char* pch3;
            pch3 = strstr(pch2,"\"");
            if(pch != nullptr){
                int length2 = strlen(pch3);

                char receiver[length1-length2];
                for(int i=1;i<(length1-length2);i++){
                 receiver[i-1] = pch2[i];
                }
                receiver[length1-length2-1] = '\0';

                int i_receiver = atoi(receiver);
                return i_receiver == getParentModule()->getIndex();
            }
        }
    }

    EV << " message format was not correct " << endl;
    return false;
}

void DroneApp::socketDataArrived(UdpSocket *socket, Packet *packet){
    if(!isReceiver(packet)){
        char* message =  (char*) packet->peekData<GeneralMsg>()->getPayload();
        sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr));
    }
}

//STOP operations
DroneApp::~DroneApp(){

}
void DroneApp::socketClosed(UdpSocket *socket){
    EV << "socket closed" << endl;
}
void DroneApp::finish()
{
    cModule* host = getContainingNode(this);
    IMobility  *mod = check_and_cast<IMobility *>(host->getSubmodule("mobility"));
    Coord pos = mod->getCurrentPosition();
    std::ofstream file("altitude.txt",std::ios_base::app);
    file << getParentModule()->getIndex() << " & " <<
            pos.x << " & " << pos.y << " & " << pos.z << " & " << endl;
    file.close();
    cancelAndDelete(event);
    ApplicationBase::finish();
}
void DroneApp::handleStopOperation(LifecycleOperation *operation)
{
    internalSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

// ERROR Operations
void DroneApp::socketErrorArrived(UdpSocket *socket, Indication *indication){
    std::cout << getParentModule()->getIndex() << endl;
    std::cout << " am I here ? " << endl;
    std::cout << indication->getClassAndFullName() << endl;
    std::cout << indication->getControlInfo() << endl;
    delete indication;
}
void DroneApp::handleCrashOperation(LifecycleOperation *operation)
{
    if (operation->getRootModule() != getContainingNode(this)){ // closes socket when the application crashed only
        internalSocket.destroy(); // TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    }
    internalSocket.setCallback(nullptr);
}

} // namespace inet
