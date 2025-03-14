#ifndef _SS_Player
#define _SS_Player

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	class Player : public Ship {
	private:
		int healthPoints = 3;
		bool moveUp = false, moveDown = false;

		float animationBoosters = 0.75;
		//sf::Sprite boosters;

	public:
		Player(sf::Vector2f position, sf::Texture& texture);
		void getEvent(sf::Event::KeyPressed keypress);
		void getEvent(sf::Event::KeyReleased keyreleased);
		void action(float& tick);
	};

}

#endif // !
