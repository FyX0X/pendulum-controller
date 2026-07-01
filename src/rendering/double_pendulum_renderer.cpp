#include "rendering/double_pendulum_renderer.h"
#include "math/vector.h"

namespace rendering {

    DoublePendulumRenderer::DoublePendulumRenderer() :
        mass1_(0.1f),
        mass2_(0.1f),
        cart_(sf::Vector2f(1.f, .2f)),
        line1_(sf::PrimitiveType::Lines, 2),
        line2_(sf::PrimitiveType::Lines, 2)
    {
        mass1_.setFillColor(sf::Color::White);
        mass1_.setOrigin({ 0.1f, 0.1f });
        mass2_.setFillColor(sf::Color::White);
        mass2_.setOrigin({ 0.1f, 0.1f });
        cart_.setFillColor(sf::Color::Red);
        cart_.setOrigin({ 0.5f, 0.1f });
    }

    void DoublePendulumRenderer::draw(simulation::DoublePendulum& double_pendulum, sf::RenderWindow& window) {
        // Implementation for drawing the pendulum
        math::Vec2 cart_position = double_pendulum.getCartPosition();
        math::Vec2 mass1_position = double_pendulum.getFirstMassPosition();
        math::Vec2 mass2_position = double_pendulum.getSecondMassPosition();

        sf::Vector2f cart_pos_sf(cart_position[0], cart_position[1]);
        sf::Vector2f mass1_pos_sf(mass1_position[0], mass1_position[1]);
        sf::Vector2f mass2_pos_sf(mass2_position[0], mass2_position[1]);

        cart_.setPosition(cart_pos_sf);

        mass1_.setPosition(mass1_pos_sf);
        mass2_.setPosition(mass2_pos_sf);
        
        line1_[0].position = cart_pos_sf;
        line1_[1].position = mass1_pos_sf;

        line2_[0].position = mass1_pos_sf;
        line2_[1].position = mass2_pos_sf;

        window.draw(cart_);
        window.draw(mass1_);
        window.draw(mass2_);
        window.draw(line1_);
        window.draw(line2_);
    }

}