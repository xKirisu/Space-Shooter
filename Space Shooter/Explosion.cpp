#include "Explosion.hpp"
#include <iostream>

namespace ss{
	int Explosion::animationMaxWidth = SIZE*4;
	Explosion Explosion::explosionPrefab;
	std::vector<Explosion> Explosion::explosions;


	Explosion::Explosion() : sprite(EMPTY_TEXTURE)
	{
	}

	Explosion::Explosion(sf::Texture& texture) : sprite(texture)
	{
		animationTickCollector = 0;
		animationSwapTime = 0.25f;
		animationMaxWidth = texture.getSize().x;

		animationRect.position = sf::Vector2i(0, 0);
		animationRect.size = sf::Vector2i(SIZE, SIZE);
		sprite.setTextureRect(animationRect);
		sprite.setScale(sf::Vector2f(SCALE, SCALE));
	}

	void Explosion::initExplosion(sf::Texture& texture)
	{
		explosionPrefab = Explosion(texture);
	}
	void Explosion::spawnExplosion(sf::Vector2f position)
	{
		explosions.push_back(explosionPrefab);
		explosions.back().sprite.setPosition(position);
	}

	void Explosion::actionExplosion(float& tick)
	{
		for (Explosion& explosion : explosions) {
			explosion.animationTickCollector += tick;

			if (explosion.animationTickCollector > explosion.animationSwapTime) {
				explosion.animationRect.position.x += SIZE;
				explosion.sprite.setTextureRect(explosion.animationRect);
				explosion.animationTickCollector = 0;
			}
		}
	}

	void Explosion::drawExplosion(sf::RenderWindow& window)
	{
		for (Explosion& explosion : explosions) {
			window.draw(explosion.sprite);
		}
	}

	void Explosion::removeExplosion()
	{

		for (size_t i = 0; i < Explosion::explosions.size(); ) {
			if (explosions[i].animationRect.position.x > Explosion::animationMaxWidth) {
				std::swap(explosions[i], explosions.back());
				explosions.pop_back();
			}
			else {
				++i;
			}
		}

	}
}