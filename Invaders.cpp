#include "Invaders.h"

#include "MoreInfo.h"

Invaders::Invaders(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

	this->speed = speed;

	invader.setTexture(*texture);
	invader.setOrigin(invader.getGlobalBounds().width / 2, invader.getGlobalBounds().height / 2);
}

void Invaders::renderTo(sf::RenderWindow& window) {
	window.draw(invader);
}

void Invaders::setInvaderPos(sf::Vector2<float> newPos) {
	invader.setPosition(newPos); 
}

void Invaders::update(int invaderSpeed) {
	//Animation
	animation.update();
	invader.setTextureRect(animation.uvRect);


	//Movements
	/*sf::Vector2<float> invaderMovement(0.f, 0.f);
	if (getX() <= SCREEN_WIDTH * 0) { isMovingLeft = false; isMovingRight = true; }
	if (getX() >= SCREEN_WIDTH)		{ isMovingLeft = true; isMovingRight = false; }

	if (isMovingLeft == false && isMovingRight == true) { invaderMovement.x += invaderSpeed; }
	if (isMovingLeft == true && isMovingRight == false) { invaderMovement.x -= invaderSpeed; }

	moveTo(invaderMovement);*/
}

void Invaders::moveTo(sf::Vector2<float> distance) {
	invader.move(distance);
}

int Invaders::getX() {
	return invader.getPosition().x;
}

int Invaders::getY() {
	return invader.getPosition().y;
}

sf::FloatRect Invaders::getGlobalBounds() {
	return invader.getGlobalBounds();
}
