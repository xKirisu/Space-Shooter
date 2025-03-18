#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Explosion.hpp"
#include "Score.hpp"

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

    sf::Texture explosion_texture("data/textures/explosion.png");

    sf::Texture background_texture("data/textures/background.png");
    background_texture.setRepeated(true);

    sf::Texture lifepoint_texture("data/textures/life_icon.png");

    // Objects Base
    bool gameOver = false;
    bool startGame = false;

    // Background
    sf::IntRect background_size(sf::Vector2i(0, 0), sf::Vector2i(ss::WIN_WIDTH, ss::WIN_HEIGHT));
    sf::Sprite background(background_texture);
    background.setTextureRect(background_size);

    // Life Points
    sf::Vector2f life_point_start_position = sf::Vector2f(ss::WIN_WIDTH - 3*ss::SIZE*ss::SCALE, ss::WIN_HEIGHT - ss::SCALE*ss::SIZE);
    sf::Sprite life_point(lifepoint_texture);
    life_point.setScale(sf::Vector2f(ss::SCALE, ss::SCALE));

    // Score
    std::string high_score = "Highscore: "+ std::to_string(ss::Score::getHighScore());
    std::string score_string = "Score: " + std::to_string(ss::Score::getScore());
    std::string title_string = "Space Shooter";

    sf::Font title_font("data/fonts/Boldreel.ttf");
    //sf::Font title_font("data/fonts/Boldreel.ttf");

    sf::Text score_text(title_font);
    sf::Text highscore_text(title_font);
    sf::Text game_over_text(title_font);

    sf::Text title_text(title_font);

    sf::Vector2f highscore_position = sf::Vector2f(ss::SIZE, ss::WIN_HEIGHT - ss::SIZE * ss::SCALE + ss::SIZE);
    sf::Vector2f score_position = sf::Vector2f(ss::SIZE, ss::WIN_HEIGHT - ss::SIZE * ss::SCALE*1.5 + ss::SIZE);

    sf::Vector2f title_position = sf::Vector2f(ss::WIN_WIDTH / 10, ss::WIN_HEIGHT / 5);

    score_text.setCharacterSize(24);
    score_text.setString(score_string);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(score_position);

    highscore_text.setCharacterSize(24);
    highscore_text.setString(high_score);
    highscore_text.setFillColor(sf::Color::White);
    highscore_text.setPosition(highscore_position);

    title_text.setCharacterSize(125);
    title_text.setString(title_string);
    title_text.setFillColor(sf::Color::Yellow);
    title_text.setPosition(title_position);

    game_over_text.setCharacterSize(125);
    game_over_text.setString("Game Over");
    game_over_text.setFillColor(sf::Color::Red);
    game_over_text.setPosition(title_position);



    // Objects
    ss::Score::initScore();

    ss::Explosion::initExplosion(explosion_texture);
    ss::Bullet::initBullet(player_bullet_texture, enemy_bullet_texture);

    sf::Vector2f spawn_points[] = {
        sf::Vector2f(0, 0), 
        sf::Vector2f(ss::WIN_WIDTH - ss::SIZE*ss::SCALE, ss::SIZE), 
        sf::Vector2f(0, ss::SIZE*2),
         sf::Vector2f(ss::WIN_WIDTH - ss::SIZE * ss::SCALE, ss::SIZE*2)
    };
    ss::Enemy::initEnemies(enemy1_texture, enemy2_texture, enemy3_texture, spawn_points, 4);

    sf::Vector2f player_start_position = sf::Vector2f(ss::WIN_WIDTH/2 - ss::SIZE*ss::SCALE/2 + ss::SIZE, ss::WIN_HEIGHT/2 + ss::SIZE * ss::SCALE*3);
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
                if (!gameOver) {
                    player.getEvent(*keyPressed);
                }


                if (!startGame) {
                    startGame = true;
                }
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

        if (!gameOver) {

            if (player.getLifes() <= 0) {
                gameOver = true;
            }

            if (startGame) {
                ss::Enemy::spawnEnemy(tick);
            }

            for (ss::Enemy& enemy : ss::Enemy::getEnemies()) {
                enemy.action(tick, time);
            }

        }

        for (ss::Bullet& bullet : ss::Bullet::getBullets()) {
            bullet.action(tick);
        }
        
        ss::Explosion::removeExplosion();
        ss::Explosion::actionExplosion(tick);

        score_string = "Score: " + std::to_string(ss::Score::getScore());
        score_text.setString(score_string);

        // Draw
        window.clear();
        window.draw(background);

        for (ss::Enemy& enemy : ss::Enemy::getEnemies()) {
            enemy.draw(window);
        }

        for (ss::Bullet& bullet : ss::Bullet::getBullets()) {
            bullet.draw(window);
        }

        if (gameOver) {
            window.draw(game_over_text);
        }
        else {
            player.draw(window);
        }
        

        ss::Explosion::drawExplosion(window);

        // Draw ui
        for (int i = 0; i < player.getLifes(); i++) {
            life_point.setPosition(life_point_start_position + sf::Vector2f(i * ss::SCALE * ss::SIZE, 0));
            window.draw(life_point);
        }

        window.draw(highscore_text);
        window.draw(score_text);

        if (!startGame) {
            window.draw(title_text);
        }
        
        window.display();
    }
}
