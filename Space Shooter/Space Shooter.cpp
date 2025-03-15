#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

int main()
{
    std::srand(time(NULL));


    sf::RenderWindow window(sf::VideoMode({ ss::WIN_WIDTH, ss::WIN_HEIGHT }), "Space Shooter");
    
    // Set Window Icon
    sf::Image icon("data/textures/icon.png");
    window.setIcon(icon);

    // Load Textures
    sf::Texture player_texture("data/textures/player.png");

    sf::Texture boosters_texture("data/textures/boosters.png");
    sf::Texture boosters_left_texture("data/textures/boosters_left.png");
    sf::Texture boosters_right_texture("data/textures/boosters_right.png");

    sf::Texture enemy1_texture("data/textures/enemy1_alan.png");
    sf::Texture enemy2_texture("data/textures/enemy2_bon_bon.png");
    sf::Texture enemy3_texture("data/textures/enemy3_lips.png");

    sf::Texture player_bullet_texture("data/textures/player_bullet.png");
    sf::Texture enemy_bullet_texture("data/textures/enemy_bullet.png");

    sf::Texture background_texture("data/textures/background.png");
    background_texture.setRepeated(true);

    sf::Texture lifepoint_texture("data/textures/life_icon.png");

    // Objects Base
    // Background
    sf::IntRect background_size(sf::Vector2i(0, 0), sf::Vector2i(ss::WIN_WIDTH, ss::WIN_HEIGHT));
    sf::Sprite background(background_texture);
    background.setTextureRect(background_size);



    // Life Points
    sf::Vector2f life_point_start_position = sf::Vector2f(ss::WIN_WIDTH - 3*ss::SIZE*ss::SCALE, ss::WIN_HEIGHT - ss::SCALE*ss::SIZE);
    sf::Sprite life_point(lifepoint_texture);
    life_point.setScale(sf::Vector2f(ss::SCALE, ss::SCALE));


    // Score
    int score = 0;
    std::string score_string = "Score: " + score;

    //sf::Font score_font("");
    //sf::Text score_text(score_font);

    //sf::Vector2f score_position = sf::Vector2f(ss::SIZE, ss::WIN_HEIGHT - ss::SIZE * ss::SCALE);

    //score_text.setCharacterSize(24);
    //score_text.setString(score_string);
    //score_text.setFillColor(sf::Color::White);
    //score_text.setPosition(score_position);



    // Objects
    ss::Bullet::initBullet(player_bullet_texture, enemy_bullet_texture);

    sf::Vector2f spawn_points[] = {
        sf::Vector2f(0, 0), 
        sf::Vector2f(ss::WIN_WIDTH - ss::SIZE*ss::SCALE, ss::SIZE), 
        sf::Vector2f(0, ss::SIZE*2),
         sf::Vector2f(ss::WIN_WIDTH - ss::SIZE * ss::SCALE, ss::SIZE*2)
    };
    ss::Enemy::initEnemies(enemy1_texture, enemy2_texture, enemy3_texture, spawn_points, 4);

    sf::Vector2f player_start_position = sf::Vector2f(32, 32);
    ss::Player player(player_start_position, player_texture, boosters_texture, boosters_left_texture, boosters_right_texture);


    // Ticks and Time
    sf::Clock timeglobal;
    sf::Clock tickrate;
    

    // Main loop
    while (window.isOpen())
    {
        // Events
        while (const std::optional event = window.pollEvent())
        {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                player.getEvent(*keyPressed);
            }
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                player.getEvent(*keyReleased);
            }

            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Actions
        float time = timeglobal.getElapsedTime().asSeconds();
        float tick = tickrate.restart().asSeconds();

        player.action(tick, time);

        ss::Enemy::spawnEnemy(tick);

        for (ss::Enemy& enemy : ss::Enemy::getEnemies()) {
            enemy.action(tick, time);
        }

        for (ss::Bullet& bullet : ss::Bullet::getBullets()) {
            bullet.action(tick);
        }

        // Draw
        window.clear();
        window.draw(background);

        for (ss::Enemy& enemy : ss::Enemy::getEnemies()) {
            enemy.draw(window);
        }

        for (ss::Bullet& bullet : ss::Bullet::getBullets()) {
            bullet.draw(window);
        }

        player.draw(window);

        // Draw ui
        for (int i = 0; i < player.getLifes(); i++) {
            life_point.setPosition(life_point_start_position + sf::Vector2f(i * ss::SCALE * ss::SIZE, 0));
            window.draw(life_point);
        }

        window.display();
    }
}
