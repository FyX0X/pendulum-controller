#pragma once

#include "simulation/pendulum_data.h"

namespace control
{

    class DoubleController
    {
    public:
        virtual ~DoubleController() = default;
        virtual float computeForce(const simulation::DoublePendulumState& state, float dt) = 0;
    };

}  // namespace control
