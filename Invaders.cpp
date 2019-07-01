#include "Invaders.h"



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

void Invaders::update() {
	animation.update();
	invader.setTextureRect(animation.uvRect);
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
