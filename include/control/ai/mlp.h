#pragma once

#include <filesystem>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace control::ai
{

    template <int In, int Hidden, int Out>
    struct MLP {
        // W1: Hidden x In, b1: Hidden
        std::array<std::array<float, In>, Hidden> W1;
        std::array<float, Hidden> b1;
        // W2: Hidden x Hidden, b2: Hidden
        std::array<std::array<float, Hidden>, Hidden> W2;
        std::array<float, Hidden> b2;
        // W3: Out x Hidden, b3: Out
        std::array<std::array<float, Hidden>, Out> W3;
        std::array<float, Out> b3;

        std::array<float, Out> forward(const std::array<float, In>& x) const
        {
            auto h1 = tanh_layer<Hidden, In>(W1, b1, x);
            auto h2 = tanh_layer<Hidden, Hidden>(W2, b2, h1);
            return linear_layer<Out, Hidden>(W3, b3, h2);  // no activation on output
        }

        template <int OutN, int InN>
        static std::array<float, OutN> tanh_layer(
            const std::array<std::array<float, InN>, OutN>& W,
            const std::array<float, OutN>& b,
            const std::array<float, InN>& x)
        {
            std::array<float, OutN> out;
            for (int i = 0; i < OutN; i++) {
                float sum = b[i];
                for (int j = 0; j < InN; j++) {
                    sum += W[i][j] * x[j];
                }
                out[i] = std::tanh(sum);
            }
            return out;
        }

        template <int OutN, int InN>
        static std::array<float, OutN> linear_layer(
            const std::array<std::array<float, InN>, OutN>& W,
            const std::array<float, OutN>& b,
            const std::array<float, InN>& x)
        {
            std::array<float, OutN> out;
            for (int i = 0; i < OutN; i++) {
                float sum = b[i];
                for (int j = 0; j < InN; j++) {
                    sum += W[i][j] * x[j];
                }
                out[i] = sum;
            }
            return out;
        }


        static MLP load_policy(const std::filesystem::path& path)
        {
            std::ifstream f(path);

            json j = json::parse(f);

            MLP mlp;

            // validate sizes before loading
            assert(j["W1"].size() == Hidden);
            assert(j["W1"][0].size() == In);

            assert(j["W2"].size() == Hidden);
            assert(j["W2"][0].size() == Hidden);

            assert(j["W3"].size() == Out);
            assert(j["W3"][0].size() == Hidden);

            // W1
            for (int i = 0; i < Hidden; i++) {
                mlp.b1[i] = j["b1"][i];
                for (int k = 0; k < In; k++)
                    mlp.W1[i][k] = j["W1"][i][k];
            }

            // W2
            for (int i = 0; i < Hidden; i++) {
                mlp.b2[i] = j["b2"][i];
                for (int k = 0; k < Hidden; k++)
                    mlp.W2[i][k] = j["W2"][i][k];
            }

            // W3
            for (int i = 0; i < Out; i++) {
                mlp.b2[i] = j["b3"][i];
                for (int k = 0; k < Hidden; k++)
                    mlp.W3[i][k] = j["W3"][i][k];
            }

            return mlp;
        }
    };

    // instantiated with exact sizes from Python output
    using PendulumMLP = MLP<5, 64, 1>;


}  // namespace control::ai
