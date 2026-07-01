#pragma once

#include "math/vector.h"
#include "simulation/pendulum_data.h"


namespace simulation
{

    class DoublePendulum
    {
    public:
        DoublePendulum(const DoublePendulumParameters& params);
        DoublePendulum(float M, float m1, float m2, float l1, float l2);

        void setState(const DoublePendulumState& state) { state_ = state; }
        void setState(float cart_position, float cart_velocity, float theta1, float omega1, float theta2, float omega2)
        {
            setState({cart_position, cart_velocity, theta1, omega1, theta2, omega2});
        }

        DoublePendulumState getState() const { return state_; };
        DoublePendulumParameters getParameters() const { return params_; };

        math::Vec2 getCartPosition() const;
        math::Vec2 getFirstMassPosition() const;
        math::Vec2 getSecondMassPosition() const;

        float getAppliedForce() const { return last_frame_force_; }

        void addForce(float force);

        void update(float dt);

    private:
        DoublePendulumParameters params_ = {0};
        DoublePendulumState state_ = {0};

        float force_ = 0.f;
        float last_frame_force_ = 0.f;
    };

}  // namespace simulation
