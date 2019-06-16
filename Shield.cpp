#include "Shield.h"



Shield::Shield() {
	texture.loadFromFile("res/images/SIShield.png");
	sf::Vector2<unsigned> shieldChar = texture.getSize();
	shieldChar.x /= 1;
	shieldChar.y /= 1;

	shield.setTexture(texture);
	shield.setTextureRect(sf::IntRect(shieldChar.x * 0, shieldChar.y * 0, shieldChar.x, shieldChar.y));
	shield.setOrigin(shieldChar.x / 2, shieldChar.y);
}

void Shield::renderTo(sf::RenderWindow& window) {
	window.draw(shield);
}

void Shield::setShieldPos(sf::Vector2<float> newPos) {
	shield.setPosition(newPos);
}

int Shield::getX() {
	return shield.getPosition().x;
}

int Shield::getY() {
	return shield.getPosition().y;
}

sf::FloatRect Shield::getGlobalBounds() {
	return shield.getGlobalBounds();
}

void Shield::shieldProtection(int num) {
	shieldProtectionAccount -= num;
}

int Shield::shieldProtectionNum() {
	return shieldProtectionAccount;
}

