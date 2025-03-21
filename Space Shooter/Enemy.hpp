#ifndef _SS_Enemy
#define _SS_Enemy

#include <SFML/Graphics.hpp>
#include "Ship.hpp"

namespace ss {

	enum EnemyType {
		ALAN, BONBON, LIPS, ENEMIES_COUNT
	};
	class Enemy : public Ship {

		static int enemiesIfMinimumBooser;
		static float enemiesSpawnCollector;
		static float enemiesSpawnBreak;
		static std::unordered_map<EnemyType, Enemy> enemies_prefabs;
		static std::vector<Enemy> enemies;

		static sf::Vector2f *spawnPoints;
		static int spawnCount;

		float shootRandomize;

		sf::IntRect animationRect;
		float animationTickCollector;
		static float animationSwapTime;
		int animationMaxWidth;

		int giveScore;


		static sf::Sound* shootSound;
		static sf::Sound* deathSound;

	public:
		Enemy();
		Enemy(sf::Texture &texture, float move_speed, float shoot_speed, int hp, int give_score, int animation_max_width);

		void action(float& tick, float& time);

		static void initEnemies(sf::Texture& enemy1, sf::Texture& enemy2, sf::Texture& enemy3, sf::Vector2f spawn_points[], int count, sf::Sound& shoot_sound, sf::Sound& death_sound);
		static void spawnEnemy(float& tick);


		static std::vector<Enemy>& getEnemies();

		void die() override;
	};

}
#endif