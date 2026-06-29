#pragma once

namespace simulation {

    class Pendulum {
    public:
        Pendulum(double length, double cart_mass, double pendulum_mass);

        void set_state(double cart_position, double cart_velocity, double theta, double omega);
        void get_state(double& cart_position, double& cart_velocity, double& theta, double& omega) const;

        void update(double force, double dt);
    private:
        double length_;
        double cart_mass_;
        double pendulum_mass_;

        double cart_position_;
        double cart_velocity_;
        double theta_;
        double omega_;
    };

} // namespace simulation
