#include "Enemy.hpp"
#include "Global.hpp"
#include "Bullet.hpp"
#include "Explosion.hpp"
#include "Score.hpp"
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

ss::Enemy::Enemy(sf::Texture& texture, float move_speed, float shoot_speed, int hp, int give_score, int animation_max_width) : Ship(sf::Vector2f(0,0), texture)
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

    giveScore = give_score;
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
                                            //prefab, movespeed, shootspeed, lives, score, animation
    enemies_prefabs[EnemyType::ALAN] = Enemy(enemy1, 65, 0.75, 2, 10, enemy1.getSize().x);
    enemies_prefabs[EnemyType::BONBON] = Enemy(enemy2, 85, 1.55, 3, 20, enemy2.getSize().x);
    enemies_prefabs[EnemyType::LIPS] = Enemy(enemy3, 70, 1.85, 1, 30, enemy3.getSize().x);

    spawnPoints = spawn_points;
    spawnCount = count;

}

void ss::Enemy::spawnEnemy(float& tick)
{

    if (enemies.size() < enemiesIfMinimumBooser) {
        enemiesSpawnCollector += tick*3;
    }
    else {
        enemiesSpawnCollector += tick ;
    }

    if (enemiesSpawnCollector > enemiesSpawnBreak) {

        int random_position = std::rand() % spawnCount;
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
    Explosion::spawnExplosion(sprite.getPosition());

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [this](const Enemy& e) { return &e == this; }),
        enemies.end());

    ss::Score::giveScore(giveScore);
}

std::vector<ss::Enemy>& ss::Enemy::getEnemies()
{
    return enemies;
}


