#include "Player.h"

#include "MoreInfo.h"


Player::Player() {
	texture.loadFromFile("res/images/SIPlayer.png");
	sf::Vector2<unsigned> playerChar = texture.getSize();
	playerChar.x /= 1;
	playerChar.y /= 1;

	player.setTexture(texture);
	player.setTextureRect(sf::IntRect(playerChar.x * 0, playerChar.y * 0, playerChar.x, playerChar.y));
	player.setOrigin(playerChar.x / 2, playerChar.y / 2);
}

void Player::renderTo(sf::RenderWindow& window) {
	window.draw(player);
}

void Player::setPlayerPos(sf::Vector2<float> newPos) {
	player.setPosition(newPos);
}

void Player::moveTo(sf::Vector2<float> distance) {
	player.move(distance);
}

int Player::getX() {
	return player.getPosition().x;
}

int Player::getY() {
	return player.getPosition().y;
}

void Player::updateBorderBounds() {
	if (getX() <= screenWidth * 0) { setPlayerPos(sf::Vector2<float>(getX() + playerBorderSpeed, getY())); } //Left Side
	if (getX() >= screenWidth)	   { setPlayerPos(sf::Vector2<float>(getX() - playerBorderSpeed, getY())); } //Right Side
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}
