#pragma once

#include <cassert>
#include "double_controller.h"


static constexpr simulation::DoublePendulumParameters kAllowedParameters = { 1.f, 0.5f, 0.5f, 1.f, 1.f };


namespace control {

    class LQRDoubleController : public DoubleController {
    public:
        LQRDoubleController(const simulation::DoublePendulumParameters& params) {
            assert(params == kAllowedParameters);
        }
        float computeForce(const simulation::DoublePendulumState& state, float dt) override {
            return - K.dot(state.to_vec());
        }
    private:
        math::Vec<6> K = { -1.f, -2.54999051f, -41.70452522f, -11.68284606f , 0.f, 0.f};
    };

} // namespace control