#pragma once
#include <SFML/Window/Keyboard.hpp>

#include "double_controller.h"

namespace control
{

    class ManualDoubleController : public DoubleController
    {
    public:
        float computeForce(const simulation::DoublePendulumState& state, float dt) override
        {
            float force = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                force -= 10.0f;  // apply force to the left
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                force += 10.0f;  // apply force to the right
            }
            return force;
        }
    };

}  // namespace control
