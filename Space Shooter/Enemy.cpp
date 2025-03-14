#include "Enemy.hpp"


std::unordered_map<ss::EnemyType, ss::Enemy> ss::Enemy::enemies_prefabs;
std::vector<ss::Enemy> ss::Enemy::enemies;

ss::Enemy::Enemy()
{

}

ss::Enemy::Enemy(sf::Vector2f position, sf::Texture& texture, float move_speed, float shoot_speed, int hp) : Ship(position, texture)
{

}

void ss::Enemy::action(float& tick, float& time)
{

}

void ss::Enemy::initalizeEnemies(sf::Texture& enemy1, sf::Texture& enemy2, sf::Texture& enemy3)
{
    sf::Vector2f position = sf::Vector2f(0, 0);
    enemies_prefabs[EnemyType::ALAN] = Enemy(position, enemy1, 25, 0.75, 2);
    enemies_prefabs[EnemyType::BONBON] = Enemy(position, enemy2, 45, 1.75, 3);
    enemies_prefabs[EnemyType::LIPS] = Enemy(position, enemy3, 15, 1.95, 1);
}

void ss::Enemy::spawnEnemy(sf::Vector2f spawn_points[], int count)
{
    int random_position = std::rand() & count;
    sf::Vector2f position = spawn_points[random_position];

    EnemyType type = EnemyType::ALAN;

    enemies.push_back(enemies_prefabs[type]);
    enemies[enemies.size() - 1].sprite.setPosition(position);
}

std::vector<ss::Enemy> ss::Enemy::getEnemies()
{
    return enemies;
}
