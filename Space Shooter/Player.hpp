#ifndef _SS_Player
#define _SS_Player

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	class Player : public Ship {
	private:

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

		void die() override;

		sf::Sound *shootSound;
		sf::Sound *deathSound;
		sf::Sound *hurtSound;

	public:
		Player(sf::Vector2f position, sf::Texture& texture, sf::Texture &boosters_main, sf::Texture &boosters_left, sf::Texture &boosters_right, sf::Sound &shoot_sound, sf::Sound& death_sound, sf::Sound& hurt_sound);
		void getEvent(sf::Event::KeyPressed keypress);
		void getEvent(sf::Event::KeyReleased keyreleased);
		void action(float& tick, float &time);
		void draw(sf::RenderWindow& window);
		int getLifes();
	};

}

#endif // !
