#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "MoreInfo.h"
#include "WinMenuState.h"
#include "LoseMenuState.h"

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)  
	: State{ machine, window, replace } {

	//Text information
	this->scoreText = new OStringText(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0 + 30, 25, spaceInvadersFont, sf::Color(255, 255, 255));
	this->verisonText = new Text(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 30, 25, arialFont, "Version 1.0", sf::Color(255, 255, 0));

	//Player information
	playerTexture.loadFromFile(playerT);
	player = new Player(&playerTexture, sf::Vector2<unsigned>(1, 1), 0.3, 2.0f);
	this->player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
	playerVector.push_back(this->player);
	pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));


	//Invader information
	iBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
		
	invaderTexture[0].loadFromFile(invaderT1);
	invaderTexture[1].loadFromFile(invaderT2);
	invaderTexture[2].loadFromFile(invaderT3);

	for (int x = 0; x < enemyCount; x++) { 
		if (x <= 4)				  { this->invaders[x] = new Invaders(&invaderTexture[0], sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		else if (x > 4 && x <= 9) { this->invaders[x] = new Invaders(&invaderTexture[1], sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		else if (x > 9)		      { this->invaders[x] = new Invaders(&invaderTexture[2], sf::Vector2<unsigned>(2, 1), 0.5, 0.0f); }
		this->invaderVector.push_back(this->invaders[x]); 
	}
	
	//Row 3
	for (int x = 0; x < enemyCount / rowCount; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX, 250)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;
	
	//Row 2
	for (int x = enemyCount / rowCount; x < invaderInEachRow * (rowCount - 1); x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX, 300)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;

	//Row 1
	for (int x = enemyCount / rowCount + invaderInEachRow; x < invaderInEachRow * rowCount; x++) { this->invaders[x]->setInvaderPos(sf::Vector2<float>(SCREEN_WIDTH - changedInvaderX - 10, 350)); changedInvaderX -= 80; }
	changedInvaderX = initialInvaderX;
	
	

	//Shield information
	for (int x = 0; x < shieldCount; x++) { shieldVector.push_back(&shield[x]); }
	shield[0].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 150));
	shield[1].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 150));
	shield[2].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT - 150));
	shield[3].setShieldPos(sf::Vector2<float>(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT - 150));



	//UFO information
	ufoVector.push_back(&ufo);
	ufo.setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));


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
	delete this->verisonText;
	delete this->scoreText;

	for (int x = 0; x < soundCount; x++)		   { playSound[x].stopSound(); playSound[x].stopMusic(); }
	for (int x = 0; x < invaderVector.size(); x++) { delete this->invaders[x]; }
}

void PlayingState::updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space)  { isBulletFiring = isPressed; }
	if (key == sf::Keyboard::Escape) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); playSound[4].stopMusic(); }
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
	scoreText->updateOText("SCORE<1>\n\t\t", playerScore);


	/*------------------------------------------------------------------------------------------------------------------*/
	//Updating
	this->player->updateBorderBounds();
	this->player->updatePlayer();
	this->player->updateLives(playerLives);
	pBullet.updateBullet(isBulletFiring, BULLET_SPEED, this->player->getX(), this->player->getY());

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Invader logic 
	//Collision and Movements 
	for (auto &invader : invaderVector) {
		//Movements
		sf::Vector2<float> invaderMovement(0.f, 0.f);
		if (invader->getX() <= SCREEN_WIDTH * 0 + 40) { isInvaderLeft = false; isInvaderRight = true; isInvaderDown = true; }
		if (invader->getX() >= SCREEN_WIDTH)		  { isInvaderLeft = true; isInvaderRight = false; isInvaderDown = true; }

		if (isInvaderLeft == false && isInvaderRight == true) { invaderMovement.x += INVADER_SPEED; }
		if (isInvaderLeft == true && isInvaderRight == false) { invaderMovement.x -= INVADER_SPEED; }

		if (isInvaderDown == true) {
			invaderDownTick++;
			invaderMovement.y += INVADER_SPEED;
			if (invaderDownTick >= 100) {
				isInvaderDown = false;
				invaderDownTick = 0;
			}
		}

		if (invader->isInvaderDead() == false) {
			invader->moveTo(invaderMovement);
			invader->update(INVADER_SPEED);
		}
		
		if (pBullet.collisionWithInvaders(invader)) {
			invader->setInvaderPos(sf::Vector2<float>(invader->getX(), invader->getY() - INVADER_ORIGIN));
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			playSound[1].setSound(invaderKilledSE, 25, false);
			playerScore += invaderPoints;
			enemyKilled++;
		}
	}

	//Shooting
	iBullet.updateBullet();

	sf::Vector2<float> iBulletMovement(0.f, 0.f);
	iBulletMovement.y += BULLET_SPEED;

	iBulletTimer = iBulletClock.getElapsedTime().asSeconds();
	if (iBulletTimer > 1.000) {
		invaderShooter = randomInvader.getInt(1, 15);

		switch (invaderShooter) {
			case 1:  if (this->invaders[0]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[0]->getX(),  this->invaders[0]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 2;  }
			case 2:  if (this->invaders[1]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[1]->getX(),  this->invaders[1]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 3;  }
			case 3:  if (this->invaders[2]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[2]->getX(),  this->invaders[2]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 4;  }
			case 4:  if (this->invaders[3]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[3]->getX(),  this->invaders[3]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 5;  }
			case 5:  if (this->invaders[4]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[4]->getX(),  this->invaders[4]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 6;  }
			case 6:  if (this->invaders[5]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[5]->getX(),  this->invaders[5]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 7;  }
			case 7:  if (this->invaders[6]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[6]->getX(),  this->invaders[6]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 8;  }
			case 8:  if (this->invaders[7]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[7]->getX(),  this->invaders[7]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 9;  }
			case 9:  if (this->invaders[8]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[8]->getX(),  this->invaders[8]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 10; }
			case 10: if (this->invaders[9]->isInvaderDead()  == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[9]->getX(),  this->invaders[9]->getY()));  iBulletClock.restart().asSeconds(); } } else { invaderShooter = 11; }
			case 11: if (this->invaders[10]->isInvaderDead() == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[10]->getX(), this->invaders[10]->getY())); iBulletClock.restart().asSeconds(); } } else { invaderShooter = 12; }
			case 12: if (this->invaders[11]->isInvaderDead() == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[11]->getX(), this->invaders[11]->getY())); iBulletClock.restart().asSeconds(); } } else { invaderShooter = 13; }
			case 13: if (this->invaders[12]->isInvaderDead() == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[12]->getX(), this->invaders[12]->getY())); iBulletClock.restart().asSeconds(); } } else { invaderShooter = 14; }
			case 14: if (this->invaders[13]->isInvaderDead() == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[13]->getX(), this->invaders[13]->getY())); iBulletClock.restart().asSeconds(); } } else { invaderShooter = 15; }
			case 15: if (this->invaders[14]->isInvaderDead() == false) { if (iBullet.getX() == BULLET_ORIGIN) { iBullet.setBulletPos(sf::Vector2<float>(this->invaders[14]->getX(), this->invaders[14]->getY())); iBulletClock.restart().asSeconds(); } } else { invaderShooter = 1;  }
		}
	}

	iBullet.moveTo(iBulletMovement);

	for (auto &player : playerVector) {
		if (iBullet.collisionWithPlayer(player)) {
			iBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			player->setPlayerPos(sf::Vector2<float>(SCREEN_WIDTH / 10, GROUND_HEIGHT));
			playSound[2].setSound(explosionSE, 20, false);
			playerLives--;
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Shield logic
	for (auto &shield : shieldVector) {
		//Collision with player bullets
		if (pBullet.collisionWithShield(shield) || iBullet.collisionWithShield(shield)) {
			shield->shieldProtection(1);

			//Collision with player bullets
			if (pBullet.collisionWithShield(shield)) { pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Collision with ivnader bullets
			else { iBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }

			//Checking for shield damage
			if (shield->shieldProtectionNum() <= 0) { shield->setShieldPos(sf::Vector2<float>(SHIELD_ORIGIN, SHIELD_ORIGIN)); }
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	//Ufo logic
	sf::Vector2<float> ufoMovement(0.f, 0.f);

	ufoTimer = ufoClock.getElapsedTime().asSeconds();
	//Moving Left
	if (ufoTimer >= 15.000 && ufoTimer <= 19.000) { ufoMovement.x -= UFO_SPEED;
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); } 
		else {playSound[3].stopSound(); }
	}

	//Moving Right
	if (ufoTimer >= 30.000 && ufoTimer <= 34.000) {
		ufoMovement.x += UFO_SPEED;
		if (ufo.isOnScreen(window) == true) { playSound[3].setSound(UFOSE, 20, false); }
		else { playSound[3].stopSound(); }
	}

	if (ufoTimer >= 35.000) { ufoClock.restart().asSeconds(); }
	ufo.moveTo(ufoMovement);

	//UFO collision
	for (auto &ufo : ufoVector) {
		if (pBullet.collisionWithUFO(ufo)) {
			ufo->setUFOPos(sf::Vector2<float>(SCREEN_WIDTH + 40, SCREEN_HEIGHT * 0 + 100));
			ufoClock.restart().asSeconds();
			pBullet.setBulletPos(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN));
			randomUFOPoints = randomPoints.getInt(100, 500);
			playerScore += randomUFOPoints;
		}
	}



	/*-------------------------------------------------------------------------------------------------------------------*/
	//Win or Lose
	if (enemyKilled == enemyCount) { machine.run(machine.buildState<WinMenuState>(machine, window, true)); playSound[4].stopMusic(); }
	if (playerLives <= 0) { machine.run(machine.buildState<LoseMenuState>(machine, window, true)); playSound[4].stopMusic(); playerScore = 0; }

}

void PlayingState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);
	this->verisonText->renderTo(window);
	this->scoreText->renderTo(window);

	this->player->renderTo(window);
	pBullet.renderTo(window);
	iBullet.renderTo(window);
	ufo.renderTo(window);

	for (auto &invader : invaderVector) { invader->renderTo(window); }
	for (auto &shield : shieldVector) { shield->renderTo(window); }


	window.display();
}
