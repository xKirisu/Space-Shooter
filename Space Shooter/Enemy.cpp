#include "Enemy.hpp"

std::vector<ss::Enemy> ss::Enemy::enemies;

std::vector<ss::Enemy> ss::Enemy::getEnemies()
{
    return enemies;
}
