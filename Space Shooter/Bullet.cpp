#include "Bullet.hpp"
#include <iostream>

std::unordered_map<ss::BulletType, ss::Bullet> ss::Bullet::bullets_prefabs;
std::vector<ss::Bullet> ss::Bullet::bullets;

ss::Bullet::Bullet() :sprite(EMPTY_TEXTURE)
{
	sprite.setScale(sf::Vector2f(SCALE, SCALE));
}

ss::Bullet::Bullet(sf::Texture& texture) :sprite(texture)
{
	sprite.setScale(sf::Vector2f(SCALE, SCALE));
}

void ss::Bullet::action(float& tick)
{
	switch (type)
	{
	case ss::PLAYER:
		sprite.move(sf::Vector2f(0, -moveSpeed * tick));
		break;
	case ss::ENEMY:
		sprite.move(sf::Vector2f(0, moveSpeed * tick));
		sprite.setTextureRect(RECT_BASE);
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
	bullets[bullets.size() - 1].sprite.setPosition(position);
	bullets[bullets.size() - 1].type = type;
}
std::vector<ss::Bullet>& ss::Bullet::getBullets()
{
	return bullets;
}
