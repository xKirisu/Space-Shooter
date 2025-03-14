#include "Player.hpp"
#include "Global.hpp"

ss::Player::Player(sf::Vector2f position, sf::Texture& texture) : Ship(position, texture)
{
	moveSpeed = 65.5f;

	rect.position = sf::Vector2i(SIZE, 0);
	rect.size = sf::Vector2i(SIZE, SIZE);
	sprite.setTextureRect(rect);
}

void ss::Player::getEvent(sf::Event::KeyPressed keypress)
{
	if (keypress.scancode == sf::Keyboard::Scancode::W) {
		moveUp = true;
	}
	if (keypress.scancode == sf::Keyboard::Scancode::S) {
		moveDown = true;
	}
	if (keypress.scancode == sf::Keyboard::Scancode::A) {
		moveLeft = true;
	}
	if (keypress.scancode == sf::Keyboard::Scancode::D) {
		moveRight = true;
	}

}

void ss::Player::getEvent(sf::Event::KeyReleased keyreleased)
{
	if (keyreleased.scancode == sf::Keyboard::Scancode::W) {
		moveUp = false;
	}
	if (keyreleased.scancode == sf::Keyboard::Scancode::S) {
		moveDown = false;
	}
	if (keyreleased.scancode == sf::Keyboard::Scancode::A) {
		moveLeft = false;

		rect.position = sf::Vector2i(SIZE, 0);
		sprite.setTextureRect(rect);
	}
	if (keyreleased.scancode == sf::Keyboard::Scancode::D) {
		moveRight = false;

		rect.position = sf::Vector2i(SIZE, 0);
		sprite.setTextureRect(rect);
	}

}

void ss::Player::action(float& tick)
{
	if (moveLeft) {
		sprite.move(sf::Vector2f(-moveSpeed * tick, 0));

		rect.position = sf::Vector2i(0, 0);
		sprite.setTextureRect(rect);
	}
	if (moveRight) {
		sprite.move(sf::Vector2f(moveSpeed * tick, 0));

		rect.position = sf::Vector2i(2*SIZE, 0);
		sprite.setTextureRect(rect);
	}
	if (moveUp) {
		sprite.move(sf::Vector2f(0, -moveSpeed * tick));
	}
	if (moveDown) {
		sprite.move(sf::Vector2f(0, moveSpeed * tick));
	}
}
