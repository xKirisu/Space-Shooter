#include "Explosion.hpp"
#include <iostream>

int ss::Explosion::animationMaxWidth = ss::SIZE;
ss::Explosion ss::Explosion::explisionPrefab;
std::vector<ss::Explosion> ss::Explosion::explosions;


ss::Explosion::Explosion() : sprite(ss::EMPTY_TEXTURE)
{
}

ss::Explosion::Explosion(sf::Texture& texture) : sprite(texture)
{
	animationSwapTime = 2.0f;
	animationMaxWidth = texture.getSize().x;

	animationRect.position = sf::Vector2i(0, 0);
	animationRect.size = sf::Vector2i(ss::SIZE, ss::SIZE);
	sprite.setTextureRect(animationRect);
}

void ss::Explosion::initExplosion(sf::Texture& texture)
{
	explisionPrefab = Explosion(texture);
}
void ss::Explosion::spawnExplosion(sf::Vector2f position)
{
	explosions.push_back(explisionPrefab);
	explosions.back().sprite.setPosition(position);
}

void ss::Explosion::actionExplosion(float& tick)
{
	for (ss::Explosion& explosion : explosions) {
		explosion.animationTickCollector += tick;

		if (explosion.animationTickCollector > explosion.animationSwapTime) {
			explosion.animationRect.position.x += ss::SIZE;
			explosion.sprite.setTextureRect(explosion.animationRect);
		}
	}

	Explosion::removeExplosion();
}

void ss::Explosion::drawExplosion(sf::RenderWindow& window)
{
	for (ss::Explosion& explosion : explosions) {
		window.draw(explosion.sprite);
	}

	std::cout << explosions.size() << std::endl;
}

void ss::Explosion::removeExplosion()
{

	for (size_t i = 0; i < ss::Explosion::explosions.size(); ) {
		if (explosions[i].animationRect.position.x > Explosion::animationMaxWidth) {
			std::swap(explosions[i], explosions.back());
			explosions.pop_back();
		}
		else {
			++i;
		}
	}

}