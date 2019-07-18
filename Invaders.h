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
		void update();
		void moveTo(sf::Vector2<float> distance);
		
		void setType(std::string type);
		int returnPointType() const;

		void setDead();
		bool isInvaderDead();

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds() const;



	private:
		//Explosion information
		const unsigned int crab	   = 20;
		const unsigned int octopus = 10;
		const unsigned int squid   = 30;

		std::string type;

		sf::Texture invaderTexture, explosionTexture;
		sf::Sprite invader;

		Animation animation;

		bool isDead = false;

		bool isMovingLeft  = true;
		bool isMovingDown  = false;
		bool isMovingRight = false;
};

#endif