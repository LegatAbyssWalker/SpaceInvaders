#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
class StateMachine;

#include "FPSCounter.h"
#include "Button.h"
#include "Text.h"
#include "MoreInfo.h"

#include <array>
#include <iostream>

class MainMenuState : public State {
	public:
		MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

		void updateEvents();
		void update();
		void render();

	private:
		//Variables
		int invaderYPosAdd = 0;

		//Class objects
		FPSCounter fpsCounter;
		Button startGameButton, quitGameButton;
		Text titleText, ufoText, t1Text, t2Text, t3Text;

		//SFML
		sf::Event sfEvent;

		std::array<sf::Texture, 3> invaderTexture;
		sf::Texture ufoTexture;
		
		std::array<sf::Sprite, 3> invaders;
		sf::Sprite ufo;
};

#endif