#pragma once
#include <SFML/Graphics.hpp>

#include "simulation/pendulum.h"


namespace rendering
{

    class PendulumRenderer
    {
    public:
        PendulumRenderer();
        void draw(simulation::Pendulum& pendulum, sf::RenderWindow& window);

    private:
        sf::CircleShape mass_;
        sf::RectangleShape cart_;
        sf::VertexArray line_;
        sf::VertexArray force_;
    };

}  // namespace rendering
