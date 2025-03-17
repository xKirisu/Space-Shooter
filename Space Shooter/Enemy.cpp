#include "Enemy.hpp"
#include "Global.hpp"
#include "Bullet.hpp"
#include "Explosion.hpp"
#include <iostream>

int ss::Enemy::enemiesIfMinimumBooser = 4;
float ss::Enemy::enemiesSpawnCollector = 0;
float ss::Enemy::enemiesSpawnBreak = 2;

sf::Vector2f* ss::Enemy::spawnPoints;
int ss::Enemy::spawnCount;

std::unordered_map<ss::EnemyType, ss::Enemy> ss::Enemy::enemies_prefabs;
std::vector<ss::Enemy> ss::Enemy::enemies;

float ss::Enemy::animationSwapTime = 0.92;

ss::Enemy::Enemy()
{

}

ss::Enemy::Enemy(sf::Vector2f position, sf::Texture& texture, float move_speed, float shoot_speed, int hp, int animation_max_width) : Ship(position, texture)
{
    moveSpeed = move_speed;
    shootSpeedTime = shoot_speed;
    healthPoints = hp;

    shootRandomize = std::rand() / RAND_MAX;

    std::rand() % 2 == 0 ? moveLeft = true : moveRight = true;

    animationTickCollector = 0;

    animationMaxWidth = animation_max_width;
    animationRect.size = sf::Vector2i(ss::SIZE, ss::SIZE);
    animationRect.position = sf::Vector2i(0, 0);
}

void ss::Enemy::action(float& tick, float& time)
{
    // Moving
    if (moveLeft) {
        sprite.move(sf::Vector2f(-moveSpeed * tick, 0));

        if (sprite.getPosition().x < 0) {
            moveLeft = false;
            moveRight = true;
        }

    }
    if (moveRight) {
        sprite.move(sf::Vector2f(moveSpeed * tick, 0));

        if (sprite.getPosition().x > WIN_WIDTH - ss::SIZE*ss::SCALE) {
            moveLeft = true;
            moveRight = false;
        }
    }

    // Shooting
    if (time > shootLastTime + shootSpeedTime + shootRandomize) {

        sf::Vector2f position = sprite.getPosition() + shootOffset;
        Bullet::spawnBullet(BulletType::ENEMY, position);
        shootLastTime = time;

        shootRandomize = std::rand() / RAND_MAX;

    }

    // Collider
    for (Bullet& bullet : Bullet::getBullets()) {
        if (bullet.getType() != BulletType::ENEMY) {
            checkCollide(bullet);
        }
    }

    // Animation
    animationTickCollector += tick;
    if (animationTickCollector > animationSwapTime) {

        animationTickCollector = 0;
        animationRect.position.x += ss::SIZE;

        if (animationRect.position.x >= animationMaxWidth) {
            animationRect.position.x = 0;
        }

        sprite.setTextureRect(animationRect);
    }

}

void ss::Enemy::initEnemies(sf::Texture& enemy1, sf::Texture& enemy2, sf::Texture& enemy3, sf::Vector2f spawn_points[], int count)
{
    sf::Vector2f position = sf::Vector2f(0, 0);
    enemies_prefabs[EnemyType::ALAN] = Enemy(position, enemy1, 55, 0.75, 2, enemy1.getSize().x);
    enemies_prefabs[EnemyType::BONBON] = Enemy(position, enemy2, 75, 1.75, 3, enemy2.getSize().x);
    enemies_prefabs[EnemyType::LIPS] = Enemy(position, enemy3, 65, 1.95, 1, enemy3.getSize().x);

    spawnPoints = spawn_points;
    spawnCount = count;

}

void ss::Enemy::spawnEnemy(float& tick)
{

    if (enemies.size() < enemiesIfMinimumBooser) {
        enemiesSpawnCollector += tick*2;
    }
    else {
        enemiesSpawnCollector += tick ;
    }

    if (enemiesSpawnCollector > enemiesSpawnBreak) {

        int random_position = std::rand() & spawnCount;
        sf::Vector2f position = spawnPoints[random_position];

        int random_enemy = std::rand() % ENEMIES_COUNT;
        EnemyType type = static_cast<EnemyType>(random_enemy);

        enemies.push_back(enemies_prefabs[type]);
        enemies.back().sprite.setPosition(position);

        enemiesSpawnCollector = 0;
    }
}

void ss::Enemy::die() 
{
    
}

std::vector<ss::Enemy>& ss::Enemy::getEnemies()
{
    return enemies;
}


