#pragma once

#include <array>
#include <cassert>
#include <cmath>
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
            std::array<float, 5> observation = {state.cart_position,
                                                state.cart_velocity,
                                                cosf(state.theta),
                                                sinf(state.theta),
                                                state.omega};


            return mlp_.forward(observation)[0];
        }

    private:
        PendulumMLP mlp_{};
    };

}  // namespace control::ai
