#include "Invaders.h"

#include "MoreInfo.h"


Invaders::Invaders() {
	texture.loadFromFile("res/images/SIInvader.png");
	sf::Vector2<unsigned> individualCharacter = texture.getSize();
	individualCharacter.x /= 1;
	individualCharacter.y /= 1;

	invader.setTexture(texture);
	invader.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	invader.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
	invader.scale(1 * 1.5, 1 * 1.5);
}



void Invaders::renderTo(sf::RenderWindow& window) {
	window.draw(invader);
}

void Invaders::setInvaderPos(sf::Vector2<float> newPos) {
	invader.setPosition(newPos);
}

int Invaders::getX() {
	return invader.getPosition().x;
}

int Invaders::getY() {
	return invader.getPosition().y;
}

void Invaders::moveTo(sf::Vector2<float>(distance)) {
	invader.move(distance);
}

sf::FloatRect Invaders::getGlobalBounds() {
	return invader.getGlobalBounds();
}
