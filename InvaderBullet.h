#ifndef INVADERBULLET_H
#define INVADERBULLET_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Player.h"
#include "Shield.h"

#include <iostream>

class InvaderBullet {
	public:
		InvaderBullet();

		void renderTo(sf::RenderWindow& window); 
		void setBulletPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);
		void getX();
		void getY();
		sf::FloatRect getGlobalBounds();
		bool collisionWithPlayer(Player* player);
		bool collisionWithShield(Shield* shield);

	private:
		//SFML
		sf::Texture texture;
		sf::Sprite bullet;
		sf::Clock bulletClock;
		float bulletTimer;
};

#endif