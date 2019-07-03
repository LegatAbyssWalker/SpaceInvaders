#include "MainMenuState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "PlayingState.h"
#include "MoreInfo.h"

#include <iostream>


MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace } {

	//Buttons
	this->quitGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 150, 50, 30, spaceInvadersFont, "Quit",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255));

	this->startGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, 150, 50, 30, spaceInvadersFont, "Play",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255));
	
	//Text
	this->titleText = new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 50, spaceInvadersFont, "Space Invaders", sf::Color(255, 255, 255));

	//Textures
	

}

MainMenuState::~MainMenuState() {
	delete this->quitGameButton;
	delete this->startGameButton;
	delete this->titleText;
}

void MainMenuState::updateEvents() {
	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);

	//Updating mouse position for button functionality
	this->quitGameButton->update(sf::Vector2<float>(mousePos));
	this->startGameButton->update(sf::Vector2<float>(mousePos));

	//Events while loop
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (this->quitGameButton->isPressed() == true) { machine.quit(); }
			if (this->startGameButton->isPressed() == true) { machine.run(machine.buildState<PlayingState>(machine, window, true)); }

			break;
		}
	}
}

void MainMenuState::update() {
	fpsCounter.updateCounter();
}

void MainMenuState::render() {
	window.clear();

	//Render items
	this->quitGameButton->renderTo(window);
	this->startGameButton->renderTo(window);
	this->titleText->renderTo(window);

	fpsCounter.renderTo(window);


	window.display();
}
