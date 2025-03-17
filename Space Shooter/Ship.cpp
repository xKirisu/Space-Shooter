#include "Ship.hpp"
#include "Global.hpp"
#include "Explosion.hpp"

ss::Ship::Ship() : sprite(EMPTY_TEXTURE)
{

}

ss::Ship::Ship(sf::Vector2f position, sf::Texture& texture) : sprite(texture)
{
	sprite.setTextureRect(RECT_BASE);
	sprite.setScale(sf::Vector2f(ss::SCALE, ss::SCALE));
	sprite.setPosition(position);
}

void ss::Ship::checkCollide(Bullet& bullet)
{
	sf::FloatRect own_collider = sprite.getGlobalBounds();

	if (own_collider.findIntersection(bullet.getCollider())) {
		
		Bullet::removeBullet(bullet);

		healthPoints -= 1;

		if (healthPoints <= 0) {
			die();
		}
	}
}

void ss::Ship::die()
{
	Explosion::spawnExplosion(sprite.getPosition());
}

void ss::Ship::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
