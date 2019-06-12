#include "Player.h"

#include "MoreInfo.h"

Player::Player() {
	texture.loadFromFile("res/images/spaceInvadersSpriteSheet.png");
	sf::Vector2<unsigned> individualCharacter = texture.getSize();	
	individualCharacter.x /= 7;
	individualCharacter.y /= 6;

	player.setTexture(texture);
	player.setTextureRect(sf::IntRect(individualCharacter.x * 1.8, individualCharacter.y * 5, individualCharacter.x, individualCharacter.y));
	player.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
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
	if (getX() <= screenWidth * 0) { setPlayerPos(sf::Vector2<float>(getX() + playerBorderSpeed, getY())); } //Left
	if (getX() >= screenWidth)	   { setPlayerPos(sf::Vector2<float>(getX() - playerBorderSpeed, getY())); } //Right
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}