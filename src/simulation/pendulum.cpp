#include "simulation/pendulum.h"
#include <cmath>

namespace simulation {

#pragma region Constructors

    Pendulum::Pendulum(const PendulumParameters& params) :
        params_(params)
    {}

    Pendulum::Pendulum(float cart_mass, float pendulum_mass, float length) : 
        params_({cart_mass, pendulum_mass, length}) 
    {}

#pragma endregion

#pragma region Getters

    math::Vec2 Pendulum::getCartPosition() const {
        return math::Vec2{state_.cart_position, 0.0};
    }
    
    math::Vec2 Pendulum::getPendulumPosition() const {
        // screen space has y-axis pointing down, so we invert the y-coordinate
        float length = params_.length;
        float theta = state_.theta;
        return getCartPosition() + math::Vec2{length * sinf(theta), -length * cosf(theta)};
    }

#pragma endregion

#pragma region Simulation

    void Pendulum::addForce(float force) {
        force_ += force;
    }

    void Pendulum::update(float dt) {
        // Constants
        static constexpr float g = 9.81; // gravity
        auto [M, m, l] = params_;
        auto [x, xdot, theta, omega] = state_;

        // Equations of motion for the inverted pendulum on a cart
        float sin_theta = sinf(theta);
        float cos_theta = cosf(theta);
        float a = M + m;
        float b = m * l * cos_theta;
        float c = b;
        float d = m * l * l;

        float e = force_ + m * l * sin_theta * omega * omega;
        float f = m * l * g * sin_theta;

        // Calculate the acceleration of the cart and the angular acceleration of the pendulum
        float det = a * d - b * c;
        float inv_det = 1.0 / det;

        float xddot = (e * d - f * c) * inv_det;
        float alpha = (f * a - e * b) * inv_det;

        // calculate new state using simple Euler integration
        xdot += xddot * dt;
        x += xdot * dt;
        omega += alpha * dt;
        theta += omega * dt;

        // update variables
        state_ = { x, xdot, theta, omega };
        force_ = 0.0;
    }

#pragma endregion

} // namespace simulation