#pragma once

#include <cassert>

#include "double_controller.h"
#include "math/vector.h"


namespace control
{

    class LQRDoubleController : public DoubleController
    {
    public:
        LQRDoubleController(const simulation::DoublePendulumParameters& params)
        {
            assert(params == kAllowedParameters);
        }
        float computeForce(const simulation::DoublePendulumState& state, float dt) override
        {
            return -K.dot(state.to_vec());
        }

    private:
        static constexpr simulation::DoublePendulumParameters kAllowedParameters = {1.f, 0.5f, 0.5f, 1.f, 1.f};
        math::Vec<6> K = {1.f, 3.78963103f, -173.55130299f, -14.94810112f, 191.60489942f, 42.77882854f};
    };

}  // namespace control
