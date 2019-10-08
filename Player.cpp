#include "Player.h"

#include "MoreInfo.h"


Player::Player(sf::Texture& texture, float speed) 
	: Entity(texture), speed(speed),
	playerLivesText(100, SCREEN_HEIGHT - 50, 25, SPACEINVADERS_FONT, sf::Color(255, 255, 255)) {

	entity.setOrigin(entity.getGlobalBounds().width / 2, entity.getGlobalBounds().height / 2);
	entity.setScale(1 * 1.2, 1 * 1.2);
}

void Player::keyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::A) { left = isPressed; }
	if (key == sf::Keyboard::D) { right = isPressed; }
}

void Player::updatePlayer() {
	//Movement/Animation
	sf::Vector2<float> movement(0.f, 0.f);
	if      (left)  { movement.x -= speed; }
	else if (right) { movement.x += speed; }

	entity.move(sf::Vector2<float>(movement));
}

void Player::updateLives(int lives) {
	playerLivesText.updateOText("Lives: ", lives);
}

void Player::updateBorderBounds() {
	//Entity cannot go through the borders of the screen
	if (getX() <= SCREEN_WIDTH * 0) { setPosition(sf::Vector2<float>(getX() + PLAYER_SPEED, getY())); } //Left Side
	if (getX() >= SCREEN_WIDTH)		{ setPosition(sf::Vector2<float>(getX() - PLAYER_SPEED, getY())); } //Right Side
}

void Player::extraRenderTo(sf::RenderWindow& window) {
	window.draw(entity);
	playerLivesText.renderTo(window);
}

