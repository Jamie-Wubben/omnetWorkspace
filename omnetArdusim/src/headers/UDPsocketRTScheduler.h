#ifndef HEADERS_UDPSOCKETRTSCHEDULER_H_
#define HEADERS_UDPSOCKETRTSCHEDULER_H_

#include <omnetpp/platdep/sockets.h>
#include <omnetpp.h>

using namespace omnetpp;

class UDPsocketRTScheduler : public cScheduler
{
  protected:
    // config
    int port;

    cModule *module;
    cMessage *notificationMsg;
    char *recvBuffer;
    int recvBufferSize;
    int *numBytesPtr;

    // state
    int64_t baseTime; // in microseconds, as returned by opp_get_monotonic_clock_usecs()
    SOCKET udpSocket = INVALID_SOCKET;
    //SOCKET connSocket = INVALID_SOCKET;

    virtual void setupListener();
    virtual bool receiveWithTimeout(long usec);
    virtual int receiveUntil(int64_t targetTime);

  public:
    /**
     * Return a description for the GUI.
     */
    virtual std::string str() const override;

    /**
     * Called at the beginning of a simulation run.
     */
    virtual void startRun() override;

    /**
     * Called at the end of a simulation run.
     */
    virtual void endRun() override;

    /**
     * Recalculates "base time" from current wall clock time.
     */
    virtual void executionResumed() override;

    /**
     * To be called from the module which wishes to receive data from the
     * socket. The method must be called from the module's initialize()
     * function.
     */
    virtual void setInterfaceModule(cModule *module, cMessage *notificationMsg,
            char *recvBuffer, int recvBufferSize, int *numBytesPtr);

    /**
     * Returns the first event in the Future Event Set.
     */
    virtual cEvent *guessNextEvent() override;

    /**
     * Scheduler function -- it comes from the cScheduler interface.
     */
    virtual cEvent *takeNextEvent() override;

    /**
     * Undo takeNextEvent() -- it comes from the cScheduler interface.
     */
    virtual void putBackEvent(cEvent *event) override;

    /**
     * Send on the currently open connection
     */
    virtual void sendBytes(const char *buf, size_t numBytes);
};

#endif /* HEADERS_UDPSOCKETRTSCHEDULER_H_ */

