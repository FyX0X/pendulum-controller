#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "simulation/pendulum.h"
#include "rendering/pendulum_renderer.h"
#include "control/controllers.h"


static constexpr float kMaxForce = 10.f;
static constexpr float kCameraSpeed = 1.f;


void updateCamera(sf::RenderWindow &window, sf::View &view, float mouse_scroll, float dt);


int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	sf::RenderWindow window( sf::VideoMode( { width, height } ), "Pendulum Controller" );
	window.setFramerateLimit(60); // call it once after creating the window

	// view aka camera 
	float world_width = 4.f;
	float world_height = 3.f;
	sf::View view(sf::FloatRect({0.f, 0.f}, {world_width, world_height}));
	view.setCenter({0.f, 0.f});
	window.setView(view);

	// axis
	sf::Color gray{};
	gray.r = 64;
	gray.g = 64;
	gray.b = 64;
	sf::VertexArray x_axis(sf::PrimitiveType::Lines, 2);
	sf::VertexArray y_axis(sf::PrimitiveType::Lines, 2);

	x_axis[0].position = {-world_width, 0.f};
	x_axis[1].position = {world_width, 0.f};
	x_axis[0].color = gray;
	x_axis[1].color = gray;

	y_axis[0].position = {0.f, -world_height};
	y_axis[1].position = {0.f, world_height};
	y_axis[0].color = gray;
	y_axis[1].color = gray;

	rendering::PendulumRenderer renderer;

	// simulation
	simulation::Pendulum pendulum( 1.0, 1.0, 0.5 );
	pendulum.setState( 0.0, 0.0, 0.01, 0.0 );

	float dt = 1.0 / 60.0;

	// control
	std::unique_ptr<control::Controller> manual_controller = std::make_unique<control::ManualController>();
	// std::unique_ptr<control::Controller> controller = std::make_unique<control::PIDController>(50.f, 0.f, 0.f);
	std::unique_ptr<control::Controller> controller = std::make_unique<control::LQRController>();

	while ( window.isOpen() )
	{
		float mouse_scroll = 0;
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ) {
				window.close();
			}
			else if (const auto* mouse_wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
				if (mouse_wheel_scrolled->wheel == sf::Mouse::Wheel::Vertical) {
					mouse_scroll = mouse_wheel_scrolled->delta;
				}
			}
		}
		
		// check for user input
		updateCamera(window, view, mouse_scroll, dt);

		// control the system
		float force = controller->computeForce(pendulum.getState(), dt);
		force += manual_controller->computeForce(pendulum.getState(), dt);
		force = std::clamp(force, -kMaxForce, kMaxForce);
		pendulum.addForce(force);


		// Update the pendulum state
		pendulum.update(dt);


		window.clear();
		window.draw(x_axis);
		window.draw(y_axis);
		renderer.draw( pendulum, window );
		window.display();
	}
}


void updateCamera(sf::RenderWindow& window, sf::View &view, float mouse_scroll, float dt) {
	view.zoom(1.f - mouse_scroll * 0.1f);

	sf::Vector2f displacement = { 0.f, 0.f };
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
