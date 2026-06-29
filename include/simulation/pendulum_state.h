#pragma once

namespace simulation {

    struct PendulumState {
        float cart_position;
        float cart_velocity;
        float theta;
        float omega;
    };

} // namespace simulation