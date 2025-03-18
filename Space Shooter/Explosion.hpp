#ifndef _SS_Explosion

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Global.hpp"

namespace ss {
	class Explosion {

		float animationTickCollector;
		float animationSwapTime;
		static int animationMaxWidth;

		static Explosion explosionPrefab;
		sf::Sprite sprite;
		sf::IntRect animationRect;

		static std::vector<Explosion> explosions;

	public:
		Explosion();
		Explosion(sf::Texture& texture);

		static void initExplosion(sf::Texture& texture);

		static void spawnExplosion(sf::Vector2f position);
		static void actionExplosion(float& tick);
		static void drawExplosion(sf::RenderWindow& window);
		static void removeExplosion();
	};

}


#endif // !_SS_Explosion
