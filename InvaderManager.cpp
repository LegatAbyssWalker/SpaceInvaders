#include "InvaderManager.h"



InvaderManager::InvaderManager() {
	//Invader information
	iBulletTexture.loadFromFile(INVADER_BULLET_T);
	iBullet = std::make_unique<InvaderBullet>(&iBulletTexture, sf::Vector2<unsigned>(2, 1), 0.1, 3.0f);
	iBullet->setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));

	invaderTexture[0].loadFromFile(INVADER_T3); //Squid
	invaderTexture[1].loadFromFile(INVADER_T1); //Crab
	invaderTexture[2].loadFromFile(INVADER_T2); //Octopus

	//Invader creation
	for (size_t x = 0; x < invaderCount; x++) {
		if (x <  (invaderCount / rowCount) * 1)                                      { invaderVector.emplace_back(new Invader(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("squid"); }
		if (x >= (invaderCount / rowCount) * 1 && x < (invaderCount / rowCount) * 2) { invaderVector.emplace_back(new Invader(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 2 && x < (invaderCount / rowCount) * 3) { invaderVector.emplace_back(new Invader(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 3 && x < (invaderCount / rowCount) * 4) { invaderVector.emplace_back(new Invader(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("octopus"); }
		if (x >= (invaderCount / rowCount) * 4 && x < (invaderCount / rowCount) * 5) { invaderVector.emplace_back(new Invader(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("octopus"); }
	}

	//Invader positioning 
	//Row 5
	for (size_t x = (invaderCount / rowCount) * 0; x < (invaderCount / rowCount) * 1; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 170)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 4
	for (size_t x = (invaderCount / rowCount) * 1; x < (invaderCount / rowCount) * 2; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 240)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 3
	for (size_t x = (invaderCount / rowCount) * 2; x < (invaderCount / rowCount) * 3; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 310)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 2
	for (size_t x = (invaderCount / rowCount) * 3; x < (invaderCount / rowCount) * 4; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 380)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 1
	for (size_t x = (invaderCount / rowCount) * 4; x < (invaderCount / rowCount) * 5; x++) { invaderVector[x]->setPosition(sf::Vector2<float>(changedInvaderX, 450)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;



	//Sound information
	//0 = Slow Background Music
	//1 = Fast Background Music
	
	sound[0].setMusic(SLOW_BACKGROUND_FX, 30, true);
}

void InvaderManager::getInformation(int enemyKilled) {
	this->enemyKilled = enemyKilled;
}

void InvaderManager::update() {
	/*-------------------------------------------------------------------------------------------------------------------*/
	//Bullet logic
	//Update
	iBullet->update();

	//Movement
	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += INVADER_BULLET_SPEED;
	iBullet->move(sf::Vector2<float>(iBulletMovement));

	//Bullet bounds
	if (iBullet->getY() >= GROUND_HEIGHT + 10) { iBullet->setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

	/*-------------------------------------------------------------------------------------------------------------------*/

	//Invader logic 
	//Collisions and Movements 
	for (auto& invader : invaderVector) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader->getX() <= 40)                                                    { invaderLeft = false; invaderDown = true; }
		if (invader->getX() >= SCREEN_WIDTH && invader->getX() <= SCREEN_WIDTH + 200) { invaderLeft = true; invaderDown = true; }

		//Slow invader
		if (enemyKilled < invaderCount - 1) {
			if (invaderLeft == false) { invaderMovement.x += INVADER_SPEED; }
			if (invaderLeft == true)  { invaderMovement.x -= INVADER_SPEED; }
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
			invaderMovement.y += INVADER_SPEED;
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
	if (invaderVector.size() > 1) { invaderShooter = randomInvader.getInt(1, invaderVector.size() - 1); }
	else { invaderShooter = 0; }

	//Determining which invader is shooting (random)
	//If the invader chosen is not dead, and if the bullet is at its origin, shoot the bullet at given invader position
	if (invaderVector[invaderShooter]->isInvaderDead() == false) {
		if (iBullet->getX() == BULLET_ORIGIN) {
			iBullet->setPosition(sf::Vector2<float>(invaderVector[invaderShooter]->getX(), invaderVector[invaderShooter]->getY()));
		}
	}
	//Else, if the invader shooter is the same as invadercount, then incriment invadershooter by 1 to find new invader. Else, invadershooter = 1;
	else {
		if (invaderShooter == invaderCount) { invaderShooter++; }
		else { invaderShooter = 1; }
	}


	/*-------------------------------------------------------------------------------------------------------------------*/
	//Removing entities
	auto invaderEnd = std::remove_if(invaderVector.begin(), invaderVector.end(), [](std::unique_ptr<Invader> & invader) {
		return !invader->isOnScreen();
	});
	invaderVector.erase(invaderEnd, invaderVector.end());
}

void InvaderManager::renderTo(sf::RenderWindow& window) {
	for (auto& invader : invaderVector) { invader->renderTo(window); }
	iBullet->renderTo(window);
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
	if (iBullet->getGlobalBounds().intersects(bounds)) {
		return iBullet.get();
	}
	return nullptr;
}

