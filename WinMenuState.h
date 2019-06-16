#ifndef WINMENUSTATE_H
#define WINMENUSTATE_H

#include "SFML/Graphics.hpp"

#include "Text.h"
#include "Button.h"
#include "FPSCounter.h"

#include "State.h"
#include "MainMenuState.h"


class StateMachine;



class WinMenuState : public State {
	public:
		WinMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~WinMenuState();

		void updateEvents();
		void update();
		void render();

	private:
		//Class objects
		Text* winText;
		Button* mainMenuButton;
		Button* quitGameButton;
		FPSCounter fpsCounter;

		//Variables
		std::string arialFont = "res/fonts/arial.ttf";


		//SFML
		sf::Event sfEvent;
};

#endif