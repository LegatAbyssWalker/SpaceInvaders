#include "UFO.h"



UFO::UFO() {
	texture.loadFromFile("res/images/SIUFO.png");
	sf::Vector2<unsigned> UFOChar = texture.getSize();
	UFOChar.x /= 1;
	UFOChar.y /= 1;

	ufo.setTexture(texture);
	ufo.setTextureRect(sf::IntRect(UFOChar.x * 0, UFOChar.y * 0, UFOChar.x, UFOChar.y));
	ufo.setOrigin(UFOChar.x / 2, UFOChar.y / 2);
	ufo.scale(1 * 1.5, 1 * 1.5);
}

void UFO::renderTo(sf::RenderWindow& window) {
	window.draw(ufo);
}

void UFO::setUFOPos(sf::Vector2<float> newPos) {
	ufo.setPosition(newPos);
}

void UFO::moveTo(sf::Vector2<float> distance) {
	ufo.move(distance);
}

int UFO::getX() {
	return ufo.getPosition().x;
}

int UFO::getY() {
	return ufo.getPosition().y; 
}

sf::FloatRect UFO::getGlobalBounds() {
	return ufo.getGlobalBounds();
}

bool UFO::isOnScreen(sf::RenderWindow& window) {
	if (getX() >= window.getSize().x || getX() <= window.getSize().x * 0) {
		return false;
	}
	return true;
}
