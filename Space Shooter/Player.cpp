#include "Global.hpp"
#include "Player.hpp"
#include "Explosion.hpp"
#include "Bullet.hpp"
#include <iostream>

namespace ss
{

	void Player::playAnimationBoosters(float& tick)
	{
		animationTickCollectorBoosters += tick;

		if (animationTickCollectorBoosters >= animationSwapTimeBoosters) {

			animationTickCollectorBoosters = 0;

			if (boosters_rect.position.x == SIZE) {
				boosters_rect.position.x = 0;
			}
			else {
				boosters_rect.position.x = SIZE;
			}

			boosters.setTextureRect(boosters_rect);
		}
	}

	Player::Player(sf::Vector2f position, sf::Texture& texture, sf::Texture& boosters_main_texture, sf::Texture& boosters_left_texture, sf::Texture& boosters_right_texture, sf::Sound& shoot_sound, sf::Sound& death_sound, sf::Sound& hurt_sound) : Ship(position, texture), boosters(boosters_main_texture)
	{
		healthPoints = 3;
		moveSpeed = 185.5f;

		shootOffset = sf::Vector2f(0, -0.45);
		shootSpeedTime = 0.45f;

		rect.position = sf::Vector2i(SIZE, 0);
		rect.size = sf::Vector2i(SIZE, SIZE);
		sprite.setTextureRect(rect);


		// boosters
		textureBoostersMain = &boosters_main_texture;
		textureBoostersLeft = &boosters_left_texture;
		textureBoostersRight = &boosters_right_texture;

		boosters_rect.position = sf::Vector2i(0, 0);
		boosters_rect.size = sf::Vector2i(SIZE, SIZE);

		animationTickCollectorBoosters = 0;
		animationSwapTimeBoosters = 0.35f;

		boosters_offset = sf::Vector2f(0, SIZE * SCALE);
		boosters.setPosition(position + boosters_offset);
		boosters.setScale(sf::Vector2f(SCALE, SCALE));
		boosters.setTextureRect(boosters_rect);

		shootSound = &shoot_sound;
		deathSound = &death_sound;
		hurtSound = &hurt_sound;
	}

	void Player::getEvent(sf::Event::KeyPressed keypress)
	{
		if (keypress.scancode == sf::Keyboard::Scancode::W) {
			moveUp = true;
		}
		if (keypress.scancode == sf::Keyboard::Scancode::S) {
			moveDown = true;
		}
		if (keypress.scancode == sf::Keyboard::Scancode::A) {

			if (!moveLeft) {
				boosters.setTexture(*textureBoostersLeft);
			}

			moveLeft = true;
		}
		if (keypress.scancode == sf::Keyboard::Scancode::D) {

			if (!moveRight) {
				boosters.setTexture(*textureBoostersRight);
			}

			moveRight = true;
		}
		if (keypress.scancode == sf::Keyboard::Scancode::Space) {
			isShoot = true;
		}
	}

	void Player::getEvent(sf::Event::KeyReleased keyreleased)
	{
		if (keyreleased.scancode == sf::Keyboard::Scancode::W) {
			moveUp = false;
		}
		if (keyreleased.scancode == sf::Keyboard::Scancode::S) {
			moveDown = false;
		}
		if (keyreleased.scancode == sf::Keyboard::Scancode::A) {

			if (moveLeft) {
				boosters.setTexture(*textureBoostersMain);
			}

			moveLeft = false;

			rect.position = sf::Vector2i(SIZE, 0);
			sprite.setTextureRect(rect);
		}
		if (keyreleased.scancode == sf::Keyboard::Scancode::D) {

			if (moveRight) {
				boosters.setTexture(*textureBoostersMain);
			}

			moveRight = false;

			rect.position = sf::Vector2i(SIZE, 0);
			sprite.setTextureRect(rect);
		}
		if (keyreleased.scancode == sf::Keyboard::Scancode::Space) {
			isShoot = false;
		}
	}

	void Player::action(float& tick, float& time)
	{
		if (moveLeft) {
			sprite.move(sf::Vector2f(-moveSpeed * tick, 0));
			boosters.move(sf::Vector2f(-moveSpeed * tick, 0));

			rect.position = sf::Vector2i(0, 0);
			sprite.setTextureRect(rect);

			if (sprite.getPosition().x < 0) {
				sprite.move(sf::Vector2f(moveSpeed * tick, 0));
				boosters.move(sf::Vector2f(moveSpeed * tick, 0));
			}
		}
		if (moveRight) {
			sprite.move(sf::Vector2f(moveSpeed * tick, 0));
			boosters.move(sf::Vector2f(moveSpeed * tick, 0));

			rect.position = sf::Vector2i(2 * SIZE, 0);
			sprite.setTextureRect(rect);

			if (sprite.getPosition().x > WIN_WIDTH - SIZE * SCALE) {
				sprite.move(sf::Vector2f(-moveSpeed * tick, 0));
				boosters.move(sf::Vector2f(-moveSpeed * tick, 0));
			}

		}
		if (moveUp) {
			sprite.move(sf::Vector2f(0, -moveSpeed * tick));
			boosters.move(sf::Vector2f(0, -moveSpeed * tick));

			if (sprite.getPosition().y < 0) {

				sprite.move(sf::Vector2f(0, moveSpeed * tick));
				boosters.move(sf::Vector2f(0, moveSpeed * tick));

			}
		}
		if (moveDown) {
			sprite.move(sf::Vector2f(0, moveSpeed * tick));
			boosters.move(sf::Vector2f(0, moveSpeed * tick));

			if (sprite.getPosition().y > WIN_HEIGHT - SIZE * SCALE) {

				sprite.move(sf::Vector2f(0, -moveSpeed * tick));
				boosters.move(sf::Vector2f(0, -moveSpeed * tick));
			}
		}

		if (isShoot) {
			if (time > shootLastTime + shootSpeedTime) {

				shootSound->play();

				sf::Vector2f position = sprite.getPosition() + shootOffset;
				Bullet::spawnBullet(BulletType::PLAYER, position);
				shootLastTime = time;

			}
		}

		playAnimationBoosters(tick);

		if (healthPoints > 0) {
			for (Bullet& bullet : Bullet::getBullets()) {
				if (bullet.getType() != BulletType::PLAYER) {
					if (checkCollide(bullet)) {
						hurtSound->play();
					}
				}
			}
		}
	}
	void Player::die()
	{
		Explosion::spawnExplosion(sprite.getPosition());

		deathSound->play();
	}

	void Player::draw(sf::RenderWindow& window)
	{
		window.draw(boosters);

		Ship::draw(window);
	}

	int Player::getLifes()
	{
		return healthPoints;
	}

}