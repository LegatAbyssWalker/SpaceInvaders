#include "PlayerBullet.h"



PlayerBullet::PlayerBullet() {
	texture.loadFromFile("res/images/SIBullet.png");
	sf::Vector2<unsigned> individualCharacter = texture.getSize();
	individualCharacter.x /= 1;
	individualCharacter.y /= 1;

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	bullet.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
	bullet.setScale(1 * 1.5, 1 * 1.5); 
}


void PlayerBullet::renderTo(sf::RenderWindow& window) {
	window.draw(bullet);
}

void PlayerBullet::setBulletPos(sf::Vector2<float> newPos) {
	bullet.setPosition(newPos);
}

void PlayerBullet::moveTo(sf::Vector2<float> distance) {
	bullet.move(distance);
}

void PlayerBullet::getX() {
	bullet.getPosition().x;
}

void PlayerBullet::getY() {
	bullet.getPosition().y;
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
