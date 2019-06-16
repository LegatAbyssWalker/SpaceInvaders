#include "WinMenuState.h"

#include "State.h"
#include "StateMachine.h"

#include "MoreInfo.h"

class StateMachine;

WinMenuState::WinMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace } {

		//Text
		this->winText = new Text(screenWidth / 2, screenHeight / 3, 40, arialFont, "YOU WIN!", sf::Color(255, 255, 0));

		
		//Button
		this->mainMenuButton = new Button(screenWidth / 2, screenHeight / 2, 150, 50, 20, arialFont, "Main Menu",
			sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));

		this->quitGameButton = new Button(screenWidth / 2, screenHeight / 2 + 100, 150, 50, 20, arialFont, "Quit Game",
			sf::Color(128, 128, 128), sf::Color(192, 192, 192), sf::Color(0, 0, 128), sf::Color(255, 255, 255));
}

WinMenuState::~WinMenuState() {
	delete this->winText;
	delete this->mainMenuButton;
	delete this->quitGameButton;
}

void WinMenuState::updateEvents() {
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				machine.quit();
				break;

			case sf::Event::MouseButtonPressed:
				if (this->quitGameButton->isPressed() == true) { machine.quit(); }
				if (this->mainMenuButton->isPressed() == true) { machine.run(machine.buildState<MainMenuState>(machine, window, true)); }
				break;
		}
	}
}

void WinMenuState::update() {
	fpsCounter.update();

	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);
	this->mainMenuButton->update(sf::Vector2<float>(mousePos));
	this->quitGameButton->update(sf::Vector2<float>(mousePos));
}

void WinMenuState::render() {
	window.clear();

	//Render items
	fpsCounter.renderTo(window);

	this->winText->renderTo(window);
	this->mainMenuButton->renderTo(window);
	this->quitGameButton->renderTo(window);


	window.display();
}
