#ifndef INVADERBULLET_H
#define INVADERBULLET_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Shield.h"

#include <iostream>

class InvaderBullet {
	public:
		InvaderBullet();
		
		void renderTo(sf::RenderWindow& window);
		void setBulletPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);
		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();

		//Collision
		bool collisionWithShield(Shield* shield); 


	private:
		sf::Texture texture;
		sf::Sprite bullet;
};

#endif