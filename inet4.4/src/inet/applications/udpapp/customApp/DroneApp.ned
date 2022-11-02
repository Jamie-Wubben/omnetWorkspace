package inet.applications.udpapp.customApp;
import inet.applications.contract.IApp;

simple DroneApp like IApp
{
    parameters:
        string interfaceTableModule;   // The path to the InterfaceTable module
        double startTime @unit(s) = default(0s); // application start time
        double stopTime @unit(s) = default(-1s);  // time of finishing receiving
        bool receiveBroadcast = default(false); // if true, makes the socket receive broadcast packets
        string multicastGroup = default(""); // if non-empty, makes the socket receive multicast packets sent to that group
        string multicastSources = default(""); // if non-empty, than the socket receives multicast packets from those sources only

        @display("i=block/sink");
        @lifecycleSupport;
        double stopOperationExtraTime @unit(s) = default(-1s);    // extra time after lifecycle stop operation finished
        double stopOperationTimeout @unit(s) = default(2s);    // timeout value for lifecycle stop operation
        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[throughput](title="throughput"; unit=bps; source="throughput(packetReceived)"; record=vector);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,vector; interpolationmode=none);
        @statistic[rcvdPkSeqNo](title="received packet sequence number"; source="appPkSeqNo(packetReceived)"; record=vector; interpolationmode=none);

    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}