#ifndef _SS_Explosion

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Global.hpp"

class Explosion {

	float animationTickCollector;
	float animationSwapTime;

	static std::vector<Explosion> explosions;

public:
	Explosion();

	static void initExplosion();
	
	static void spawnExplosion();
	static void actionExplosion(float &tick);
	static void drawExplosion(sf::RenderWindow &app);
	static void removeExplosion();
};


#endif // !_SS_Explosion
