#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

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
		void getX();
		void getY();
		sf::FloatRect getGlobalBounds();

		//Collisions
		bool collisionWithInvaders(Invaders* invaders);
		bool collisionWithShield(Shield* shield);
		bool collisionWithUFO(UFO* ufo);

	private:
		sf::Texture texture;
		sf::Sprite bullet;
};

#endif