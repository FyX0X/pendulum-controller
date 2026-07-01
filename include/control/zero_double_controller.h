#pragma once
#include "double_controller.h"

namespace control {

    class ZeroDoubleController : public DoubleController {
    public:
        float computeForce(const simulation::DoublePendulumState& state, float dt) override {
            return 0.f;
        }
    };

} // namespace control