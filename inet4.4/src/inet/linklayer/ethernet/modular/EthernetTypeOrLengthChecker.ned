//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.linklayer.ethernet.modular;

import inet.queueing.base.PacketFilterBase;
import inet.queueing.contract.IPacketFilter;

simple EthernetTypeOrLengthChecker extends PacketFilterBase like IPacketFilter
{
    parameters:
        @class(EthernetTypeOrLengthChecker);
        @display("i=block/checker");
}
