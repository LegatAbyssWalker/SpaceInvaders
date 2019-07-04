#include "Player.h"

#include "MoreInfo.h"



Player::Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

	this->speed = speed;

	player.setTexture(*texture);
	player.setOrigin(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2);
	player.setScale(1 * 1.2, 1 * 1.2);



	playerLivesText = new OStringText(SCREEN_WIDTH * 0 + 100, SCREEN_HEIGHT - 50, 25, spaceInvadersFont, sf::Color(255, 255, 255));
}

void Player::renderTo(sf::RenderWindow& window) {
	window.draw(player);

	this->playerLivesText->renderTo(window);
}

void Player::setPlayerPos(sf::Vector2<float> newPos) {
	player.setPosition(newPos);
}

void Player::updatePlayer() {
	//Movement/Animation
	sf::Vector2<float> playerMovement(0.f, 0.f);
	using Key = sf::Keyboard::Key;
	auto keyDown = [](sf::Keyboard::Key k) { return sf::Keyboard::isKeyPressed(k); };

	if (keyDown(Key::A)) { playerMovement.x -= speed; }
	if (keyDown(Key::D)) { playerMovement.x += speed; }

	
	animation.update();
	player.setTextureRect(animation.uvRect);
	player.move(playerMovement);
}

void Player::updateLives(int lives) {
	this->playerLivesText->updateOText("Lives: ", lives);
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