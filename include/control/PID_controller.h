#pragma once


#include "controller.h"


namespace control
{

    class PIDController : public Controller
    {
    public:
        PIDController(float kp, float ki, float kd) :
            kp_(kp),
            ki_(ki),
            kd_(kd)
        {
        }

        float computeForce(const simulation::PendulumState& state, float dt) override
        {
            integral_ += state.theta * dt;

            return kp_ * state.theta + ki_ * integral_ + kd_ * state.omega;
        }

    private:
        float kp_ = 0;
        float ki_ = 0;
        float kd_ = 0;

        float integral_ = 0;
    };

}  // namespace control
