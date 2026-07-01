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

    struct DoublePendulumState {
        float x = 0.f;
        float xdot = 0.f;
        float theta1 = 0.f;
        float omega1 = 0.f;
        float theta2 = 0.f;
        float omega2 = 0.f;

        math::Vec<6> to_vec() const {
            return {x, xdot, theta1, omega1, theta2, omega2};
        }
    };

    struct DoublePendulumParameters {
        float M = 0.f;
        float m1 = 0.f;
        float m2 = 0.f;
        float l1 = 0.f;
        float l2 = 0.f;

        math::Vec<5> to_vec() const {
            return {M, m1, m2, l1, l2};
        }
    };

} // namespace simulation