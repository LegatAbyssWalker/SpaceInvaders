#ifndef LOSEMENUSTATE_H
#define LOSEMENUSTATE_H

#include "State.h"
#include "MainMenuState.h"


class StateMachine;

class LoseMenuState : public State {
	public:
		LoseMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~LoseMenuState();

		void updateEvents();
		void update();
		void render();

	private:
		//Class objects
		Text* loseText;
		Button* mainMenuButton;
		Button* quitGameButton;
		FPSCounter fpsCounter;

		//Variables
		std::string arialFont = "res/fonts/arial.ttf";

		//SFML
		sf::Event sfEvent;
};

#endif