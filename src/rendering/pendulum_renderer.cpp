#include "rendering/pendulum_renderer.h"
#include "math/vector.h"

namespace rendering {

    PendulumRenderer::PendulumRenderer() :
        mass_(10.f),
        cart_(sf::Vector2f(200.f, 20.f)),
        line_(sf::PrimitiveType::Lines, 2)
    {
        mass_.setFillColor(sf::Color::White);
        mass_.setOrigin({ 10.f, 10.f });
        cart_.setFillColor(sf::Color::Red);
        cart_.setOrigin({ 100.f, 10.f });
    }

    void PendulumRenderer::draw(simulation::Pendulum& pendulum, sf::RenderWindow& window) {
        // Implementation for drawing the pendulum
        math::Vec2 cart_position = pendulum.get_cart_position();
        math::Vec2 pendulum_position = pendulum.get_pendulum_position();

        sf::Vector2f cart_pos_sf(cart_position[0], cart_position[1]);
        sf::Vector2f pendulum_pos_sf(pendulum_position[0], pendulum_position[1]);
        cart_pos_sf *= 100.f; // scale for better visibility
        pendulum_pos_sf *= 100.f;

        sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

        cart_.setPosition(center + cart_pos_sf);
        mass_.setPosition(center + pendulum_pos_sf);
        line_[0].position = center + cart_pos_sf;
        line_[1].position = center + pendulum_pos_sf;

        window.draw(cart_);
        window.draw(mass_);
        window.draw(line_);
    }

}