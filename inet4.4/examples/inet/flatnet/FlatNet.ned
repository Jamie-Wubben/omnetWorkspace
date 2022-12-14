//
// Copyright (C) 2004 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//






package inet.examples.inet.flatnet;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;


network FlatNet
{
    types:
        channel fiberline extends DatarateChannel
        {
            delay = 1us;
            datarate = 512Mbps;
        }
        channel ethernetline extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 10Mbps;
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='192.168.x.x' netmask='255.255.x.x'/></config>");
                @display("p=100,100;is=s");
        }
        rte[57]: Router;
        cli[2]: StandardHost {
            parameters:
                @display("i=device/laptop");
        }
        srv: StandardHost {
            parameters:
                @display("i=device/server");
        }
    connections:
        cli[0].pppg++ <--> ethernetline <--> rte[50].pppg++;
        cli[1].pppg++ <--> ethernetline <--> rte[8].pppg++;
        srv.pppg++ <--> fiberline <--> rte[18].pppg++;
        rte[0].pppg++ <--> fiberline <--> rte[1].pppg++;
        rte[1].pppg++ <--> fiberline <--> rte[2].pppg++;
        rte[1].pppg++ <--> fiberline <--> rte[4].pppg++;
        rte[3].pppg++ <--> fiberline <--> rte[4].pppg++;
        rte[4].pppg++ <--> fiberline <--> rte[5].pppg++;
        rte[4].pppg++ <--> fiberline <--> rte[7].pppg++;
        rte[5].pppg++ <--> fiberline <--> rte[6].pppg++;
        rte[5].pppg++ <--> fiberline <--> rte[10].pppg++;
        rte[6].pppg++ <--> fiberline <--> rte[7].pppg++;
        rte[6].pppg++ <--> fiberline <--> rte[9].pppg++;
        rte[7].pppg++ <--> fiberline <--> rte[8].pppg++;
        rte[7].pppg++ <--> fiberline <--> rte[12].pppg++;
        rte[9].pppg++ <--> fiberline <--> rte[11].pppg++;
        rte[10].pppg++ <--> fiberline <--> rte[11].pppg++;
        rte[10].pppg++ <--> fiberline <--> rte[13].pppg++;
        rte[11].pppg++ <--> fiberline <--> rte[12].pppg++;
        rte[11].pppg++ <--> fiberline <--> rte[14].pppg++;
        rte[12].pppg++ <--> fiberline <--> rte[15].pppg++;
        rte[13].pppg++ <--> fiberline <--> rte[18].pppg++;
        rte[14].pppg++ <--> fiberline <--> rte[15].pppg++;
        rte[14].pppg++ <--> fiberline <--> rte[22].pppg++;
        rte[15].pppg++ <--> fiberline <--> rte[16].pppg++;
        rte[16].pppg++ <--> fiberline <--> rte[17].pppg++;
        rte[16].pppg++ <--> fiberline <--> rte[23].pppg++;
        rte[18].pppg++ <--> fiberline <--> rte[19].pppg++;
        rte[18].pppg++ <--> fiberline <--> rte[21].pppg++;
        rte[19].pppg++ <--> fiberline <--> rte[20].pppg++;
        rte[19].pppg++ <--> fiberline <--> rte[26].pppg++;
        rte[20].pppg++ <--> fiberline <--> rte[21].pppg++;
        rte[20].pppg++ <--> fiberline <--> rte[24].pppg++;
        rte[20].pppg++ <--> fiberline <--> rte[25].pppg++;
        rte[21].pppg++ <--> fiberline <--> rte[22].pppg++;
        rte[21].pppg++ <--> fiberline <--> rte[23].pppg++;
        rte[21].pppg++ <--> fiberline <--> rte[24].pppg++;
        rte[23].pppg++ <--> fiberline <--> rte[24].pppg++;
        rte[24].pppg++ <--> fiberline <--> rte[28].pppg++;
        rte[25].pppg++ <--> fiberline <--> rte[27].pppg++;
        rte[26].pppg++ <--> fiberline <--> rte[32].pppg++;
        rte[27].pppg++ <--> fiberline <--> rte[29].pppg++;
        rte[27].pppg++ <--> fiberline <--> rte[30].pppg++;
        rte[27].pppg++ <--> fiberline <--> rte[32].pppg++;
        rte[28].pppg++ <--> fiberline <--> rte[29].pppg++;
        rte[28].pppg++ <--> fiberline <--> rte[31].pppg++;
        rte[29].pppg++ <--> fiberline <--> rte[31].pppg++;
        rte[30].pppg++ <--> fiberline <--> rte[36].pppg++;
        rte[31].pppg++ <--> fiberline <--> rte[33].pppg++;
        rte[32].pppg++ <--> fiberline <--> rte[34].pppg++;
        rte[33].pppg++ <--> fiberline <--> rte[37].pppg++;
        rte[34].pppg++ <--> fiberline <--> rte[35].pppg++;
        rte[34].pppg++ <--> fiberline <--> rte[40].pppg++;
        rte[35].pppg++ <--> fiberline <--> rte[36].pppg++;
        rte[35].pppg++ <--> fiberline <--> rte[39].pppg++;
        rte[36].pppg++ <--> fiberline <--> rte[37].pppg++;
        rte[37].pppg++ <--> fiberline <--> rte[38].pppg++;
        rte[38].pppg++ <--> fiberline <--> rte[39].pppg++;
        rte[38].pppg++ <--> fiberline <--> rte[42].pppg++;
        rte[39].pppg++ <--> fiberline <--> rte[40].pppg++;
        rte[39].pppg++ <--> fiberline <--> rte[41].pppg++;
        rte[40].pppg++ <--> fiberline <--> rte[43].pppg++;
        rte[40].pppg++ <--> fiberline <--> rte[44].pppg++;
        rte[40].pppg++ <--> fiberline <--> rte[52].pppg++;
        rte[41].pppg++ <--> fiberline <--> rte[42].pppg++;
        rte[41].pppg++ <--> fiberline <--> rte[43].pppg++;
        rte[42].pppg++ <--> fiberline <--> rte[43].pppg++;
        rte[43].pppg++ <--> fiberline <--> rte[46].pppg++;
        rte[44].pppg++ <--> fiberline <--> rte[45].pppg++;
        rte[44].pppg++ <--> fiberline <--> rte[47].pppg++;
        rte[45].pppg++ <--> fiberline <--> rte[46].pppg++;
        rte[46].pppg++ <--> fiberline <--> rte[49].pppg++;
        rte[47].pppg++ <--> fiberline <--> rte[48].pppg++;
        rte[48].pppg++ <--> fiberline <--> rte[50].pppg++;
        rte[48].pppg++ <--> fiberline <--> rte[51].pppg++;
        rte[49].pppg++ <--> fiberline <--> rte[50].pppg++;
        rte[50].pppg++ <--> fiberline <--> rte[53].pppg++;
        rte[51].pppg++ <--> fiberline <--> rte[52].pppg++;
        rte[51].pppg++ <--> fiberline <--> rte[53].pppg++;
        rte[52].pppg++ <--> fiberline <--> rte[53].pppg++;
        rte[52].pppg++ <--> fiberline <--> rte[54].pppg++;
        rte[53].pppg++ <--> fiberline <--> rte[56].pppg++;
        rte[54].pppg++ <--> fiberline <--> rte[55].pppg++;
        rte[55].pppg++ <--> fiberline <--> rte[56].pppg++;
}


