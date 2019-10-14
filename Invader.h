#ifndef INVADER_H
#define INVADER_H

#include "State.h"
#include "Entity.h"
#include "Animation.h"
#include "MoreInfo.h"

#include <iostream>

class Invader : public Entity {
	public:
		enum InvaderType {
			crab = 20,
			octopus = 10,
			squid = 30
		};

		Invader(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void update();
		void move(sf::Vector2<float> distance);

		void setType(Invader::InvaderType type);
		int returnPoints() const;

		void setDead();
		bool isInvaderDead();

		bool isOnScreen();

	private:
		Invader::InvaderType type;
		Animation animation;

		bool isDead = false;
		bool isMovingLeft = false;
		bool isMovingDown = false;

};

#endif