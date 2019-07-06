#ifndef INVADERS_H
#define INVADERS_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"

#include <iostream>

class Invaders {
	public:
		Invaders(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void renderTo(sf::RenderWindow& window);
		void setInvaderPos(sf::Vector2<float> newPos);
		void update(int invaderSpeed);
		void moveTo(sf::Vector2<float> distance);
		
		void setDead();
		bool isInvaderDead();

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();

	private:
		sf::Texture invaderTexture;
		sf::Sprite invader;

		Animation animation;
		float speed;

		bool isDead = false;

		bool isMovingLeft  = true;
		bool isMovingDown  = false;
		bool isMovingRight = false;
};

#endif