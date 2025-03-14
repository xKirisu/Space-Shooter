#ifndef _SS_Ship
#define _SS_Ship

#include <SFML/Graphics.hpp>

namespace ss {

	class Ship {
	protected:

		sf::Sprite sprite;
		sf::IntRect rect;

		float moveSpeed = 0;
		bool moveLeft = false, moveRight = false;

	public:

		Ship(sf::Vector2f position, sf::Texture& texture);

		void shoot();

		// change object
		void action(float &tick);

		// draw object
		void draw(sf::RenderWindow &window);

	};

}

#endif // !
