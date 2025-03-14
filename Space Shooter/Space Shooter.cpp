#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Bullet.hpp"
#include "Player.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ ss::WIN_WIDTH, ss::WIN_HEIGHT }), "Space Shooter");

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

    sf::Texture lifepoint_texture("data/textures/life_icon.png");

    // Objects Base
    sf::Vector2f background_size = sf::Vector2f(ss::WIN_WIDTH, ss::WIN_HEIGHT);
    sf::RectangleShape background(background_size);
    background.setTexture(&background_texture);



    // Objects
    ss::Bullet::initBullet(player_bullet_texture, enemy_bullet_texture);

    sf::Vector2f start_position = sf::Vector2f(32, 32);
    ss::Player player(start_position, player_texture);


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

        // Draw
        window.clear();
        window.draw(background);

        player.draw(window);

        for (ss::Bullet& bullet : ss::Bullet::getBullets()) {
            bullet.draw(window);
        }

        window.display();
    }
}
