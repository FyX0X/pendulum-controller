#pragma once

#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

#include "control/controller.h"
#include "mlp.h"

namespace control::ai
{
    class NeuralController : public Controller
    {
    public:
        NeuralController(const std::filesystem::path& policy_path)
        {
            mlp_ = PendulumMLP::load_policy(policy_path);
        }

        float computeForce(const simulation::PendulumState& state, float dt) override
        {
            return mlp_.forward(std::array<float, 4>({state.cart_position, state.cart_velocity, state.theta, state.omega}))[0];
        }

    private:
        PendulumMLP mlp_{};
    };
}  // namespace control::ai
