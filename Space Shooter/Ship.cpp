#include "Ship.hpp"
#include "Global.hpp"

ss::Ship::Ship(sf::Vector2f position, sf::Texture& texture) : sprite(texture)
{
	sprite.setTextureRect(RECT_BASE);
	sprite.setScale(sf::Vector2f(ss::SCALE, ss::SCALE));
	sprite.setPosition(position);
}

void ss::Ship::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
