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
		float moveSpeed;
		
	public:

		Bullet();
		Bullet(sf::Texture& texture);

		sf::FloatRect getCollider();

		void action(float& tick);
		void draw(sf::RenderWindow& window);

		BulletType getType();

		static void initBullet(sf::Texture &player_bullet_texture, sf::Texture &enemy_bullet_texture);
		static void spawnBullet(BulletType type, sf::Vector2f position);

		static void removeBullet(Bullet& bullet);

		static std::vector<Bullet>& getBullets();
	};

}

#endif // !_SS_Bullet
