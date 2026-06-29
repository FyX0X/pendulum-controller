#include "simulation/pendulum.h"
#include <cmath>

namespace simulation {

    Pendulum::Pendulum(float length, float cart_mass, float pendulum_mass) : 
        length_(length), 
        cart_mass_(cart_mass), 
        pendulum_mass_(pendulum_mass),
        cart_position_(0.0), 
        cart_velocity_(0.0), 
        theta_(0.0), 
        omega_(0.0) 
        {}

    void Pendulum::set_state(float cart_position, float cart_velocity, float theta, float omega) {
        cart_position_ = cart_position;
        cart_velocity_ = cart_velocity;
        theta_ = theta;
        omega_ = omega;
    }

#pragma region Getters

    void Pendulum::get_state(float& cart_position, float& cart_velocity, float& theta, float& omega) const {
        cart_position = cart_position_;
        cart_velocity = cart_velocity_;
        theta = theta_;
        omega = omega_;
    }


    math::Vec2 Pendulum::get_cart_position() const {
        return math::Vec2{cart_position_, 0.0};
    }
    math::Vec2 Pendulum::get_pendulum_position() const {
        // screen space has y-axis pointing down, so we invert the y-coordinate
        return get_cart_position() + math::Vec2{length_ * sinf(theta_), -length_ * cosf(theta_)};
    }

#pragma endregion

    void Pendulum::add_force(float force) {
        force_ += force;
    }

    void Pendulum::update(float dt) {
        // Constants
        static constexpr float g = 9.81; // gravity

        // Equations of motion for the inverted pendulum on a cart
        float sin_theta = sin(theta_);
        float cos_theta = cos(theta_);
        float a = cart_mass_ + pendulum_mass_;
        float b = pendulum_mass_ * length_ * cos_theta;
        float c = b;
        float d = pendulum_mass_ * length_ * length_;

        float e = force_ + pendulum_mass_ * length_ * sin_theta * omega_ * omega_;
        float f = pendulum_mass_ * length_ * g * sin_theta;


        // Calculate the acceleration of the cart and the angular acceleration of the pendulum
        float det = a * d - b * c;
        float inv_det = 1.0 / det;

        float cart_acceleration = (e * d - f * c) * inv_det;
        float alpha = (f * a - e * b) * inv_det;



        // Update the state using simple Euler integration
        cart_velocity_ += cart_acceleration * dt;
        cart_position_ += cart_velocity_ * dt;
        omega_ += alpha * dt;
        theta_ += omega_ * dt;

        // reset force after each update
        force_ = 0.0;
    }


} // namespace simulation