#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Vector2.hpp"

#include "State.h"
class StateMachine;

#include "FPSCounter.h"
#include "Button.h"
#include "Text.h"
#include "MoreInfo.h"


class MainMenuState : public State {
	public:
		MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~MainMenuState();

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

		sf::Texture invaderTexture[3], ufoTexture;
		sf::Sprite invaders[3], ufo;
};

#endif