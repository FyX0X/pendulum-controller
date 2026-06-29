#include "pendulum.h"
#include <cmath>

namespace simulation {

    Pendulum::Pendulum(double length, double cart_mass, double pendulum_mass) : 
        length_(length), 
        cart_mass_(cart_mass), 
        pendulum_mass_(pendulum_mass),
        cart_position_(0.0), 
        cart_velocity_(0.0), 
        theta_(0.0), 
        omega_(0.0) 
        {}

    void Pendulum::set_state(double cart_position, double cart_velocity, double theta, double omega) {
        cart_position_ = cart_position;
        cart_velocity_ = cart_velocity;
        theta_ = theta;
        omega_ = omega;
    }

    void Pendulum::get_state(double& cart_position, double& cart_velocity, double& theta, double& omega) const {
        cart_position = cart_position_;
        cart_velocity = cart_velocity_;
        theta = theta_;
        omega = omega_;
    }

    void Pendulum::update(double force, double dt) {
        // Constants
        static constexpr double g = 9.81; // gravity

        // Equations of motion for the inverted pendulum on a cart
        double sin_theta = sin(theta_);
        double cos_theta = cos(theta_);
        double a = cart_mass_ + pendulum_mass_;
        double b = pendulum_mass_ * length_ * cos_theta;
        double c = b;
        double d = pendulum_mass_ * length_ * length_;

        double e = force + pendulum_mass_ * length_ * sin_theta * omega_ * omega_;
        double f = pendulum_mass_ * length_ * g * sin_theta;


        // Calculate the acceleration of the cart and the angular acceleration of the pendulum
        double det = a * d - b * c;
        double inv_det = 1.0 / det;

        double cart_acceleration = (e * d - f * c) * inv_det;
        double alpha = (f * a - e * b) * inv_det;



        // Update the state using simple Euler integration
        cart_velocity_ += cart_acceleration * dt;
        cart_position_ += cart_velocity_ * dt;
        omega_ += alpha * dt;
        theta_ += omega_ * dt;
    }


} // namespace simulation