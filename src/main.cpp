#include <SFML/Graphics.hpp>
#include "simulation/pendulum.h"
#include <cmath>


int main()
{
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "Pendulum Controller" );
	window.setFramerateLimit(60); // call it once after creating the window


	sf::CircleShape mass( 10.f );
	mass.setFillColor( sf::Color::Green );
	mass.setOrigin( { 10.f, 10.f } );

	sf::RectangleShape cart( sf::Vector2f( 200.f, 20.f ) );
	cart.setFillColor( sf::Color::Red );
	cart.setOrigin( {100.f, 10.f } );

	sf::VertexArray line (sf::PrimitiveType::Lines, 2);



	simulation::Pendulum pendulum( 1.0, 1.0, 0.5 );
	pendulum.set_state( 0.0, 0.0, 3.14 / 4.0 * 3.0, 0.0 );

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		// Update the pendulum state
		pendulum.update( 0.0, 1.0 / 60.0 );

		// Position shapes based on pendulum state
		double cart_position, cart_velocity, theta, omega;
		pendulum.get_state( cart_position, cart_velocity, theta, omega );

		sf::Vector2f cart_pos( 
			400.f + static_cast<float>( cart_position * 100.f ), 
			300.f 
		);
		sf::Vector2f mass_pos( 
			400.f + static_cast<float>( cart_position * 100.f ) + static_cast<float>( sin( theta ) * 100.f ), 
			300.f - static_cast<float>( cos( theta ) * 100.f ) );

		cart.setPosition( cart_pos );
		mass.setPosition( mass_pos );

		line[0].position = cart_pos;
		line[1].position = mass_pos;

		window.clear();
		window.draw( cart );
		window.draw( mass );
		window.draw( line );
		window.display();
	}
}
