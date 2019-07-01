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
	playerTexture.loadFromFile(playerT);
	player = new Player(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.3, 2.0f);
	this->player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 2, GROUND_HEIGHT));
	playerVector.push_back(this->player);


	//Invader information
	invaderTexture1.loadFromFile(invaderT1);
	invaderTexture2.loadFromFile(invaderT2);
	invaderTexture3.loadFromFile(invaderT3);

	for (int x = 0; x < enemyCount; x++) { 
		if (x <= 4)				  { this->invaders[x] = new Invaders(&invaderTexture1, sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		else if (x > 4 && x <= 9) { this->invaders[x] = new Invaders(&invaderTexture2, sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		else if (x > 9)		      { this->invaders[x] = new Invaders(&invaderTexture3, sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		this->invaderVector.push_back(this->invaders[x]); 
	}
	
	//Row 3
	for (int x = 0; x < enemyCount / rowCount; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX, 250)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;
	
	//Row 2
	for (int x = enemyCount / rowCount; x < invaderInEachRow * (rowCount - 1); x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX, 300)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;

	//Row 1
	for (int x = enemyCount / rowCount + invaderInEachRow; x < invaderInEachRow * rowCount; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX, 350)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;



	//Shield information
	for (int x = 0; x < shieldCount; x++) { shieldVector.push_back(&shield[x]); }
	shield[0].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 150));
	shield[1].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT - 150));
	shield[2].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT - 150));
	shield[3].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT - 150));



	//UFO information
	ufoVector.push_back(&ufo);
	ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));


	//Text information
	this->text = new Text(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, arialFont, "Version 0.7.0", sf::Color(255, 255, 0));


	//Sound information
	//0 = Shooting Effect
	//1 = Invader Killed Effect
	//2 = Explosion
	//3 = Ufo Sound Effect
	//4 = Backround Music

	for (int x = 0; x < soundCount; x++) { soundVector.push_back(&playSound[x]); }
	playSound[4].setMusic(backgroundSE, 30, true);
}

PlayingState::~PlayingState() {
	delete this->player;
	delete this->text;
	for (int x = 0; x < soundCount; x++)		   { playSound[x].stopSound(); playSound[x].stopMusic(); }
	for (int x = 0; x < invaderVector.size(); x++) { delete this->invaders[x]; }

}

void PlayingState::updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space) { isBulletFiring = isPressed; }
	if (key == sf::Keyboard::R)		{ machine.run(machine.buildState<MainMenuState>(machine, window, true)); playSound[4].stopMusic(); }
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

	/*------------------------------------------------------------------------------------------------------------------*/
	this->player->updateBorderBounds();
	this->player->updatePlayer();

	//Player bullet logic
	sf::Vector2<float> pBulletMovement(0.f, 0.f);
	pBulletMovement.y -= bulletSpeed;

	if (isBulletFiring) {
		if (pBulletCount <= 1) {
			switch (pBulletCount) {
				case 0:
					pBullet.setBulletPos(sf::Vector2<float>(this->player->getX(), this->player->getY()));
					playSound[0].setSound(shootingSE, 35, false);
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
	for (int x = 0; x < invaderVector.size(); x++) { this->invaders[x]->update(); }

	//Movement
	sf::Vector2<float> invaderMovement(0.f, 0.f);
	invaderTimer = invaderClock.getElapsedTime().asSeconds();
	invaderDownTimer = invaderDownClock.getElapsedTime().asSeconds();

	//Left or Right
	if (invaderTimer > 0)   { isInvaderLeft  = true; }
	if (invaderTimer > 2.8) { isInvaderLeft  = false; isInvaderRight = true; }
	if (invaderTimer > 5.6) { isInvaderRight = false; invaderClock.restart().asSeconds(); }
	//Down
	if (invaderDownTimer >= 20)   { isInvaderDown = true; }
	if (invaderDownTimer >= 20.3) { isInvaderDown = false; invaderDownClock.restart().asSeconds(); }

	//Movement
	if (isInvaderLeft)  { invaderMovement.x -= invaderSpeed; } //Left
	if (isInvaderRight) { invaderMovement.x += invaderSpeed; } //Right
	if (isInvaderDown)  { invaderMovement.y += invaderSpeed; } //Down

	//Collision and Movements
	for (int x = 0; x < invaderVector.size(); x++) {
		invaderVector[x]->moveTo(invaderMovement);
		
		if (pBullet.collisionWithInvaders(invaderVector[x])) {
			invaderVector[x]->setInvaderPos(sf::Vector2<float>(100000, 100000));
			pBullet.setBulletPos(sf::Vector2<float>(10000, 10000));
			playSound[1].setSound(invaderKilledSE, 35, false);
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
			case 1:  if (this->invaders[0]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[0]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[0]->getX(),  this->invaders[0]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 2:  if (this->invaders[1]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[1]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[1]->getX(),  this->invaders[1]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 3:  if (this->invaders[2]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[2]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[2]->getX(),  this->invaders[2]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 4:  if (this->invaders[3]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[3]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[3]->getX(),  this->invaders[3]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 5:  if (this->invaders[4]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[4]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[4]->getX(),  this->invaders[4]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 6:  if (this->invaders[5]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[5]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[5]->getX(),  this->invaders[5]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 7:  if (this->invaders[6]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[6]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[6]->getX(),  this->invaders[6]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 8:  if (this->invaders[7]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[7]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[7]->getX(),  this->invaders[7]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 9:  if (this->invaders[8]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[8]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[8]->getX(),  this->invaders[8]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 10: if (this->invaders[9]->getX()  >= SCREEN_WIDTH * 0 && this->invaders[9]->getX()  <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[9]->getX(),  this->invaders[9]->getY())); }  if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 11: if (this->invaders[10]->getX() >= SCREEN_WIDTH * 0 && this->invaders[10]->getX() <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[10]->getX(), this->invaders[10]->getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 12: if (this->invaders[11]->getX() >= SCREEN_WIDTH * 0 && this->invaders[11]->getX() <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[11]->getX(), this->invaders[11]->getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 13: if (this->invaders[12]->getX() >= SCREEN_WIDTH * 0 && this->invaders[12]->getX() <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[12]->getX(), this->invaders[12]->getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 14: if (this->invaders[13]->getX() >= SCREEN_WIDTH * 0 && this->invaders[13]->getX() <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[13]->getX(), this->invaders[13]->getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
			case 15: if (this->invaders[14]->getX() >= SCREEN_WIDTH * 0 && this->invaders[14]->getX() <= SCREEN_WIDTH) { iBulletTimer2 = iBulletClock2.getElapsedTime().asSeconds(); if (iBulletTimer2 > 0.000) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[14]->getX(), this->invaders[14]->getY())); } if (iBulletTimer2 > 2.000) { iBulletClock.restart().asSeconds(); iBulletClock2.restart().asSeconds(); } break; }
		}
	}

	iBullet.moveTo(iBulletMovement);

	for (int x = 0; x < playerVector.size(); x++) {
		if (iBullet.collisionWithPlayer(playerVector[x])) {
			iBullet.setBulletPos(sf::Vector2<float>(100000, 100000));
			playSound[2].setSound(explosionSE, 20, false);
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
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); } 
		else {playSound[3].stopSound(); }
	}

	//Moving Right
	if (ufoTimer >= 30.000 && ufoTimer <= 34.000) {
		ufoMovement.x += ufoSpeed;
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); }
		else { playSound[3].stopSound(); }
	}

	if (ufoTimer >= 35.000) { ufoClock.restart().asSeconds(); }
	ufo.moveTo(ufoMovement);

	//UFO collision
	for (int x = 0; x < ufoVector.size(); x++) {
		if (pBullet.collisionWithUFO(ufoVector[x])) {
			ufoVector[x]->setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));
			ufoClock.restart().asSeconds();
			pBullet.setBulletPos(sf::Vector2<float>(1000000, 10000));
		}
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	//Win or Lose
	if (playerScore >= enemyCount) { machine.run(machine.buildState<WinMenuState>(machine, window, true)); playSound[4].stopMusic(); }
	if (playerLives <= 0) { machine.run(machine.buildState<LoseMenuState>(machine, window, true)); playSound[4].stopMusic(); }

}

void PlayingState::render() {
	window.clear();

	//Render items
	this->text->renderTo(window);

	fpsCounter.renderTo(window);
	this->player->renderTo(window);
	pBullet.renderTo(window);
	iBullet.renderTo(window);
	ufo.renderTo(window);

	for (int x = 0; x < invaderVector.size(); x++) { invaderVector[x]->renderTo(window); }
	for (int x = 0; x < shieldVector.size(); x++)  { shieldVector[x]->renderTo(window); }


	window.display();
}
