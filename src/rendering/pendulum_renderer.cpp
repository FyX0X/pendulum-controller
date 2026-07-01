#include "rendering/pendulum_renderer.h"

#include "math/vector.h"

namespace rendering
{

    PendulumRenderer::PendulumRenderer() :
        mass_(0.1f),
        cart_(sf::Vector2f(2.f, .2f)),
        line_(sf::PrimitiveType::Lines, 2)
    {
        mass_.setFillColor(sf::Color::White);
        mass_.setOrigin({0.1f, 0.1f});
        cart_.setFillColor(sf::Color::Red);
        cart_.setOrigin({1.f, 0.1f});
    }

    void PendulumRenderer::draw(simulation::Pendulum& pendulum, sf::RenderWindow& window)
    {
        // Implementation for drawing the pendulum
        math::Vec2 cart_position = pendulum.getCartPosition();
        math::Vec2 pendulum_position = pendulum.getPendulumPosition();

        sf::Vector2f cart_pos_sf(cart_position[0], cart_position[1]);
        sf::Vector2f pendulum_pos_sf(pendulum_position[0], pendulum_position[1]);

        cart_.setPosition(cart_pos_sf);
        mass_.setPosition(pendulum_pos_sf);
        line_[0].position = cart_pos_sf;
        line_[1].position = pendulum_pos_sf;

        window.draw(cart_);
        window.draw(mass_);
        window.draw(line_);
    }

}  // namespace rendering
