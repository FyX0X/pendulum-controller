#pragma once

#include "math/vector.h"
#include "simulation/pendulum_data.h"


namespace simulation {


    class Pendulum {
    public:
        Pendulum(const PendulumParameters& params);
        Pendulum(float cart_mass, float pendulum_mass, float length);

        void setState(const PendulumState& state) { state_ = state; }
        void setState(float cart_position, float cart_velocity, float theta, float omega) {
            setState({cart_position, cart_velocity, theta, omega});
        }

        PendulumState getState() const { return state_; }
        PendulumParameters getParameters() const { return params_; }

        math::Vec2 getCartPosition() const;
        math::Vec2 getPendulumPosition() const;

        void addForce(float force);

        void update(float dt);
    private:
        PendulumParameters params_ = { 0 };
        PendulumState state_ = { 0 };

        float force_ = 0.f;
    };

} // namespace simulation
