#include "Bullet.hpp"
#include <iostream>
namespace ss{
	std::unordered_map<BulletType, Bullet> Bullet::bullets_prefabs;
	std::vector<Bullet> Bullet::bullets;

	Bullet::Bullet() :sprite(EMPTY_TEXTURE)
	{
		sprite.setScale(sf::Vector2f(SCALE, SCALE));
	}

	Bullet::Bullet(sf::Texture& texture) :sprite(texture)
	{
		moveSpeed = 215;
		sprite.setScale(sf::Vector2f(SCALE, SCALE));
	}

	sf::FloatRect Bullet::getCollider()
	{
		return sprite.getGlobalBounds();
	}

	void Bullet::action(float& tick)
	{
		switch (type)
		{
		case PLAYER:
			sprite.move(sf::Vector2f(0, -moveSpeed * tick));
			break;
		case ENEMY:
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

	void Bullet::draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	BulletType Bullet::getType()
	{
		return type;
	}


	void Bullet::initBullet(sf::Texture& player_bullet_texture, sf::Texture& enemy_bullet_texture)
	{
		bullets_prefabs[BulletType::PLAYER] = Bullet(player_bullet_texture);
		bullets_prefabs[BulletType::ENEMY] = Bullet(enemy_bullet_texture);
	}

	void Bullet::spawnBullet(BulletType type, sf::Vector2f position)
	{
		Bullet bullet = bullets_prefabs[type];
		bullet.sprite.setPosition(position);
		bullet.type = type;

		bullets.push_back(bullet);
	}
	void Bullet::removeBullet(Bullet& bullet)
	{
		bullets.erase(
			std::remove_if(bullets.begin(), bullets.end(),
				[&bullet](const Bullet& b) { return &b == &bullet; }),
			bullets.end());
	}
	std::vector<Bullet>& Bullet::getBullets()
	{
		return bullets;
	}

}