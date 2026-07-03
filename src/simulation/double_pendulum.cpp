#include "simulation/double_pendulum.h"

#include <cmath>
#include <numbers>

namespace simulation
{

#pragma region Constructors

    DoublePendulum::DoublePendulum(const DoublePendulumParameters& params) :
        params_(params)
    {
    }

    DoublePendulum::DoublePendulum(float M, float m1, float m2, float l1, float l2) :
        params_({M, m1, m2, l1, l2})
    {
    }

#pragma endregion

#pragma region Getters

    math::Vec2 DoublePendulum::getCartPosition() const { return math::Vec2{state_.cart_position, 0.0}; }

    math::Vec2 DoublePendulum::getFirstMassPosition() const
    {
        // screen space has y-axis pointing down, so we invert the y-coordinate
        float l1 = params_.length1;
        float theta1 = state_.theta1;
        return getCartPosition() + math::Vec2{l1 * sinf(theta1), -l1 * cosf(theta1)};
    }

    math::Vec2 DoublePendulum::getSecondMassPosition() const
    {
        // screen space has y-axis pointing down, so we invert the y-coordinate
        float l2 = params_.length2;
        float theta2 = state_.theta2;
        return getFirstMassPosition() + math::Vec2{l2 * sinf(theta2), -l2 * cosf(theta2)};
    }

#pragma endregion

#pragma region Setters

    void DoublePendulum::setState(const DoublePendulumState& state)
    {
        state_ = state;
        state_.theta1 = std::remainder(state_.theta1, 2.f * std::numbers::pi_v<float>);
        state_.theta2 = std::remainder(state_.theta2, 2.f * std::numbers::pi_v<float>);
    }

#pragma endregion


#pragma region Simulation

    void DoublePendulum::addForce(float force) { force_ += force; }

    void DoublePendulum::update(float dt)
    {
        // Constants, parameters and variables
        static constexpr float g = 9.81;  // gravity
        auto [M, m1, m2, l1, l2] = params_;
        auto [x, xdot, theta1, omega1, theta2, omega2] = state_;
        float F = force_;

        // Compute accelerations (Code generated using Sympy)
        float xddot =
            (F * m1 - F * m2 * pow(cos(theta1 - theta2), 2) + F * m2 - 1.0 / 2.0 * g * pow(m1, 2) * sin(2 * theta1) +
             g * m1 * m2 * sin(theta1) * cos(theta2) * cos(theta1 - theta2) - g * m1 * m2 * sin(2 * theta1) +
             g * m1 * m2 * sin(theta2) * cos(theta1) * cos(theta1 - theta2) -
             1.0 / 2.0 * g * m1 * m2 * sin(2 * theta2) +
             g * pow(m2, 2) * sin(theta1) * cos(theta2) * cos(theta1 - theta2) -
             1.0 / 2.0 * g * pow(m2, 2) * sin(2 * theta1) +
             g * pow(m2, 2) * sin(theta2) * cos(theta1) * cos(theta1 - theta2) -
             1.0 / 2.0 * g * pow(m2, 2) * sin(2 * theta2) + l1 * pow(m1, 2) * pow(omega1, 2) * sin(theta1) +
             (1.0 / 4.0) * l1 * m1 * m2 * pow(omega1, 2) * (sin(theta1 - 2 * theta2) + sin(3 * theta1 - 2 * theta2)) -
             l1 * m1 * m2 * pow(omega1, 2) * sin(theta1) * pow(cos(theta1 - theta2), 2) +
             2 * l1 * m1 * m2 * pow(omega1, 2) * sin(theta1) -
             l1 * m1 * m2 * pow(omega1, 2) * sin(theta1 - theta2) * cos(theta2) +
             (1.0 / 4.0) * l1 * pow(m2, 2) * pow(omega1, 2) *
                 (sin(theta1 - 2 * theta2) + sin(3 * theta1 - 2 * theta2)) -
             l1 * pow(m2, 2) * pow(omega1, 2) * sin(theta1) * pow(cos(theta1 - theta2), 2) +
             l1 * pow(m2, 2) * pow(omega1, 2) * sin(theta1) -
             l1 * pow(m2, 2) * pow(omega1, 2) * sin(theta1 - theta2) * cos(theta2) +
             l2 * m1 * m2 * pow(omega2, 2) * sin(theta2) +
             l2 * m1 * m2 * pow(omega2, 2) * sin(theta1 - theta2) * cos(theta1) -
             1.0 / 4.0 * l2 * pow(m2, 2) * pow(omega2, 2) * (sin(2 * theta1 - 3 * theta2) + sin(2 * theta1 - theta2)) -
             l2 * pow(m2, 2) * pow(omega2, 2) * sin(theta2) * pow(cos(theta1 - theta2), 2) +
             l2 * pow(m2, 2) * pow(omega2, 2) * sin(theta2) +
             l2 * pow(m2, 2) * pow(omega2, 2) * sin(theta1 - theta2) * cos(theta1)) /
            (M * m1 + M * m2 * pow(sin(theta1), 2) - 2 * M * m2 * sin(theta1) * sin(theta2) * cos(theta1 - theta2) +
             M * m2 * pow(sin(theta2), 2) + pow(m1, 2) * pow(sin(theta1), 2) + m1 * m2 * pow(sin(theta1), 2));
        float alpha1 =
            (-2 * F * m1 * cos(theta1) - F * m2 * cos(theta1) + F * m2 * cos(theta1 - 2 * theta2) +
             2 * M * g * m1 * sin(theta1) + M * g * m2 * sin(theta1) + M * g * m2 * sin(theta1 - 2 * theta2) -
             M * l1 * m2 * pow(omega1, 2) * sin(2 * theta1 - 2 * theta2) -
             2 * M * l2 * m2 * pow(omega2, 2) * sin(theta1 - theta2) + 2 * g * pow(m1, 2) * sin(theta1) +
             2 * g * m1 * m2 * sin(theta1) - l1 * pow(m1, 2) * pow(omega1, 2) * sin(2 * theta1) -
             l1 * m1 * m2 * pow(omega1, 2) * sin(2 * theta1) - l2 * m1 * m2 * pow(omega2, 2) * sin(theta1 - theta2) -
             l2 * m1 * m2 * pow(omega2, 2) * sin(theta1 + theta2)) /
            (l1 * (2 * M * m1 - M * m2 * cos(2 * theta1 - 2 * theta2) + M * m2 - pow(m1, 2) * cos(2 * theta1) +
                   pow(m1, 2) - m1 * m2 * cos(2 * theta1) + m1 * m2));
        float alpha2 =
            (-(m1 + m2) * (g * sin(theta2) + l1 * pow(omega1, 2) * sin(theta1 - theta2)) * (M + m1 + m2) *
                 (M + m1 + m2 - (m1 + m2) * pow(cos(theta1), 2)) +
             (m1 + m2) * (F + l1 * pow(omega1, 2) * (m1 + m2) * sin(theta1) + l2 * m2 * pow(omega2, 2) * sin(theta2)) *
                 (M + m1 + m2 - (m1 + m2) * pow(cos(theta1), 2)) * cos(theta2) +
             ((m1 + m2) * (F + l1 * pow(omega1, 2) * (m1 + m2) * sin(theta1) + l2 * m2 * pow(omega2, 2) * sin(theta2)) *
                  cos(theta1) -
              (g * (m1 + m2) * sin(theta1) - l2 * m2 * pow(omega2, 2) * sin(theta1 - theta2)) * (M + m1 + m2)) *
                 ((m1 + m2) * cos(theta1) * cos(theta2) - (M + m1 + m2) * cos(theta1 - theta2))) /
            (l2 * (m2 * (m1 + m2) * (M + m1 + m2 - (m1 + m2) * pow(cos(theta1), 2)) * pow(cos(theta2), 2) +
                   m2 * pow((m1 + m2) * cos(theta1) * cos(theta2) - (M + m1 + m2) * cos(theta1 - theta2), 2) -
                   (m1 + m2) * (M + m1 + m2) * (M + m1 + m2 - (m1 + m2) * pow(cos(theta1), 2))));

        // integrate
        xdot += xddot * dt;
        x += xdot * dt;
        omega1 += alpha1 * dt;
        theta1 += omega1 * dt;
        omega2 += alpha2 * dt;
        theta2 += omega2 * dt;

        // update actual state
        setState({x, xdot, theta1, omega1, theta2, omega2});
        last_frame_force_ = force_;
        force_ = 0.0;
    }

#pragma endregion

}  // namespace simulation
