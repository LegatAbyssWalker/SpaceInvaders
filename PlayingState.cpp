#include "PlayingState.h"

#include "State.h"
#include "StateMachine.h"

#include "MoreInfo.h"

class StateMachine;

PlayingState::PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace } {


		//Player information
		player.setPlayerPos(sf::Vector2<float>(screenWidth / 2, groundHeight));

		
		//Invader information
		invaderVector.push_back(&invaders[0]);
		invaderVector.push_back(&invaders[1]);
		invaderVector.push_back(&invaders[2]);
		invaderVector.push_back(&invaders[3]);
		invaderVector.push_back(&invaders[4]);

		invaders[0].setInvaderPos(sf::Vector2<float>(screenWidth - 160, 200));
		invaders[1].setInvaderPos(sf::Vector2<float>(screenWidth - 80, 200));
		invaders[2].setInvaderPos(sf::Vector2<float>(screenWidth - 00, 200));
		invaders[3].setInvaderPos(sf::Vector2<float>(screenWidth + 80, 200));
		invaders[4].setInvaderPos(sf::Vector2<float>(screenWidth + 160, 200));

}

PlayingState::~PlayingState() {
	
}



void PlayingState::handleKeyboardInputs(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::A)		{ isMovingLeft = isPressed; }
	if (key == sf::Keyboard::D)		{ isMovingRight = isPressed; }
	if (key == sf::Keyboard::Space) { isBulletFiring = isPressed; }

	//Invader movement test
	if (key == sf::Keyboard::Left)  { isInvaderLeft = isPressed; }
	if (key == sf::Keyboard::Right) { isInvaderRight = isPressed; }
	if (key == sf::Keyboard::Down)  { isInvaderDown = isPressed; }


}

void PlayingState::updateEvents() {
	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);

	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				machine.quit();

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
	fpsCounter.update();
	player.updateBorderBounds();

	//Player logic
	sf::Vector2<float> playerMovement(0.f, 0.f);
	if (isMovingLeft)  { playerMovement.x -= playerSpeed; }
	if (isMovingRight) { playerMovement.x += playerSpeed; }
	player.moveTo(playerMovement);




	//Invader logic
	sf::Vector2<float> invaderMovement(0.f, 0.f);
	//Keyboard movement
	//if (isInvaderLeft)  { invaderMovement.x -= invaderSpeed; } //Left
	//if (isInvaderRight) { invaderMovement.x += invaderSpeed; } //Right
	//if (isInvaderDown)  { invaderMovement.y += invaderSpeed; } //Down

	//AI movement
	for (int x = 0; x < invaderVector.size(); x++) {
		//THIS IS NOT WORKING CORRECTLY FOR SOME REASON
		invaderTimer = invaderClock.getElapsedTime().asSeconds();
		if (invaderTimer <= 1.5) { isInvaderLeft = true; }
		if (invaderTimer > 0.5)  { isInvaderLeft = false; isInvaderRight = true; invaderClock.restart(); }

		if (isInvaderLeft)  { invaderMovement.x -= invaderSpeed; } //Left
		if (isInvaderRight) { invaderMovement.x += invaderSpeed; } //Right
		if (isInvaderDown)  { invaderMovement.y += invaderSpeed; } //Down


		invaders[0].moveTo(invaderMovement);
		invaders[1].moveTo(invaderMovement);
		invaders[2].moveTo(invaderMovement);
		invaders[3].moveTo(invaderMovement);
		invaders[4].moveTo(invaderMovement);

	}

}

void PlayingState::render() {
	window.clear();

	//Render items

	fpsCounter.renderTo(window);
	player.renderTo(window);
	for (int x = 0; x < invaderVector.size(); x++) { invaderVector[x]->renderTo(window); }


	window.display();
}
