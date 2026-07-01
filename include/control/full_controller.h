#pragma once

#include <cmath>
#include <iostream>

#include "LQR_controller.h"
#include "controller.h"
#include "energy_controller.h"


namespace control
{

    class FullController : public Controller
    {
    public:
        FullController(const simulation::PendulumParameters& params, float k) :
            energy(params, k),
            lqr(params)
        {
        }

        float computeForce(const simulation::PendulumState& state, float dt) override
        {
            if (upright) {
                upright = std::abs(state.theta) < 3.1415f * 0.5f;
            } else {
                upright = std::abs(state.theta) < 0.2f;
            }
            if (upright) {
                return lqr.computeForce(state, dt);
            }
            return energy.computeForce(state, dt);
        }

    private:
        LQRController lqr;
        EnergyController energy;
        bool upright = false;
    };

}  // namespace control
