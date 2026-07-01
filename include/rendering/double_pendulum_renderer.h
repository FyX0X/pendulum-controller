#pragma once
#include <SFML/Graphics.hpp>

#include "simulation/double_pendulum.h"


namespace rendering
{

    class DoublePendulumRenderer
    {
    public:
        DoublePendulumRenderer();
        void draw(simulation::DoublePendulum& double_pendulum, sf::RenderWindow& window);

    private:
        sf::CircleShape mass1_;
        sf::CircleShape mass2_;
        sf::RectangleShape cart_;
        sf::VertexArray line1_;
        sf::VertexArray line2_;
    };

}  // namespace rendering
