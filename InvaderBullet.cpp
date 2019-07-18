#include "InvaderBullet.h"

#include "MoreInfo.h"


InvaderBullet::InvaderBullet(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: animation(texture, imageCount, switchTime) {

	bullet.setTexture(*texture);
	bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);
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
	animation.update();
	bullet.setTextureRect(animation.uvRect);

	if (getY() >= GROUND_HEIGHT + 10) { setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

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

bool InvaderBullet::collisionWithPlayer(const Player& player) {
	if (getGlobalBounds().intersects(player.getGlobalBounds())) {
		return true;
	}
	return false;
}

bool InvaderBullet::collisionWithShield(const Shield& shield) {
	if (getGlobalBounds().intersects(shield.getGlobalBounds())) {
		return true;
	}
	return false;
}
