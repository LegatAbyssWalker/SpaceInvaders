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
	this->quitGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40, 150, 50, 20, arialFont, "Quit Game",
		sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));

	this->startGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40, 150, 50, 20, arialFont, "Start Game",
		sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));

	//Text
	this->titleText = new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 40, arialFont, "Space Invaders!", sf::Color(0, 139, 139));

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
