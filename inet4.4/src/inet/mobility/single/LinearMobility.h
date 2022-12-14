//
// Copyright (C) 2005 Emin Ilker Cetinbas
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
//
// Author: Emin Ilker Cetinbas (niw3_at_yahoo_d0t_com)
//

#ifndef __INET_LINEARMOBILITY_H
#define __INET_LINEARMOBILITY_H

#include "inet/mobility/base/MovingMobilityBase.h"
#include <omnetpp/platdep/sockets.h>
#include <string>

namespace inet {

/**
 * @brief Linear movement model. See NED file for more info.
 *
 * @ingroup mobility
 * @author Emin Ilker Cetinbas
 */
class INET_API LinearMobility : public MovingMobilityBase
{
    private:
        void setArdusimListener(int port);
        int listenToArduSim(long usec);
        SOCKET ardusimListingSocket;
        int SIZE_MSG_BUFFER = 1000;
        char recvBuffer[1000];

    protected:
        double speed;

    protected:
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }

        /** @brief Initializes mobility model parameters.*/
        virtual void initialize(int stage) override;

        /** @brief Move the host*/
        virtual void move() override;

    public:
        virtual double getMaxSpeed() const override { return speed; }
        LinearMobility();
        ~LinearMobility();
};

} // namespace inet

#endif
