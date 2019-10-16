#include "InvaderManager.h"



InvaderManager::InvaderManager() {
	//Invader information
	iBulletTexture[0].loadFromFile(INVADER_BULLET_1_T);
	iBulletTexture[1].loadFromFile(INVADER_BULLET_2_T);

	for (size_t x = 0; x < 2; x++) {
		switch (x) {
			case 0: iBulletVector.emplace_back(new InvaderBullet(&iBulletTexture[0], sf::Vector2<unsigned>(2, 1), 0.1, 3.0f)); break;
			case 1: iBulletVector.emplace_back(new InvaderBullet(&iBulletTexture[1], sf::Vector2<unsigned>(2, 1), 0.1, 3.0f)); break;
		}
	}
	for (auto& iBullet : iBulletVector) { iBullet->setPosition(sf::Vector2<float>(INVADER_BULLET_ORIGIN, INVADER_BULLET_ORIGIN)); }

	invaderTexture[0].loadFromFile(INVADER_T3); //Squid
	invaderTexture[1].loadFromFile(INVADER_T1); //Crab
	invaderTexture[2].loadFromFile(INVADER_T2); //Octopus

	//Invader creation
	for (size_t x = 0; x < INVADER_COUNT; x++) {
		if (x <  (INVADER_COUNT / rowCount) * 1)                                      { invaderVector.emplace_back(new Invader(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, NULL)); invaderVector[x]->setType(Invader::InvaderType::squid); }
		if (x >= (INVADER_COUNT / rowCount) * 1 && x < (INVADER_COUNT / rowCount) * 2) { invaderVector.emplace_back(new Invader(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, NULL)); invaderVector[x]->setType(Invader::InvaderType::crab); }
		if (x >= (INVADER_COUNT / rowCount) * 2 && x < (INVADER_COUNT / rowCount) * 3) { invaderVector.emplace_back(new Invader(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, NULL)); invaderVector[x]->setType(Invader::InvaderType::crab); }
		if (x >= (INVADER_COUNT / rowCount) * 3 && x < (INVADER_COUNT / rowCount) * 4) { invaderVector.emplace_back(new Invader(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, NULL)); invaderVector[x]->setType(Invader::InvaderType::octopus); }
		if (x >= (INVADER_COUNT / rowCount) * 4 && x < (INVADER_COUNT / rowCount) * 5) { invaderVector.emplace_back(new Invader(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, NULL)); invaderVector[x]->setType(Invader::InvaderType::octopus); }
	}

	//Invader positioning 
	//Row 5
	for (size_t x = (INVADER_COUNT / rowCount) * 0; x < (INVADER_COUNT / rowCount) * 1; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 170)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 4
	for (size_t x = (INVADER_COUNT / rowCount) * 1; x < (INVADER_COUNT / rowCount) * 2; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 240)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 3
	for (size_t x = (INVADER_COUNT / rowCount) * 2; x < (INVADER_COUNT / rowCount) * 3; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 310)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 2
	for (size_t x = (INVADER_COUNT / rowCount) * 3; x < (INVADER_COUNT / rowCount) * 4; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 380)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 1
	for (size_t x = (INVADER_COUNT / rowCount) * 4; x < (INVADER_COUNT / rowCount) * 5; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 450)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;



	//Sound information
	//0 = Slow Background Music
	//1 = Fast Background Music
	
	sound[0].setMusic(SLOW_BACKGROUND_FX, 30, true);
}

void InvaderManager::update() {
	/*-------------------------------------------------------------------------------------------------------------------*/
	//Bullet logic
	//Update
	for (auto& iBullet : iBulletVector) { iBullet->update(); }

	//Movement
	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += INVADER_BULLET_SPEED;
	for (auto& iBullet : iBulletVector) {
		iBullet->move(sf::Vector2<float>(iBulletMovement));

		//Bullet bounds
		if (iBullet->getY() >= GROUND_HEIGHT + 10) { iBullet->setPosition(sf::Vector2<float>(INVADER_BULLET_ORIGIN, INVADER_BULLET_ORIGIN)); }
	}

	/*-------------------------------------------------------------------------------------------------------------------*/

	//Invader logic 
	//Collisions and Movements 
	for (auto& invader : invaderVector) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader->getX() <= 40)                                                    { invaderLeft = false; invaderDown = true; }
		if (invader->getX() >= SCREEN_WIDTH && invader->getX() <= SCREEN_WIDTH + 200) { invaderLeft = true; invaderDown = true; }

		//Slow invader
		if (invaderVector.size() > 20) {
			if (invaderLeft == false) { invaderMovement.x += SLOW_INVADER_SPEED; }
			if (invaderLeft == true)  { invaderMovement.x -= SLOW_INVADER_SPEED; }
		}
		
		else if (invaderVector.size() <= 20 && invaderVector.size() > 1) {
			if (invaderLeft == false) { invaderMovement.x += FAST_INVADER_SPEED; }
			if (invaderLeft == true)  { invaderMovement.x -= FAST_INVADER_SPEED; }
		}

		//Fast invader
		else {
			sound[0].stopMusic();
			invaderSoundTick++;
			if (invaderSoundTick <= 5) { sound[1].setMusic(FAST_BACKGROUND_FX, 30, true); }

			if (invaderLeft == false) { invaderMovement.x += HYPER_INVADER_SPEED; }
			if (invaderLeft == true)  { invaderMovement.x -= HYPER_INVADER_SPEED; }
		}

		//Down invader
		if (invaderDown == true) {
			invaderDownTick++;
			invaderMovement.y += SLOW_INVADER_SPEED;
			if (invaderVector.size() > 1) {
				if (invaderDownTick >= invaderDownTickNum) {
					invaderDown = false;
					invaderDownTick = 0;
					invaderMovement.y = 0;
				}
			}

			else {
				if (invaderDownTick >= invaderDownTickNum / 4) {
					invaderDown = false;
					invaderDownTick = 0;
					invaderMovement.y = 0;
				}
			}
		}

		if (invader->isInvaderDead() == false) {
			invader->move(invaderMovement);
			invader->update();
		}
	}

	//Shooting
	if (invaderVector.size() > 1) { invaderShooter = random[0].getInt(1, invaderVector.size() - 1); }
	else { invaderShooter = 0; }

		//Determining which invader is shooting (random)
		//If the invader chosen is not dead, and if the bullet is at its origin, shoot the bullet at given invader position
		if (invaderVector[invaderShooter]->isInvaderDead() == false) {
			//Decides whether or not to use 2 or 1 bullet
			if (invaderVector.size() <= INVADER_CHANGE) {
				//Chooses random bullet type
				int bulletType = random[1].getInt(0, iBulletVector.size() - 1);
			
				if (iBulletVector[bulletType]->getX() == INVADER_BULLET_ORIGIN) {
					iBulletVector[bulletType]->setPosition(sf::Vector2<float>(invaderVector[invaderShooter]->getX(), invaderVector[invaderShooter]->getY()));
				}
			}

			else {
				if (iBulletVector[0]->getX() == INVADER_BULLET_ORIGIN) {
					iBulletVector[0]->setPosition(sf::Vector2<float>(invaderVector[invaderShooter]->getX(), invaderVector[invaderShooter]->getY()));
				}
			}
		}
		//Else, if the invader shooter is the same as INVADER_COUNT, then incriment invadershooter by 1 to find new invader. Else, invadershooter = 1;
		else {
			if (invaderShooter == INVADER_COUNT) { invaderShooter++; }
			else { invaderShooter = 1; }
		}


	/*-------------------------------------------------------------------------------------------------------------------*/
	//Removing entities
	auto invaderEnd = std::remove_if(invaderVector.begin(), invaderVector.end(), [](std::unique_ptr<Invader> & invader) {
		return invader->isInvaderDead();
	});
	invaderVector.erase(invaderEnd, invaderVector.end());
}

void InvaderManager::renderTo(sf::RenderWindow& window) {
	for (auto& invader : invaderVector) { invader->renderTo(window); }
	for (auto& iBullet : iBulletVector) { iBullet->renderTo(window); }
}

int InvaderManager::invaderVectorSize() {
	return invaderVector.size();
}

void InvaderManager::stopSounds() {
	for (size_t x = 0; x < sound.size(); x++) {
		sound[x].stopMusic();
	}
}

//Collision
Invader* InvaderManager::invaderCollision(sf::FloatRect bounds) {
	for (auto& invader : invaderVector) {
		if (invader->getGlobalBounds().intersects(bounds)) {
			return invader.get();
		}
	}
	return nullptr;
}

InvaderBullet* InvaderManager::iBulletCollision(sf::FloatRect bounds) {
	for (auto& iBullet : iBulletVector) {
		if (iBullet->getGlobalBounds().intersects(bounds)) {
			return iBullet.get();
		}
	}
	return nullptr;
}

