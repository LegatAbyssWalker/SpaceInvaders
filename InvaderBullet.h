#ifndef INVADERBULLET_H
#define INVADERBULLET_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"
#include "Player.h"
#include "Shield.h"

#include <iostream>

class InvaderBullet {
	public:
		InvaderBullet(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void renderTo(sf::RenderWindow& window);
		void setBulletPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);
		void updateBullet();

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();

		//Collision
		bool collisionWithPlayer(const Player& player);
		bool collisionWithShield(const Shield& shield);

	private:
		Animation animation;
	
		sf::Texture texture;
		sf::Sprite bullet;
};

#endif