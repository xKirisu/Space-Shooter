#ifndef _SS_Enemy
#define _SS_Enemy

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	enum EnemyType {
		ALAN, BONBON, LIPS, ENEMIES_COUNT
	};
	class Enemy : public Ship {

		static float enemiesSpawnCollector;
		static float enemiesSpawnBreak;
		static std::unordered_map<EnemyType, Enemy> enemies_prefabs;
		static std::vector<Enemy> enemies;

		static sf::Vector2f *spawnPoints;
		static int spawnCount;

	public:
		Enemy();
		Enemy(sf::Vector2f position, sf::Texture &texture, float move_speed, float shoot_speed, int hp);

		void action(float& tick, float& time);

		static void initEnemies(sf::Texture& enemy1, sf::Texture& enemy2, sf::Texture& enemy3, sf::Vector2f spawn_points[], int count);
		static void spawnEnemy(float& tick);
		static std::vector<Enemy>& getEnemies();

	};

}
#endif