#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "Entity.h"
#include "State.h"
#include "MoreInfo.h"
#include "Sound.h"


class PlayerBullet : public Entity {
	public:
		PlayerBullet(sf::Texture& texture);
		
		void update(bool isBulletFiring, int bulletSpeed, int playerX, int playerY);

	private:
		Sound shootingFX;
};

#endif