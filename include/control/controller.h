#pragma once
#include "simulation/pendulum_state.h"

namespace control {

    class Controller {
    public:
        virtual ~Controller() = default;
        virtual float computeForce(const simulation::PendulumState& state, float dt) = 0;
    };

}