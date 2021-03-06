#include "Invader.h"


Invader::Invader(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: Entity(*texture), animation(texture, imageCount, switchTime) {

	entity.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void Invader::update() {
	//Animation
	animation.updateAnimation(false, true);
	entity.setTextureRect(animation.uvRect);

	//Updating death
	if (isOnScreen() == false) { setDead(); }
}

void Invader::move(sf::Vector2<float> distance) {
	entity.move(sf::Vector2<float>(distance));
}

void Invader::setType(Invader::InvaderType type) {
	this->type = type;

}

int Invader::returnPoints() const {
	if (type == Invader::InvaderType::crab)    { return Invader::InvaderType::crab; }
	if (type == Invader::InvaderType::octopus) { return Invader::InvaderType::octopus; }
	if (type == Invader::InvaderType::squid)   { return Invader::InvaderType::squid; }
}

void Invader::setDead() {
	isDead = true;
}

bool Invader::isInvaderDead() {
	if (isDead) {
		return true;
	}
	return false;
}

bool Invader::isOnScreen() {
	if (getX() >= 0 && getX() <= SCREEN_WIDTH + 100 && getY() >= 0 && getY() <= SCREEN_HEIGHT) {
		return true;
	}
	return false;
}
