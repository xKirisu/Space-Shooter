#include "Bullet.hpp"

std::unordered_map<ss::BulletType, ss::Bullet> ss::Bullet::bullets_prefabs;
std::vector<ss::Bullet> ss::Bullet::bullets;

void ss::Bullet::action(float& tick)
{
	switch (type)
	{
	case ss::PLAYER:
		sprite.move(sf::Vector2f(0, -moveSpeed * tick));
		break;
	case ss::ENEMY:
		sprite.move(sf::Vector2f(0, moveSpeed * tick));
		break;
	default:
		break;
	}
}

void ss::Bullet::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}


void ss::Bullet::initBullet(sf::Texture& player_bullet_texture, sf::Texture& enemy_bullet_texture)
{
	bullets_prefabs[BulletType::PLAYER] = Bullet(player_bullet_texture);
	bullets_prefabs[BulletType::ENEMY] = Bullet(enemy_bullet_texture);
}

void ss::Bullet::spawnBullet(BulletType type, sf::Vector2f position)
{
	bullets.push_back(bullets_prefabs[type]);
}
std::vector<ss::Bullet> ss::Bullet::getBullets()
{
	return bullets;
}
