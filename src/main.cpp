#include <SFML/Graphics.hpp>
#include "simulation/pendulum.h"
#include "rendering/pendulum_renderer.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "Pendulum Controller" );
	window.setFramerateLimit(60); // call it once after creating the window


	simulation::Pendulum pendulum( 1.0, 1.0, 0.5 );
	pendulum.set_state( 0.0, 0.0, 3.14 / 4.0 * 3.0, 0.0 );

	rendering::PendulumRenderer renderer;

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		// Update the pendulum state
		pendulum.update( 0.0, 1.0 / 60.0 );


		window.clear();
		renderer.draw( pendulum, window );
		window.display();
	}
}
