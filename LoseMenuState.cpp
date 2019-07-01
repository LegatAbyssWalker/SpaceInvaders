#include "LoseMenuState.h"

#include "MoreInfo.h"
#include "MainMenuState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

LoseMenuState::LoseMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace } {

	//Text
	this->loseText = new Text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 40, arialFont, "YOU LOSE!", sf::Color(0, 139, 139));

	//Buttons
	this->mainMenuButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 150, 50, 20, arialFont, "Main Menu",
		sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));

	this->quitGameButton = new Button(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 150, 50, 20, arialFont, "Quit Game",
		sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));
}

LoseMenuState::~LoseMenuState() {
	delete this->loseText;
	delete this->mainMenuButton;
	delete this->quitGameButton;
}

void LoseMenuState::updateEvents() {
	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
	this->mainMenuButton->update(sf::Vector2<float>(mousePos));
	this->quitGameButton->update(sf::Vector2<float>(mousePos));

	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
		case sf::Event::Closed:
			machine.quit();
			break;

		case sf::Event::MouseButtonPressed:
			if (this->mainMenuButton->isPressed() == true) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); }
			if (this->quitGameButton->isPressed() == true) { machine.quit(); }

		}
	}
}

void LoseMenuState::update() {
	fpsCounter.updateCounter();
}

void LoseMenuState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);
	this->quitGameButton->renderTo(window);
	this->mainMenuButton->renderTo(window);
	this->loseText->renderTo(window);


	window.display();
}
