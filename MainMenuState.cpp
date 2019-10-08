#include "MainMenuState.h"

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "PlayingState.h"
#include "MoreInfo.h"

#include <iostream>
#include <fstream>


MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State{ machine, window, replace },
	//Text
	titleText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 20, 50, SPACEINVADERS_FONT, "Space Invaders", sf::Color(255, 255, 255)),
	ufoText(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 - 040, 20, SPACEINVADERS_FONT, " = ? MYSTERY", sf::Color(255, 255, 255)),
	t1Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 040, 20, SPACEINVADERS_FONT, " = 30 Points", sf::Color(255, 255, 255)),
	t2Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 140, 20, SPACEINVADERS_FONT, " = 20 Points", sf::Color(255, 255, 255)),
	t3Text(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2.5 + 240, 20, SPACEINVADERS_FONT, " = 10 Points", sf::Color(0, 128, 0)),
	//Buttons
	startGameButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 100, 40, 30, SPACEINVADERS_FONT, "Play",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255)),
	quitGameButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300, 100, 40, 30, SPACEINVADERS_FONT, "Quit",
		sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(0, 255, 255)) {

	//Textures
	invaderTexture[0].loadFromFile(INVADER_T3);
	invaderTexture[1].loadFromFile(INVADER_T1);
	invaderTexture[2].loadFromFile(INVADER_T2);
	ufoTexture.loadFromFile(UFO_T);

	for (int x = 0; x < 3; x++) {
		invaders[x].setTexture(invaderTexture[x]);
		invaders[x].setTextureRect(sf::IntRect(invaderTexture[x].getSize().x / 2 * 0, invaderTexture[x].getSize().y * 0, invaderTexture[x].getSize().x / 2, invaderTexture[x].getSize().y));
		invaders[x].setPosition(sf::Vector2<float>(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2.5 + 30 + invaderYPosAdd));
		invaderYPosAdd += 100;
		if (x == 2) { invaders[x].setColor(sf::Color(0, 128, 0)); }
	}

	ufo.setTexture(ufoTexture);
	ufo.setPosition(sf::Vector2<float>(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2.5 - 70));
	ufo.setScale(1 * 1.5, 1 * 1.5);
}

void MainMenuState::updateEvents() {
	sf::Vector2<int> mousePos = sf::Mouse::getPosition(window);

	//Updating mouse position for button functionality
	quitGameButton.update(sf::Vector2<float>(mousePos));
	startGameButton.update(sf::Vector2<float>(mousePos));

	//Events while loop
	while (window.pollEvent(sfEvent)) {
		switch (sfEvent.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (quitGameButton.isPressed() == true) { machine.quit(); }
				if (startGameButton.isPressed() == true) { machine.run(machine.buildState<PlayingState>(machine, window, true)); }
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
	quitGameButton.renderTo(window);
	startGameButton.renderTo(window);
	titleText.renderTo(window);

	ufoText.renderTo(window);
	t1Text.renderTo(window);
	t2Text.renderTo(window);
	t3Text.renderTo(window);

	fpsCounter.renderTo(window);

	for (int x = 0; x < 3; x++) { window.draw(invaders[x]); }
	window.draw(ufo);

	window.display();
}
