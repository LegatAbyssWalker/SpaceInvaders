#include "PlayerBullet.h"

#include "MoreInfo.h"

PlayerBullet::PlayerBullet() {
	texture.loadFromFile(bulletT);
	sf::Vector2<unsigned> individualCharacter = texture.getSize();

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	bullet.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
}


void PlayerBullet::renderTo(sf::RenderWindow & window) {
	window.draw(bullet);
}

void PlayerBullet::setBulletPos(sf::Vector2<float> newPos) {
	bullet.setPosition(newPos);
}

void PlayerBullet::moveTo(sf::Vector2<float> distance) {
	bullet.move(distance);
}

int PlayerBullet::getX() {
	return bullet.getPosition().x;
}

int PlayerBullet::getY() {
	return bullet.getPosition().y;
}

sf::FloatRect PlayerBullet::getGlobalBounds() {
	return bullet.getGlobalBounds();
}

bool PlayerBullet::collisionWithInvaders(Invaders* invaders) {
	if (getGlobalBounds().intersects(invaders->getGlobalBounds())) {
		return true;
	}
	return false;
}

bool PlayerBullet::collisionWithShield(Shield* shield) {
	if (getGlobalBounds().intersects(shield->getGlobalBounds())) {
		return true;
	}
	return false;
}

bool PlayerBullet::collisionWithUFO(UFO* ufo) {
	if (getGlobalBounds().intersects(ufo->getGlobalBounds())) {
		return true;
	}
	return false;
}
