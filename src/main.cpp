#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

#include "control/controllers.h"
#include "rendering/double_pendulum_renderer.h"
#include "rendering/pendulum_renderer.h"
#include "simulation/double_pendulum.h"
#include "simulation/pendulum.h"

#define DOUBLE true

static constexpr float kMaxForce = 10.f;
static constexpr float kCameraSpeed = 1.f;

static constexpr unsigned int kWidth = 800;
static constexpr unsigned int kHeight = 600;
static constexpr float kWorldWidth = 4.f;
static constexpr float kWorldHeight = 3.f;

#if DOUBLE
static constexpr simulation::DoublePendulumState kDefaultState = {0.f, 0.f, 0.01f, 0.f, 0.f, 0.f};
#else
static constexpr simulation::PendulumState kDefaultState = {0.0, 0.0, 3.14, 0.0};
#endif


void setupAxis(sf::VertexArray& x_axis, sf::VertexArray& y_axis);
void updateCamera(sf::RenderWindow& window, sf::View& view, float mouse_scroll, float dt);

sf::VertexArray force_shape{sf::PrimitiveType::Lines, 2};

int main()
{
    sf::RenderWindow window(sf::VideoMode({kWidth, kHeight}), "Pendulum Controller");
    window.setFramerateLimit(60);  // call it once after creating the window

    // view aka camera
    sf::View view(sf::FloatRect({0.f, 0.f}, {kWorldWidth, kWorldHeight}));
    view.setCenter({0.f, 0.f});
    view.zoom(2);
    window.setView(view);

    // axis
    sf::VertexArray x_axis, y_axis;
    setupAxis(x_axis, y_axis);

    // timestep
    float dt = 1.0 / 60.0;


// simulation
#if DOUBLE
    rendering::DoublePendulumRenderer renderer;
    simulation::DoublePendulum pendulum(1.f, 0.5f, 0.5f, 1.f, 1.f);

    std::unique_ptr<control::DoubleController> manual_controller = std::make_unique<control::ManualDoubleController>();
    std::unique_ptr<control::DoubleController> controller = std::make_unique<control::LQRDoubleController>(pendulum.getParameters());
#else
    rendering::PendulumRenderer renderer;
    simulation::Pendulum pendulum(1.0, 0.5, 1.f);

    std::unique_ptr<control::Controller> manual_controller = std::make_unique<control::ManualController>();
    std::unique_ptr<control::Controller> controller = std::make_unique<control::FullController>(pendulum.getParameters(), 20.f);
#endif

    pendulum.setState(kDefaultState);

    while (window.isOpen()) {
        float mouse_scroll = 0;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* mouse_wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (mouse_wheel_scrolled->wheel == sf::Mouse::Wheel::Vertical) {
                    mouse_scroll = mouse_wheel_scrolled->delta;
                }
            } else if (const auto* key_press = event->getIf<sf::Event::KeyPressed>()) {
                if (key_press->scancode == sf::Keyboard::Scancode::Space) {
                    pendulum.setState(kDefaultState);
                }
            }
        }

        // check for user input
        updateCamera(window, view, mouse_scroll, dt);

        // control the system
        float override_control = manual_controller->computeForce(pendulum.getState(), dt);
        float force = override_control != 0.f ? override_control : controller->computeForce(pendulum.getState(), dt);
        force = std::clamp(force, -kMaxForce, kMaxForce);
        pendulum.addForce(force);

        // Update the pendulum state
        pendulum.update(dt);

        // rendering
        window.clear();
        window.draw(x_axis);
        window.draw(y_axis);
        renderer.draw(pendulum, window);
        window.display();
    }
}

void setupAxis(sf::VertexArray& x_axis, sf::VertexArray& y_axis)
{
    sf::Color gray{};
    gray.r = 64;
    gray.g = 64;
    gray.b = 64;

    x_axis = sf::VertexArray(sf::PrimitiveType::Lines, 2);
    y_axis = sf::VertexArray(sf::PrimitiveType::Lines, 2);

    x_axis[0].position = {-kWorldWidth, 0.f};
    x_axis[1].position = {kWorldWidth, 0.f};
    x_axis[0].color = gray;
    x_axis[1].color = gray;

    y_axis[0].position = {0.f, -kWorldHeight};
    y_axis[1].position = {0.f, kWorldHeight};
    y_axis[0].color = gray;
    y_axis[1].color = gray;
}

void updateCamera(sf::RenderWindow& window, sf::View& view, float mouse_scroll, float dt)
{
    view.zoom(1.f - mouse_scroll * 0.1f);

    sf::Vector2f displacement = {0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        displacement.y -= kCameraSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        displacement.y += kCameraSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        displacement.x -= kCameraSpeed * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        displacement.x += kCameraSpeed * dt;
    }
    // scale displacement when zoomed
    float scale = view.getSize().x;
    view.move(displacement * scale);
    window.setView(view);
}
