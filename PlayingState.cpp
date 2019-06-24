#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"
#include "WinMenuState.h"
#include "LoseMenuState.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace) 
	: State{ machine, window, replace } {

	//Player information
	player.setPlayerPos(sf::Vector2<float>(screenWidth / 2, groundHeight));
	playerVector.push_back(&player);



	//Invader information
	invaderVector.push_back(&invaders[0]);
	invaderVector.push_back(&invaders[1]);
	invaderVector.push_back(&invaders[2]);
	invaderVector.push_back(&invaders[3]);
	invaderVector.push_back(&invaders[4]);
	invaderVector.push_back(&invaders[5]);
	invaderVector.push_back(&invaders[6]);
	invaderVector.push_back(&invaders[7]);
	invaderVector.push_back(&invaders[8]);
	invaderVector.push_back(&invaders[9]);
	invaderVector.push_back(&invaders[10]);
	invaderVector.push_back(&invaders[11]);
	invaderVector.push_back(&invaders[12]);
	invaderVector.push_back(&invaders[13]);
	invaderVector.push_back(&invaders[14]);
	
	//Row 3
	invaders[0].setInvaderPos(sf::Vector2<float>(screenWidth - 320, 200));
	invaders[1].setInvaderPos(sf::Vector2<float>(screenWidth - 240, 200));
	invaders[2].setInvaderPos(sf::Vector2<float>(screenWidth - 160, 200));
	invaders[3].setInvaderPos(sf::Vector2<float>(screenWidth - 80,  200));
	invaders[4].setInvaderPos(sf::Vector2<float>(screenWidth - 00,  200));
	
	//Row 2
	invaders[5].setInvaderPos(sf::Vector2<float>(screenWidth - 320, 250));
	invaders[6].setInvaderPos(sf::Vector2<float>(screenWidth - 240, 250));
	invaders[7].setInvaderPos(sf::Vector2<float>(screenWidth - 160, 250));
	invaders[8].setInvaderPos(sf::Vector2<float>(screenWidth - 80,  250));
	invaders[9].setInvaderPos(sf::Vector2<float>(screenWidth - 00,  250));

	//Row 1
	invaders[10].setInvaderPos(sf::Vector2<float>(screenWidth - 320, 300));
	invaders[11].setInvaderPos(sf::Vector2<float>(screenWidth - 240, 300));
	invaders[12].setInvaderPos(sf::Vector2<float>(screenWidth - 160, 300));
	invaders[13].setInvaderPos(sf::Vector2<float>(screenWidth - 80,  300));
	invaders[14].setInvaderPos(sf::Vector2<float>(screenWidth - 00,  300));



	//Shield information
	shieldVector.push_back(&shield[0]);
	shieldVector.push_back(&shield[1]);
	shieldVector.push_back(&shield[2]);

	shield[0].setShieldPos(sf::Vector2<float>(screenWidth / 2 + 000, screenHeight - 300));
	shield[1].setShieldPos(sf::Vector2<float>(screenWidth / 2 - 300, screenHeight - 300));
	shield[2].setShieldPos(sf::Vector2<float>(screenWidth / 2 + 300, screenHeight - 300));


	//UFO information
	ufoVector.push_back(&ufo);
	ufo.setUFOPos(sf::Vector2<float>(screenWidth + 40, screenHeight * 0 + 100));



	//Sound information
	playSound.setMusic("res/sounds/backgroundSong.wav", 30, true);
}

PlayingState::~PlayingState() {
	playSound.stopMusic();
	playSound.stopSound();
}

void PlayingState::handleKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::A)		{ isMovingLeft = isPressed; }
	if (key == sf::Keyboard::D)		{ isMovingRight = isPressed; }
	if (key == sf::Keyboard::Space) { isBulletFiring = isPressed; }
}

void PlayingState::updateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::KeyPressed:
				handleKeyboardInputs(sfEvent.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handleKeyboardInputs(sfEvent.key.code, false);
				break;
		}
	}
}

void PlayingState::update() {
	fpsCounter.updateCounter();

	/*------------------------------------------------------------------------------------------------------------------*/
	//Player logic 
	sf::Vector2<float> playerMovement(0.f, 0.f);
	if (isMovingLeft) { playerMovement.x -= playerSpeed; }
	if (isMovingRight) { playerMovement.x += playerSpeed; }
	player.moveTo(playerMovement);

	//Player bullet logic
	sf::Vector2<float> pBulletMovement(0.f, 0.f);
	pBulletMovement.y -= bulletSpeed;

	if (isBulletFiring) {
		if (pBulletCount <= 1) {
			switch (pBulletCount) {
				case 0:
					pBullet.setBulletPos(sf::Vector2<float>(player.getX(), player.getY()));
					playSound.setSound("res/sounds/shoot.wav", 35, false);
					break;
			}

			pBulletCount++;
			isBulletFiring = false;
		}

		if (pBulletCount > 1) {
			isBulletFiring = false;
			pBulletTimer = pBulletClock.getElapsedTime().asSeconds();
			if (pBulletTimer >= 1.000) {
				pBulletCount = 0;
				pBulletClock.restart();
			}
		}
	}

	pBullet.moveTo(pBulletMovement);



	/*-------------------------------------------------------------------------------------------------------------------*/
	//Invader logic 
	sf::Vector2<float> invaderMovement(0.f, 0.f);
	invaderTimer = invaderClock.getElapsedTime().asSeconds();
	invaderDownTimer = invaderDownClock.getElapsedTime().asSeconds();

	//Left or Right
	if (invaderTimer > 0) { isInvaderLeft = true; }
	if (invaderTimer > 2.8) { isInvaderLeft = false; isInvaderRight = true; }
	if (invaderTimer > 5.6) { isInvaderRight = false; invaderClock.restart().asSeconds(); }
	//Down
	if (invaderDownTimer >= 20) { isInvaderDown = true; }
	if (invaderDownTimer >= 20.3) { isInvaderDown = false; invaderDownClock.restart().asSeconds(); }

	//Movement
	if (isInvaderLeft) { invaderMovement.x -= invaderSpeed; } //Left
	if (isInvaderRight) { invaderMovement.x += invaderSpeed; } //Right
	if (isInvaderDown) { invaderMovement.y += invaderSpeed; } //Down

	//Collision and Movements
	for (int x = 0; x < invaderVector.size(); x++) {
		invaderVector[x]->moveTo(invaderMovement);
		
		if (pBullet.collisionWithInvaders(invaderVector[x])) {
			invaderVector[x]->setInvaderPos(sf::Vector2<float>(100000, 100000));
			pBullet.setBulletPos(sf::Vector2<float>(10000, 10000));
			playSound.setSound("res/sounds/invaderKilled.wav", 35, false);
			playerScore++;
		}
	}

	//Shooting
	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += bulletSpeed;

	iBulletTimer = iBulletClock.getElapsedTime().asSeconds();
	if (iBulletTimer > 1.000) {
		shooter = random.getInt(1, 15);

		switch (shooter) {
			case 1:  if (invaders[0].getX()  >= screenWidth * 0 && invaders[0].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[0].getX(),  invaders[0].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 2:  if (invaders[1].getX()  >= screenWidth * 0 && invaders[1].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[1].getX(),  invaders[1].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 3:  if (invaders[2].getX()  >= screenWidth * 0 && invaders[2].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[2].getX(),  invaders[2].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 4:  if (invaders[3].getX()  >= screenWidth * 0 && invaders[3].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[3].getX(),  invaders[3].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 5:  if (invaders[4].getX()  >= screenWidth * 0 && invaders[4].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[4].getX(),  invaders[4].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 6:  if (invaders[5].getX()  >= screenWidth * 0 && invaders[5].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[5].getX(),  invaders[5].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 7:  if (invaders[6].getX()  >= screenWidth * 0 && invaders[6].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[6].getX(),  invaders[6].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 8:  if (invaders[7].getX()  >= screenWidth * 0 && invaders[7].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[7].getX(),  invaders[7].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 9:  if (invaders[8].getX()  >= screenWidth * 0 && invaders[8].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[8].getX(),  invaders[8].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 10: if (invaders[9].getX()  >= screenWidth * 0 && invaders[9].getX()  <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[9].getX(),  invaders[9].getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 11: if (invaders[10].getX() >= screenWidth * 0 && invaders[10].getX() <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[10].getX(), invaders[10].getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 12: if (invaders[11].getX() >= screenWidth * 0 && invaders[11].getX() <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[11].getX(), invaders[11].getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 13: if (invaders[12].getX() >= screenWidth * 0 && invaders[12].getX() <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[12].getX(), invaders[12].getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 14: if (invaders[13].getX() >= screenWidth * 0 && invaders[13].getX() <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[13].getX(), invaders[13].getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 15: if (invaders[14].getX() >= screenWidth * 0 && invaders[14].getX() <= screenWidth) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(invaders[14].getX(), invaders[14].getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
		}
	}

	iBullet.moveTo(iBulletMovement);

	for (int x = 0; x < playerVector.size(); x++) {
		if (iBullet.collisionWithPlayer(playerVector[x])) {
			iBullet.setBulletPos(sf::Vector2<float>(100000, 100000));
			playSound.setSound("res/sounds/explosion.wav", 20, false);
			playerLives--;
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Shield logic
	for (int x = 0; x < shieldVector.size(); x++) {
		//Collision with player bullets
		if (pBullet.collisionWithShield(shieldVector[x])) {
			shieldVector[x]->shieldProtection(1);
			pBullet.setBulletPos(sf::Vector2 <float>(10000, 10000));

			//Checking for shield damage
			if (shieldVector[x]->shieldProtectionNum() <= 0) { shieldVector[x]->setShieldPos(sf::Vector2<float>(100000, 10000)); }
		}

		//Collision with invader bullet
		if (iBullet.collisionWithShield(shieldVector[x])) {
			shieldVector[x]->shieldProtection(1);
			iBullet.setBulletPos(sf::Vector2 <float>(10000, 10000));

			//Checking for shield damage
			if (shieldVector[x]->shieldProtectionNum() <= 0) { shieldVector[x]->setShieldPos(sf::Vector2<float>(100000, 10000)); }
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Ufo logic
	sf::Vector2<float> ufoMovement(0.f, 0.f);

	ufoTimer = ufoClock.getElapsedTime().asSeconds();
	//Moving Left
	if (ufoTimer >= 15.000 && ufoTimer <= 19.000) { ufoMovement.x -= ufoSpeed;
		if (ufo.isOnScreen(window) == true) { playSound.setSound("res/sounds/ufoSound.wav", 20, false); } 
		else {playSound.stopSound(); }
	}

	//Moving Right
	if (ufoTimer >= 30.000 && ufoTimer <= 34.000) {
		ufoMovement.x += ufoSpeed;
		if (ufo.isOnScreen(window) == true) { playSound.setSound("res/sounds/ufoSound.wav", 20, false); }
		else { playSound.stopSound(); }
	}

	if (ufoTimer >= 35.000) { ufoClock.restart().asSeconds(); }
	ufo.moveTo(ufoMovement);

	//UFO collision
	for (int x = 0; x < ufoVector.size(); x++) {
		if (pBullet.collisionWithUFO(ufoVector[x])) {
			ufoVector[x]->setUFOPos(sf::Vector2<float>(screenWidth + 40, screenHeight * 0 + 100));
			ufoClock.restart().asSeconds();
			pBullet.setBulletPos(sf::Vector2<float>(1000000, 10000));
		}
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	//Win or Lose
	if (playerScore >= enemyCount) { machine.run(machine.buildState<WinMenuState>(machine, window, true)); playSound.stopMusic(); }
	if (playerLives <= 0) { machine.run(machine.buildState<LoseMenuState>(machine, window, true)); playSound.stopMusic(); }

}

void PlayingState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);
	player.renderTo(window);
	pBullet.renderTo(window);
	iBullet.renderTo(window);
	ufo.renderTo(window);

	for (int x = 0; x < invaderVector.size(); x++) { invaderVector[x]->renderTo(window); }
	for (int x = 0; x < shieldVector.size(); x++)  { shieldVector[x]->renderTo(window); }


	window.display();
}
