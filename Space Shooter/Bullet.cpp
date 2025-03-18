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
	moveSpeed = 215;
	sprite.setScale(sf::Vector2f(SCALE, SCALE));
}

sf::FloatRect ss::Bullet::getCollider()
{
	return sprite.getGlobalBounds();
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
	
	if (sprite.getPosition().y > WIN_HEIGHT * 2 || sprite.getPosition().y < -WIN_HEIGHT) {
		removeBullet(*this);
	}
}

void ss::Bullet::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

ss::BulletType ss::Bullet::getType()
{
	return type;
}


void ss::Bullet::initBullet(sf::Texture& player_bullet_texture, sf::Texture& enemy_bullet_texture)
{
	bullets_prefabs[BulletType::PLAYER] = Bullet(player_bullet_texture);
	bullets_prefabs[BulletType::ENEMY] = Bullet(enemy_bullet_texture);
}

void ss::Bullet::spawnBullet(BulletType type, sf::Vector2f position)
{
	Bullet bullet = bullets_prefabs[type];
	bullet.sprite.setPosition(position);
	bullet.type = type;

	bullets.push_back(bullet);
}
void ss::Bullet::removeBullet(Bullet& bullet)
{
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[&bullet](const Bullet& b) { return &b == &bullet; }),
		bullets.end());
}
std::vector<ss::Bullet>& ss::Bullet::getBullets()
{
	return bullets;
}

