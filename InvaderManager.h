#ifndef INVADERMANAGER_H
#define INVADERMANAGER_H

#include "Invader.h"
#include "InvaderBullet.h"
#include "Random.h"
#include "Sound.h"

#include "State.h"
#include "MoreInfo.h"

#include <iostream>
#include <array>

class InvaderManager {
	public:
		InvaderManager();
		
		void update();
		void renderTo(sf::RenderWindow& window);

		int invaderVectorSize();
		void stopSounds();

		//Collision 
		Invader* invaderCollision(sf::FloatRect bounds);
		InvaderBullet* iBulletCollision(sf::FloatRect bounds);


	private:
		//Class objects
		std::array<Random<>, 2> random;
		std::array<Sound, 2> sound;
		std::array<sf::Texture, 3> invaderTexture;
		std::array<sf::Texture, 2> iBulletTexture;

		std::vector<std::unique_ptr<Invader>> invaderVector;
		std::vector<std::unique_ptr<InvaderBullet>> iBulletVector;
		
		//Variables and Booleans
		int invaderShooter = 0;
		int enemyKilled = 0;

		static const int invaderCount = INVADER_COUNT;
		static const int shieldCount = 4;
		static const int soundCount = 5;
		static const int rowCount = 5;
		float invaderSwitchTimer = 0.45;
		const int initialInvaderX = 100;
		int changedInvaderX = 100;

		int invaderSoundTick = 0;
		int invaderDownTick = 0;
		int invaderDownTickNum = 100;

		bool invaderLeft = false;
		bool invaderDown = false;

};

#endif