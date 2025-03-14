#ifndef _SS_Enemy
#define _SS_Enemy

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	class Enemy : public Ship {

		static std::vector<Enemy> enemies;



		std::vector<Enemy> getEnemies();

	};

}
#endif