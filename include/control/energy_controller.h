#pragma once

#include <cmath>

#include "controller.h"
#include "math/vector.h"

namespace control
{

    class EnergyController : public Controller
    {
    public:
        EnergyController(const simulation::PendulumParameters& params, float k) :
            params_(params),
            k_(k)
        {
        }

        float computeForce(const simulation::PendulumState& state, float dt) override
        {
            auto [x, xdot, theta, omega] = state;
            float E = get_pendulum_energy_inertial_frame(state);
            float sign = omega * cosf(theta) >= 0 ? 1.f : -1.f;
            return k_ * E * sign;
        }

    private:
        simulation::PendulumParameters params_ = {0};
        float k_ = 0.f;
        // returns the energy of mass of the pendulum in the reference frame moving with cart
        // (normalized so E = 0 at top)
        float get_pendulum_energy_inertial_frame(const simulation::PendulumState& state)
        {
            static constexpr float g = 9.81;
            auto [M, m, l] = params_;
            auto [x, xdot, theta, omega] = state;

            return 0.5f * m * l * l * omega * omega + m * g * l * (cosf(theta) - 1);
        }
    };

}  // namespace control
