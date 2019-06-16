#ifndef LOSEMENUSTATE_H
#define LOSEMENUSTATE_H

#include "SFML/Graphics.hpp"

#include "Text.h"
#include "Button.h"
#include "FPSCounter.h"

#include "State.h"
#include "StateMachine.h"
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
		Button* quitGameButton;
		Button* mainMenuButton;
		FPSCounter fpsCounter;

		//Variables
		std::string arialFont = "res/fonts/arial.ttf";


		//SFML
		sf::Event sfEvent;
};

#endif