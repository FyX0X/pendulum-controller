#pragma once

#include "math/vector.h"

namespace simulation {

    class Pendulum {
    public:
        Pendulum(float length, float cart_mass, float pendulum_mass);

        void set_state(float cart_position, float cart_velocity, float theta, float omega);
        void get_state(float& cart_position, float& cart_velocity, float& theta, float& omega) const;

        math::Vec2 get_cart_position() const;
        math::Vec2 get_pendulum_position() const;

        void add_force(float force);

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
