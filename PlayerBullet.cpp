#include "PlayerBullet.h"

#include "MoreInfo.h"

PlayerBullet::PlayerBullet() {
	texture.loadFromFile(PLAYER_BULLET_T);
	sf::Vector2<unsigned> individualCharacter = texture.getSize();

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(individualCharacter.x * 0, individualCharacter.y * 0, individualCharacter.x, individualCharacter.y));
	bullet.setOrigin(individualCharacter.x / 2, individualCharacter.y / 2);
	bullet.setScale(1 * 2, 1 * 2);
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

void PlayerBullet::updateBullet(bool isBulletFiring, int bulletSpeed, int playerX, int playerY) {
	//Border bounds
	if (getY() <= SCREEN_HEIGHT * 0) { setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); bullet.move(sf::Vector2<float>(0, 0)); }


	//Updating shooting
	sf::Vector2<float> pBulletMovement(0.f, 0.f);
	pBulletMovement.y -= bulletSpeed;

	if (isBulletFiring) {
		if (getX() == BULLET_ORIGIN) {
			setBulletPos(sf::Vector2<float>(playerX, playerY));
			playSound.setSound(SHOOTING_FX, 25, false);
		}
	}
	moveTo(pBulletMovement);
}

int PlayerBullet::getX() {
	return bullet.getPosition().x;
}

int PlayerBullet::getY() {
	return bullet.getPosition().y;
}

sf::FloatRect PlayerBullet::getGlobalBounds() const {
	return bullet.getGlobalBounds();
}

bool PlayerBullet::collisionWithInvaders(Invaders& invaders) {
	if (getGlobalBounds().intersects(invaders.getGlobalBounds())) {
		return true;
	}
	return false;
}

bool PlayerBullet::collisionWithShield(Shield& shield) {
	if (getGlobalBounds().intersects(shield.getGlobalBounds())) {
		return true;
	}
	return false;
}

bool PlayerBullet::collisionWithUFO(UFO& ufo) {
	if (getGlobalBounds().intersects(ufo.getGlobalBounds())) {
		return true;
	}
	return false;
}
