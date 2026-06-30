#pragma once

#include "math/vector.h"

namespace simulation {

    struct PendulumState {
        float cart_position = 0;
        float cart_velocity = 0;
        float theta = 0;
        float omega = 0;

        math::Vec4 to_vec() const {
            return {cart_position, cart_velocity, theta, omega};
        }
    };

    struct PendulumParameters {
        float cart_mass = 0;
        float pendulum_mass = 0;
        float length = 0;

        math::Vec3 to_vec() const {
            return {cart_mass, pendulum_mass, length};
        }
    };

} // namespace simulation