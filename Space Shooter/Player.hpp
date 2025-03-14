#ifndef _SS_Player
#define _SS_Player

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	class Player : public Ship {
	private:
		int healthPoints = 3;
		bool moveUp = false, moveDown = false;

		

		sf::Sprite boosters;
		sf::Vector2f boosters_offset;
		sf::IntRect boosters_rect;

		sf::Texture *textureBoostersMain;
		sf::Texture *textureBoostersLeft;
		sf::Texture *textureBoostersRight;

		float animationTickCollectorBoosters;
		float animationSwapTimeBoosters;
		void playAnimationBoosters(float& tick);

	public:
		Player(sf::Vector2f position, sf::Texture& texture, sf::Texture &boosters_main, sf::Texture &boosters_left, sf::Texture &boosters_right);
		void getEvent(sf::Event::KeyPressed keypress);
		void getEvent(sf::Event::KeyReleased keyreleased);
		void action(float& tick, float &time);
		void draw(sf::RenderWindow& window);
	};

}

#endif // !
