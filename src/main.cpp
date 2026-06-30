#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "simulation/pendulum.h"
#include "rendering/pendulum_renderer.h"
#include "control/manual_controller.h"


static constexpr float kMaxForce = 10.f;
static constexpr float kCameraSpeed = 1.f;


void update_camera(sf::RenderWindow &window, sf::View &view, float dt);


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
	pendulum.set_state( 0.0, 0.0, 3.14 / 4.0 * 3.0, 0.0 );

	float dt = 1.0 / 60.0;

	// control
	std::unique_ptr<control::Controller> controller = std::make_unique<control::ManualController>();

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}
		
		// check for user input
		update_camera(window, view, dt);

		// control the system
		float force = controller->compute_force(pendulum.get_state(), dt);
		force = std::clamp(force, -kMaxForce, kMaxForce);
		pendulum.add_force(force);


		// Update the pendulum state
		pendulum.update(dt);


		window.clear();
		window.draw(x_axis);
		window.draw(y_axis);
		renderer.draw( pendulum, window );
		window.display();
	}
}


void update_camera(sf::RenderWindow& window, sf::View &view, float dt) {
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
	view.move(displacement);
	window.setView(view);
}
