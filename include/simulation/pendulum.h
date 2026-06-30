#pragma once

#include "math/vector.h"
#include "simulation/pendulum_data.h"


namespace simulation {


    class Pendulum {
    public:
        Pendulum(float length, float cart_mass, float pendulum_mass);

        void setState(float cart_position, float cart_velocity, float theta, float omega);
        void setState(const PendulumState& state) {
            setState(state.cart_position, state.cart_velocity, state.theta, state.omega);
        }

        PendulumState getState() const;
        PendulumParameters getParameters() const;

        math::Vec2 getCartPosition() const;
        math::Vec2 getPendulumPosition() const;

        void addForce(float force);

        void update(float dt);
    private:
        float length_ = 0.f;
        float cart_mass_ = 0.f;
        float pendulum_mass_ = 0.f;

        float cart_position_ = 0.f;
        float cart_velocity_ = 0.f;
        float theta_ = 0.f;
        float omega_ = 0.f;

        float force_ = 0.f;
    };

} // namespace simulation
