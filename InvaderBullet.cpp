#include "InvaderBullet.h"

#include "MoreInfo.h"


InvaderBullet::InvaderBullet() {
	texture.loadFromFile("res/images/SIBullet.png");
	sf::Vector2<unsigned> individualCharacter = texture.getSize();
	individualCharacter.x /= 1;
	individualCharacter.y /= 1;

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	bullet.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
	bullet.setScale(1 * 1.5, 1 * 1.5);
}

void InvaderBullet::renderTo(sf::RenderWindow & window) {
	window.draw(bullet);
}

void InvaderBullet::setBulletPos(sf::Vector2<float> newPos) {
	bullet.setPosition(newPos);
}

void InvaderBullet::moveTo(sf::Vector2<float> distance) {
	bullet.move(distance);
}

int InvaderBullet::getX() {
	return bullet.getPosition().x;
}

int InvaderBullet::getY() {
	return bullet.getPosition().y;
}

sf::FloatRect InvaderBullet::getGlobalBounds() {
	return bullet.getGlobalBounds();
}

bool InvaderBullet::collisionWithPlayer(Player* player) {
	if (getGlobalBounds().intersects(player->getGlobalBounds())) {
		return true;
	}
	return false;
}

bool InvaderBullet::collisionWithShield(Shield* shield) {
	if (getGlobalBounds().intersects(shield->getGlobalBounds())) {
		return true;
	}
	return false;
}
