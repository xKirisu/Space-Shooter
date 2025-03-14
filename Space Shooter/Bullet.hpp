#ifndef _SS_Bullet
#define _SS_Bullet

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Global.hpp"

namespace ss {

	enum BulletType {
		PLAYER, ENEMY
	};

	class Bullet {
	private:
		
		BulletType type;
		sf::Sprite sprite;

		static std::unordered_map<BulletType, Bullet> bullets_prefabs;
		static std::vector<Bullet> bullets;
		float moveSpeed = 4;

	public:

		Bullet() :sprite(EMPTY_TEXTURE) {

		}
		Bullet(sf::Texture &texture) :sprite(texture) {
			
		}

		void action(float& tick);
		void draw(sf::RenderWindow& window);

		static void initBullet(sf::Texture &player_bullet_texture, sf::Texture &enemy_bullet_texture);
		static void spawnBullet(BulletType type, sf::Vector2f position);
		static std::vector<Bullet> getBullets();

	};

}

#endif // !_SS_Bullet
