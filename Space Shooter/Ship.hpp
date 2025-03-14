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

		sf::Vector2f shootOffset;
		float shootLastTime = 0;
		float shootSpeedTime = 0;
		bool isShoot = false;
	public:

		Ship();
		Ship(sf::Vector2f position, sf::Texture& texture);

		void shoot();

		// change object
		void action(float &tick, float&time);

		// draw object
		void draw(sf::RenderWindow &window);

	};

}

#endif // !
