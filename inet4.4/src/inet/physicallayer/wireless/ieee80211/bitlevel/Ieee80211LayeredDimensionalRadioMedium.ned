//
// Copyright (C) 2014 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package inet.physicallayer.wireless.ieee80211.bitlevel;

import inet.physicallayer.wireless.common.medium.RadioMedium;

module Ieee80211LayeredDimensionalRadioMedium extends RadioMedium
{
    parameters:
        analogModel.typename = default("LayeredDimensionalAnalogModel");
        backgroundNoise.typename = default("IsotropicDimensionalBackgroundNoise");
        backgroundNoise.power = default(-110dBm);
        mediumLimitCache.centerFrequency = default(2.4GHz);
        mediumLimitCache.minReceptionPower = default(-85dBm);
        mediumLimitCache.minInterferencePower = default(-110dBm);
}

