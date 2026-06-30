#pragma once


#include "controller.h"
#include "math/vector.h"

namespace control {

    class LQRController : public Controller {
    public:
        LQRController() = default;

        float computeForce(const simulation::PendulumState& state, float dt) override {
            return - K.dot(state.to_vec());
        }

    private:
        simulation::PendulumParameters param_ = {0};

        math::Vec4 K = { -1.f, -2.54999051f, -41.70452522f, -11.68284606f };
    };

}