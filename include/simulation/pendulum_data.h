#pragma once

#include "math/vector.h"

namespace simulation {

    struct PendulumState {
        float cart_position = 0;
        float cart_velocity = 0;
        float theta = 0;
        float omega = 0;

        math::Vec4 to_vec() const {
            return { cart_position, cart_velocity, theta, omega };
        }
    };

    struct PendulumParameters {
        float cart_mass = 0;
        float pendulum_mass = 0;
        float length = 0;

        math::Vec3 to_vec() const {
            return { cart_mass, pendulum_mass, length };
        }

        bool operator==(const PendulumParameters&) const = default;
    };

    struct DoublePendulumState {
        float cart_position = 0.f;
        float cart_velocity = 0.f;
        float theta1 = 0.f;
        float omega1 = 0.f;
        float theta2 = 0.f;
        float omega2 = 0.f;

        math::Vec<6> to_vec() const {
            return { cart_position, cart_velocity, theta1, omega1, theta2, omega2 };
        }

    };

    struct DoublePendulumParameters {
        float cart_mass = 0.f;
        float mass1 = 0.f;
        float mass2 = 0.f;
        float length1 = 0.f;
        float length2 = 0.f;

        math::Vec<5> to_vec() const {
            return { cart_mass, mass1, mass2, length1, length2 };
        }

        bool operator==(const DoublePendulumParameters&) const = default;
    };

} // namespace simulation