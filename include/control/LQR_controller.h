#pragma once

#include <cassert>

#include "controller.h"
#include "math/vector.h"

namespace control
{

    class LQRController : public Controller
    {
    public:
        LQRController(const simulation::PendulumParameters& params) { assert(params == kAllowedParameters); }

        float computeForce(const simulation::PendulumState& state, float dt) override { return -K.dot(state.to_vec()); }

    private:
        static constexpr simulation::PendulumParameters kAllowedParameters = {1.f, 0.5f, 1.f};
        math::Vec4 K = {-1.f, -2.54999051f, -41.70452522f, -11.68284606f};
    };

}  // namespace control
