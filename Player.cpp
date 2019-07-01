#include "Player.h"

#include "MoreInfo.h"


Player::Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

	this->speed = speed;

	player.setTexture(*texture);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	player.setScale(1 * 1.2, 1 * 1.2);
}

void Player::renderTo(sf::RenderWindow& window) {
	window.draw(player);
}

void Player::setPlayerPos(sf::Vector2<float> newPos) {
	player.setPosition(newPos);
}

void Player::updatePlayer() {
	sf::Vector2<float> playerMovement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { playerMovement.x -= speed; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { playerMovement.x += speed; }
	
	animation.update();
	player.setTextureRect(animation.uvRect);
	player.move(playerMovement);
}


int Player::getX() {
	return player.getPosition().x;
}

int Player::getY() {
	return player.getPosition().y;
}

void Player::updateBorderBounds() {
	if (getX() <= SCREEN_WIDTH * 0) { setPlayerPos(sf::Vector2<float>(getX() + PLAYER_BORDER_SPEED, getY())); } //Left Side
	if (getX() >= SCREEN_WIDTH)	    { setPlayerPos(sf::Vector2<float>(getX() - PLAYER_BORDER_SPEED, getY())); } //Right Side
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}