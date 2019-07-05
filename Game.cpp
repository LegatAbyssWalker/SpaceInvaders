#include "Game.h"
#include "MoreInfo.h"


void Game::run() {
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders!");
	window.setPosition({ window.getPosition().x, window.getPosition().y - 40 });
	window.setFramerateLimit(FRAMERATE_LIMIT);

	machine.run(StateMachine::buildState<MainMenuState>(machine, window, true));



	//Main Game Loop
	while (window.isOpen() && machine.running()) {
		machine.nextState();
		machine.updateEvents();
		machine.update();
		machine.render();
	}
}
