#pragma once


#include "controller.h"


namespace control
{

    class ZeroController : public Controller
    {
    public:
        float computeForce(const simulation::PendulumState& state, float dt) override
        {
            return 0;
        }
    };

}  // namespace control
