#include "Invaders.h"



Invaders::Invaders() {
	texture.loadFromFile("res/images/SIInvader.png");
	sf::Vector2<unsigned> invaderChar = texture.getSize();
	invaderChar.x /= 1;
	invaderChar.y /= 1;

	invader.setTexture(texture);
	invader.setTextureRect(sf::IntRect(invaderChar.x * 0, invaderChar.y * 0, invaderChar.x, invaderChar.y));
	invader.setOrigin(invaderChar.x / 2, invaderChar.y / 2);
	invader.scale(1 * 1.5, 1 * 1.5);
}

void Invaders::renderTo(sf::RenderWindow& window) {
	window.draw(invader);
}

void Invaders::setInvaderPos(sf::Vector2<float> newPos) {
	invader.setPosition(newPos); 
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
