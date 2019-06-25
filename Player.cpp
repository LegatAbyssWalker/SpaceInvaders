#include "Player.h"

#include "MoreInfo.h"


Player::Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

	this->speed = speed;
	row = 0;
	isFacingRight = true;

	player.setTexture(*texture);
}

void Player::renderTo(sf::RenderWindow& window) {
	window.draw(player);
}

void Player::setPlayerPos(sf::Vector2<float> newPos) {
	player.setPosition(newPos);
}

void Player::updatePlayer(float dt) {
	sf::Vector2<float> playerMovement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { playerMovement.x -= speed; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { playerMovement.x += speed; }
	if (playerMovement.x == 0.0f) { row = 0; }

	else {
		row = 1;

		if (playerMovement.x > 0.0f) { isFacingRight = false; }
		else { isFacingRight = true; }
	}

	animation.update(row, dt, isFacingRight);
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
	if (getX() <= screenWidth * 0) { setPlayerPos(sf::Vector2<float>(getX() + playerBorderSpeed, getY())); } //Left Side
	if (getX() >= screenWidth)	   { setPlayerPos(sf::Vector2<float>(getX() - playerBorderSpeed, getY())); } //Right Side
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}

bool Player::collisionWithInvaderBullet(InvaderBullet* invaderBullet) {
	if (getGlobalBounds().intersects(invaderBullet->getGlobalBounds())) {
		return true;
	}
	return false;
}
