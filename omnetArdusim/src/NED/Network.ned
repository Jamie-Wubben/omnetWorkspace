import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.contract.INetworkNode;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.node.inet.ArdusimHost;
import inet.applications.udpapp.Trigger;
import inet.environment.common.PhysicalEnvironment;
import inet.common.geometry.common.OsgGeographicCoordinateSystem;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.common.IntegratedVisualizer;

network Network
{
    parameters:
        int numUAVs @prompt("Number of clients:") = default(5);
        @display("bgb=1,1");
    submodules:
        rt: RealTime {
            @display("p=765.048,917.65594");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=748.98395,819.264");
        }
        radioMedium: <default("Ieee80211DimensionalRadioMedium")> like IRadioMedium {
            @display("p=905.608,817.256");
        }
        visualizer: IntegratedVisualizer {
            parameters:
                @display("p=576.29596,789.144");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=608.424,947.776");
        }
        
        //<default("AdhocHost")> like INetworkNode 
        host[numUAVs]: ArdusimHost {
            @display("p=905.608,919.664");
        }
        
        trig: Trigger{
            gates:
        		out[parent.numUAVs];  
        }
        
	connections allowunconnected:
	    for i=0..(numUAVs - 1){
	    	trig.out[i] --> host[i].trigger;
	    }
}

