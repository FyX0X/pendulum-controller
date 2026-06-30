#pragma once

#include "simulation/pendulum_data.h"

namespace control {

    class Controller {
    public:
        virtual ~Controller() = default;
        virtual float computeForce(const simulation::PendulumState& state, float dt) = 0;
    };

}