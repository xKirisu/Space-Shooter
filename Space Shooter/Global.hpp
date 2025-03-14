#ifndef _SS_Global
#define _SS_Global

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace ss {

	constexpr int WIN_WIDTH = 1100;
	constexpr int WIN_HEIGHT = 800;

	constexpr int SCALE = 4;
	constexpr int SIZE = 16;

	constexpr sf::IntRect RECT_BASE(sf::Vector2i(0,0), sf::Vector2i(SIZE, SIZE));
	static sf::Texture EMPTY_TEXTURE("data/textures/empty.png");
}

#endif // !_SS_Global
