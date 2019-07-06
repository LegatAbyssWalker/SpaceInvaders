#include "InvaderBullet.h"

#include "MoreInfo.h"


InvaderBullet::InvaderBullet() {
	texture.loadFromFile(bulletT);
	sf::Vector2<unsigned> individualCharacter = texture.getSize();
	
	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	bullet.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
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

void InvaderBullet::updateBullet() {
	if (getY() >= SCREEN_HEIGHT)	 { setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }
	if (getY() <= SCREEN_HEIGHT * 0) { setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

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
