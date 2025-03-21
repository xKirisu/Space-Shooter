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
    
    // Init score
    ss::Score::initScore();

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

    // Load sounds and sounds
    sf::Music music("data/sounds/xcreenplay__retro-playground.wav");
    music.setVolume(2);
    music.setLooping(true);
    music.play();

    sf::SoundBuffer buff_death_sound("data/sounds/etheraudio__retro-death.wav");
    sf::Sound death_sound(buff_death_sound);
    death_sound.setVolume(2);

    sf::SoundBuffer buff_hurt_sound("data/sounds/cabled_mess__hurt_c_03.wav");
    sf::Sound hurt_sound(buff_hurt_sound);
    hurt_sound.setVolume(4);


    sf::SoundBuffer buff_enemy_death_sound("data/sounds/jalastram__sfx_explosion_04.wav");
    sf::Sound enemy_death_sound(buff_enemy_death_sound);
    enemy_death_sound.setVolume(4);

    sf::SoundBuffer buff_enemy_shoot_sound("data/sounds/greyfeather__retro-mouse-sound.wav");
    sf::Sound enemy_shoot_sound(buff_enemy_shoot_sound);
    enemy_shoot_sound.setVolume(2);

    sf::SoundBuffer buff_shoot_sound("data/sounds/matrixxx__retro-laser-shot-04.wav");
    sf::Sound shoot_sound(buff_shoot_sound);
    shoot_sound.setVolume(2);



    // Objects Base //FLAGS//
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

    sf::Text score_text(title_font);
    sf::Text highscore_text(title_font);
    sf::Text game_over_text(title_font);
    sf::Text new_record(title_font);

    sf::Text title_text(title_font);

    sf::Vector2f highscore_position = sf::Vector2f(ss::SIZE, ss::WIN_HEIGHT - ss::SIZE * ss::SCALE + ss::SIZE);
    sf::Vector2f score_position = sf::Vector2f(ss::SIZE, ss::WIN_HEIGHT - ss::SIZE * ss::SCALE*1.5 + ss::SIZE);

    sf::Vector2f title_position = sf::Vector2f(ss::WIN_WIDTH / 10, ss::WIN_HEIGHT / 5);
    sf::Vector2f gameover_position = sf::Vector2f(ss::WIN_WIDTH / 5, ss::WIN_HEIGHT / 5);
    sf::Vector2f new_record_position = sf::Vector2f(ss::WIN_WIDTH / 4, ss::WIN_HEIGHT * 0.65);

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
    game_over_text.setPosition(gameover_position);

    new_record.setCharacterSize(96);
    new_record.setString("New Record");
    new_record.setFillColor(sf::Color::Yellow);
    new_record.setPosition(new_record_position);


    // Objects

    ss::Explosion::initExplosion(explosion_texture);
    ss::Bullet::initBullet(player_bullet_texture, enemy_bullet_texture);

    sf::Vector2f spawn_points[] = {
        sf::Vector2f(0, 0), 
        sf::Vector2f(ss::WIN_WIDTH - ss::SIZE*ss::SCALE, ss::SIZE), 
        sf::Vector2f(0, ss::SIZE*ss::SCALE * 2),
         sf::Vector2f(ss::WIN_WIDTH - ss::SIZE * ss::SCALE, ss::SIZE * ss::SCALE * 2)
    };
    ss::Enemy::initEnemies(enemy1_texture, enemy2_texture, enemy3_texture, spawn_points, 4, enemy_shoot_sound, enemy_death_sound);

    sf::Vector2f player_start_position = sf::Vector2f(ss::WIN_WIDTH/2 - ss::SIZE*ss::SCALE/2 + ss::SIZE, ss::WIN_HEIGHT/2 + ss::SIZE * ss::SCALE*3);
    ss::Player player(player_start_position, player_texture, boosters_texture, boosters_left_texture, boosters_right_texture, shoot_sound, death_sound, hurt_sound);


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
                ss::Score::saveHighScore();
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

            if (ss::Score::getScore() > ss::Score::getHighScore()) {
                window.draw(new_record);
            }
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
