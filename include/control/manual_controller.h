#pragma once
#include "controller.h"

#include <SFML/Window/Keyboard.hpp>

namespace control {

    class ManualController : public Controller {
    public:
        float computeForce(const simulation::PendulumState& state, float dt) override {
            float force = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                force -= 10.0f; // apply force to the left
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                force += 10.0f; // apply force to the right
            }
            return force;
        }
    };

} // namespace control