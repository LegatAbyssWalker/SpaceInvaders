#include "Invaders.h"

#include "MoreInfo.h"

Invaders::Invaders(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

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
	//Animation
	animation.update();
	invader.setTextureRect(animation.uvRect);

	//Updating death
	if (getY() <= SCREEN_HEIGHT * 0) { setDead(); }
}

void Invaders::moveTo(sf::Vector2<float> distance) {
	invader.move(distance);
}

void Invaders::setType(std::string type) {
	this->type = type;
}

int Invaders::returnPointType() const {
	if (type == "crab")    { return crab; }
	if (type == "octopus") { return octopus; }
	if (type == "squid")   { return squid; }
}

void Invaders::setDead() {
	isDead = true;
}

bool Invaders::isInvaderDead() {
	if (isDead == true) {
		return true; 
	}
	return false;
}

int Invaders::getX() {
	return invader.getPosition().x;
}

int Invaders::getY() {
	return invader.getPosition().y;
}

sf::FloatRect Invaders::getGlobalBounds() const {
	return invader.getGlobalBounds();
}
