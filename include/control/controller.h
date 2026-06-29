#pragma once
#include "simulation/pendulum_state.h"

namespace control {

    class Controller {
    public:
        virtual ~Controller() = default;
        virtual float compute_force(const simulation::PendulumState& state) = 0;
    };

}