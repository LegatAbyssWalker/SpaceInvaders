#ifndef UFO_H
#define UFO_H

#include "State.h"
#include "Entity.h"
#include "Random.h"
#include "PlaySound.h"

#include <iostream>
#include <chrono>

class UFO : public Entity {
	public:
		UFO(sf::Texture& texture, int speed);

		void update(size_t timeNumber);
		void ufoCollisionSound();
		bool isOnScreen();


	private:
		PlaySound ufoAppear;
		bool left = true;
		int speed;

		std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now();
};

#endif