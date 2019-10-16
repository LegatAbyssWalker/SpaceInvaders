#include "PlayerBullet.h"

#include "MoreInfo.h"

PlayerBullet::PlayerBullet(sf::Texture& texture)
	: Entity(texture) {

	entity.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	entity.setScale(1 * 2, 1 * 2);
}

void PlayerBullet::update(bool isBulletFiring, int bulletSpeed, int playerX, int playerY) {
	//Border bounds
	if (getY() <= SKY_HEIGHT) { setPosition(sf::Vector2<float>(PLAYER_BULLET_ORIGIN, PLAYER_BULLET_ORIGIN)); entity.move(sf::Vector2<float>(0, 0)); }

	//Update shooting
	sf::Vector2<float> movement(0.f, 0.f);
	movement.y -= bulletSpeed;

	if (isBulletFiring) {
		if (getX() == PLAYER_BULLET_ORIGIN) {
			setPosition(sf::Vector2<float>(playerX, playerY));
			shootingFX.setSound(SHOOTING_FX, 20, false);
		}
	}
	entity.move(sf::Vector2<float>(movement));
}
