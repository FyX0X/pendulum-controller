#pragma once

#include "math/vector.h"
#include "simulation/pendulum_data.h"


namespace simulation {


    class DoublePendulum {
    public:
        DoublePendulum(const DoublePendulumState& state);
        DoublePendulum(float M, float m1, float m2, float l1, float l2);
        
        void setState(const DoublePendulumState& state) { state_ = state; }
        void setState(float x, float xdot, float theta1, float omega1, float theta2, float omega2) {
            setState({x, xdot, theta1, omega1, theta2, omega2});
        }

        DoublePendulumState getState() const { return state_; };
        DoublePendulumParameters getParameters() const { return params_; };

        math::Vec2 getCartPosition() const;
        math::Vec2 getFirstMassPosition() const;
        math::Vec2 getSecondMassPosition() const;

        void addForce(float force);

        void update(float dt);
    private:
        DoublePendulumParameters params_ = { 0 };
        DoublePendulumState state_ = { 0 };

        float force_ = 0.f;
    };

} // namespace simulation
