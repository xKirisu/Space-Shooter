#include "Enemy.hpp"
#include "Global.hpp"
#include "Bullet.hpp"
#include <iostream>

float ss::Enemy::enemiesSpawnCollector = 0;
float ss::Enemy::enemiesSpawnBreak = 2;

sf::Vector2f* ss::Enemy::spawnPoints;
int ss::Enemy::spawnCount;

std::unordered_map<ss::EnemyType, ss::Enemy> ss::Enemy::enemies_prefabs;
std::vector<ss::Enemy> ss::Enemy::enemies;

ss::Enemy::Enemy()
{

}

ss::Enemy::Enemy(sf::Vector2f position, sf::Texture& texture, float move_speed, float shoot_speed, int hp) : Ship(position, texture)
{
    shootSpeedTime = shoot_speed;
    std::rand() % 2 == 0 ? moveLeft = true : moveRight = true;
}

void ss::Enemy::action(float& tick, float& time)
{
    if (moveLeft) {
        sprite.move(sf::Vector2f(-moveSpeed * tick, 0));

        if (sprite.getPosition().x < 0) {
            moveLeft = false;
            moveRight = true;
        }

    }
    if (moveRight) {
        sprite.move(sf::Vector2f(moveSpeed * tick, 0));

        if (sprite.getPosition().x > WIN_WIDTH) {
            moveLeft = true;
            moveRight = false;
        }
    }

    if (time > shootLastTime + shootSpeedTime) {

        sf::Vector2f position = sprite.getPosition() + shootOffset;
        Bullet::spawnBullet(BulletType::ENEMY, position);
        shootLastTime = time;

    }
}

void ss::Enemy::initEnemies(sf::Texture& enemy1, sf::Texture& enemy2, sf::Texture& enemy3, sf::Vector2f spawn_points[], int count)
{
    sf::Vector2f position = sf::Vector2f(0, 0);
    enemies_prefabs[EnemyType::ALAN] = Enemy(position, enemy1, 35, 0.75, 2);
    enemies_prefabs[EnemyType::BONBON] = Enemy(position, enemy2, 45, 1.75, 3);
    enemies_prefabs[EnemyType::LIPS] = Enemy(position, enemy3, 25, 1.95, 1);

    spawnPoints = spawn_points;
    spawnCount = count;
}

void ss::Enemy::spawnEnemy(float& tick)
{
    enemiesSpawnCollector += tick;

    if (enemiesSpawnCollector > enemiesSpawnBreak) {

        int random_position = std::rand() & spawnCount;
        sf::Vector2f position = spawnPoints[random_position];

        int random_enemy = std::rand() % ENEMIES_COUNT;
        EnemyType type = static_cast<EnemyType>(random_enemy);

        enemies.push_back(enemies_prefabs[type]);
        enemies[enemies.size() - 1].sprite.setPosition(position);

        enemiesSpawnCollector = 0;
    }
}

std::vector<ss::Enemy>& ss::Enemy::getEnemies()
{
    return enemies;
}
