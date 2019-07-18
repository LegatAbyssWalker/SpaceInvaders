#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace },
	versionText(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, ARIAL_FONT, "Version 1.2", sf::Color(255, 255, 0)),
	scoreText(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0 + 30, 25, SPACEINVADERS_FONT, sf::Color(255, 255, 255)) {


	//Score and lives information
	std::ifstream ifs("Information/SpaceInvaders.txt");
	if (ifs.is_open()) { 
		ifs >> playerScore; //Score
		ifs >> playerLives; //Lives
	}

	//Player information
	playerTexture.loadFromFile(PLAYER_T);
	player = std::make_unique<Player>(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.3, 2.0f);
	player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
	pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));


	//Invader information
	iBulletTexture.loadFromFile(INVADER_BULLET_T);
	iBullet = std::make_unique<InvaderBullet>(&iBulletTexture, sf::Vector2<unsigned>(2, 1), 0.1, 3.0f);
	iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));

	invaderTexture[0].loadFromFile(INVADER_T3); //Squid
	invaderTexture[1].loadFromFile(INVADER_T1); //Crab
	invaderTexture[2].loadFromFile(INVADER_T2); //Octopus

	//Invader creation
	for (int x = 0; x < invaderCount; x++) {
		if (x < (invaderCount / rowCount) * 1)										 { invaderVector.emplace_back(new Invaders(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("squid"); }
		if (x >= (invaderCount / rowCount) * 1 && x < (invaderCount / rowCount) * 2) { invaderVector.emplace_back(new Invaders(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 2 && x < (invaderCount / rowCount) * 3) { invaderVector.emplace_back(new Invaders(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("crab"); }
		if (x >= (invaderCount / rowCount) * 3 && x < (invaderCount / rowCount) * 4) { invaderVector.emplace_back(new Invaders(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("octopus"); }
		if (x >= (invaderCount / rowCount) * 4 && x < (invaderCount / rowCount) * 5) { invaderVector.emplace_back(new Invaders(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), invaderSwitchTimer, 0.0f)); invaderVector[x]->setType("octopus"); }
	}

	//Invader positioning 
	//Row 5
	for (int x = (invaderCount / rowCount) * 0; x < (invaderCount / rowCount) * 1; x++) { invaderVector[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 150)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 4
	for (int x = (invaderCount / rowCount) * 1; x < (invaderCount / rowCount) * 2; x++) { invaderVector[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 220)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;

	//Row 3
	for (int x = (invaderCount / rowCount) * 2; x < (invaderCount / rowCount) * 3; x++) { invaderVector[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 290)); changedInvaderX += 80;}
	changedInvaderX = initialInvaderX;

	//Row 2
	for (int x = (invaderCount / rowCount) * 3; x < (invaderCount / rowCount) * 4; x++) { invaderVector[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 360)); changedInvaderX += 80;}
	changedInvaderX = initialInvaderX;

	//Row 1
	for (int x = (invaderCount / rowCount) * 4; x < (invaderCount / rowCount) * 5; x++) { invaderVector[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH * 0 + changedInvaderX, 430)); changedInvaderX += 80; }
	changedInvaderX = initialInvaderX;


	//Shield information
	shieldArray[0].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 150));
	shieldArray[1].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 150));
	shieldArray[2].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT - 150));
	shieldArray[3].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 150));



	//UFO information
	ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));


	//Sound information
	//0 = Shooting Effect
	//1 = Invader Killed Effect
	//2 = Explosion
	//3 = Ufo Sound Effect
	//4 = Slow Background Music
	//5 = Fast Background Music

	playSound[4].setMusic(SLOW_BACKGROUND_FX, 30, true);
}

PlayingState::~PlayingState() {
	for (int x = 0; x < soundCount; x++) { playSound[x].stopSound(); playSound[x].stopMusic(); }
}

void PlayingState::updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space)  { isPlayerShooting = isPressed; }
	if (key == sf::Keyboard::Escape) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); playSound[4].stopMusic(); playSound[5].stopMusic(); }
}

void PlayingState::updateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			machine.quit();
			break;

		case sf::Event::KeyPressed:
			updateKeyboardInputs(sfEvent.key.code, true);
			break;

		case sf::Event::KeyReleased:
			updateKeyboardInputs(sfEvent.key.code, false);
			break;
		}
	}
}

void PlayingState::update() {
	fpsCounter.updateCounter();
	scoreText.updateOText("SCORE<1>\n\t\t", playerScore);


	/*------------------------------------------------------------------------------------------------------------------*/
	//Generalized Updating
	player->updateBorderBounds();
	player->updatePlayer();
	player->updateLives(playerLives);
	pBullet.updateBullet(isPlayerShooting, PLAYER_BULLET_SPEED, player->getX(), player->getY());
	iBullet->updateBullet();

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Invader logic 
	//Collisions and Movements 
	for (auto& invader : invaderVector) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader->getX() <= SCREEN_WIDTH * 0 + 40) { isInvaderLeft = false; isInvaderDown = true; }
		if (invader->getX() >= SCREEN_WIDTH)		  { isInvaderLeft = true; isInvaderDown = true; }

		//Slow invader
		if (enemyKilled < invaderCount - 1) {
			if (isInvaderLeft == false) { invaderMovement.x += INVADER_SPEED; }
			if (isInvaderLeft == true)  { invaderMovement.x -= INVADER_SPEED; }
		}

		//Fast invader
		else {
			invaderDownTickNum = 300;
			invaderSoundTick++;

			playSound[4].stopMusic();
			if (invaderSoundTick <= 5) { playSound[5].setMusic(FAST_BACKGROUND_FX, 30, true); }

			if (isInvaderLeft == false) { invaderMovement.x += HYPER_INVADER_SPEED; }
			if (isInvaderLeft == true)  { invaderMovement.x -= HYPER_INVADER_SPEED; }
		}

		if (isInvaderDown == true) {
			invaderDownTick++;
			invaderMovement.y += INVADER_SPEED;
			if (invaderDownTick >= invaderDownTickNum) {
				isInvaderDown = false;
				invaderDownTick = 0;
				invaderMovement.y = 0;
			}
		}

		if (invader->isInvaderDead() == false) {
			invader->moveTo(invaderMovement);
			invader->update();
		}

		//Player collision
		if (player->collisionWithInvaders(*invader)) { playerLives = 0; }

		//Bullet collision
		if (pBullet.collisionWithInvaders(*invader)) {
			invader->setInvaderPos(sf::Vector2<float>(invader->getX(), invader->getY() - INVADER_ORIGIN));
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			playSound[1].setSound(INVADER_KILLED_FX, 20, false);
			enemyKilled++;
			playerScore += invader->returnPointType();
		}


		//Invader touches ground
		if (invader->getY() >= GROUND_HEIGHT) { playerLives = 0; }
	}

	//Shooting
	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += INVADER_BULLET_SPEED;
	invaderShooter = randomInvader.getInt(1, invaderCount - 1);

	//Determining which invader is shooting (random)
	//If the invader chosen is not dead, and if the bullet is at its origin, shoot the bullet at given invader position
	if (invaderVector[invaderShooter]->isInvaderDead() == false) {
		if (iBullet->getX() == BULLET_ORIGIN) {
			iBullet->setBulletPos(sf::Vector2<float>(invaderVector[invaderShooter]->getX(), invaderVector[invaderShooter]->getY()));
		}
	}
	//Else, if the invader shooter is the same as invadercount, then incriment invadershooter by 1 to find new invader. Else, invadershooter = 1;
	else {
		if (invaderShooter == invaderCount) { invaderShooter++; }
		else { invaderShooter = 1; }
	}

	iBullet->moveTo(iBulletMovement);

	//Collision with player
	if (iBullet->collisionWithPlayer(*player)) {
		iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
		player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
		playSound[2].setSound(EXPLOSION_FX, 25, false);
		playerLives--;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Shield logic
	for (auto& shield : shieldArray) {
		//Collision with player bullets
		if (pBullet.collisionWithShield(shield) || iBullet->collisionWithShield(shield)) {
			shield.shieldProtection(1);

			//Collision with player bullets
			if (pBullet.collisionWithShield(shield)) { pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Collision with invader bullets
			else { iBullet->setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Checking for shield damage
			if (shield.shieldProtectionNum() <= 0) { shield.setShieldPos(sf::Vector2<float>(SHIELD_ORIGIN, SHIELD_ORIGIN)); }
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Ufo logic
	sf::Vector2<float> ufoMovement(0.f, 0.f);

	if (enemyKilled < invaderCount - 1) {
		ufoTimer = ufoClock.getElapsedTime().asSeconds();
		//Moving Left
		if (ufoTimer >= 15.000 && ufoTimer <= 21.000) {
			ufoMovement.x -= UFO_SPEED;
			if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFO_FX, 100, false); }
			else if (ufo.isOnScreen(window) == false) { playSound[3].stopSound(); }
		}

		//Moving Right
		if (ufoTimer >= 30.000 && ufoTimer <= 37.000) {
			ufoMovement.x += UFO_SPEED;
			if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFO_FX, 100, false); }
			else if (ufo.isOnScreen(window) == false) { playSound[3].stopSound(); }
		}

		if (ufoTimer >= 38.000) { ufoClock.restart().asSeconds(); }
		ufo.moveTo(ufoMovement);
	}

	else { 
		if (ufo.isOnScreen(window) == true) { ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100)); } 
		ufoTimer = 0; 
	}


	//UFO collision
	if (pBullet.collisionWithUFO(ufo)) {
		ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));
		ufoClock.restart().asSeconds();
		pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));

		//Determining the amount of points given to player after shooting UFO
		randomUFOPoints = randomPoints.getInt(1, 3);
		switch (randomUFOPoints) {
			case 1: ufoPoints = 050; break;
			case 2: ufoPoints = 100; break;
			case 3: ufoPoints = 150; break;
		}
		playerScore += ufoPoints;
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	std::ofstream ofs("Information/SpaceInvaders.txt", std::ios::out | std::ios::trunc);

	//Win
	if (enemyKilled == invaderCount) {
		ofs << playerScore << std::endl; //Score
		ofs << playerLives << std::endl; //Lives

		machine.run(machine.buildState<PlayingState>(machine, window, true)); playSound[5].stopMusic();
	}

	//Lose
	if (playerLives <= 0) {
		ofs << 0; //Score
		ofs << 0; //Lives

		playSound[5].stopMusic();
		machine.run(machine.buildState<MainMenuState>(machine, window, true));
	}

}

void PlayingState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);

	versionText.renderTo(window);
	scoreText.renderTo(window);
	
	player->renderTo(window);
	iBullet->renderTo(window);

	pBullet.renderTo(window);
	ufo.renderTo(window);

	for (auto& invader : invaderVector) { invader->renderTo(window); }
	for (auto& shield : shieldArray)	{ shield.renderTo(window); }


	window.display();
}