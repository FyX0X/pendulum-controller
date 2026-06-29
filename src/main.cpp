#include <SFML/Graphics.hpp>
#include <cmath>

#include "simulation/pendulum.h"
#include "rendering/pendulum_renderer.h"
#include "control/manual_controller.h"


static constexpr float kMaxForce = 10.f;


int main()
{
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "Pendulum Controller" );
	window.setFramerateLimit(60); // call it once after creating the window


	simulation::Pendulum pendulum( 1.0, 1.0, 0.5 );
	pendulum.set_state( 0.0, 0.0, 3.14 / 4.0 * 3.0, 0.0 );

	rendering::PendulumRenderer renderer;

	std::unique_ptr<control::Controller> controller = std::make_unique<control::ManualController>();

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		// check for user input
		float force = controller->compute_force(pendulum.get_state());
		force = std::clamp(force, -kMaxForce, kMaxForce);
		pendulum.add_force(force);


		// Update the pendulum state
		pendulum.update( 1.0 / 60.0 );


		window.clear();
		renderer.draw( pendulum, window );
		window.display();
	}
}
