#ifndef INVADER_H
#define INVADER_H

#include "State.h"
#include "Entity.h"
#include "Animation.h"
#include "MoreInfo.h"

#include <iostream>

class Invader : public Entity {
	public:
		Invader(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void update();
		void move(sf::Vector2<float> distance);

		void setType(std::string type);
		int returnPoints() const;

		void setDead();
		bool isInvaderDead();

		bool isOnScreen();

	private:
		std::string type;
		unsigned int crabPoints = 20;
		unsigned int octopusPoints = 10;
		unsigned int squidPoints = 30;

		Animation animation;

		bool isDead = false;
		bool isMovingLeft = false;
		bool isMovingDown = false;

};

#endif