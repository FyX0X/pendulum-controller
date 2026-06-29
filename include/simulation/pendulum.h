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

        void update(float force, float dt);
    private:
        float length_;
        float cart_mass_;
        float pendulum_mass_;

        float cart_position_;
        float cart_velocity_;
        float theta_;
        float omega_;
    };

} // namespace simulation
