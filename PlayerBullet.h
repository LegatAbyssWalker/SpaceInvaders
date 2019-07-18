#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "PlaySound.h"

#include "Invaders.h"
#include "Shield.h"
#include "UFO.h"

#include <iostream>

class PlayerBullet {
	public:
		PlayerBullet();
		
		void renderTo(sf::RenderWindow& window);
		void setBulletPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);  
		void updateBullet(bool isBulletFiring, int bulletSpeed, int playerX, int playerY);

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds() const;

		//Collisions
		bool collisionWithInvaders(Invaders& invaders);
		bool collisionWithShield(Shield& shield);
		bool collisionWithUFO(UFO& ufo);

	private:
		PlaySound playSound;

		sf::Texture texture;
		sf::Sprite bullet;
};

#endif