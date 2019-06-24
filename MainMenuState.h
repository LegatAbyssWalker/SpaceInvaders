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


class MainMenuState : public State {
	public:
		MainMenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~MainMenuState();

		void updateEvents();
		void update();
		void render();

	private:
		//Class objects
		FPSCounter fpsCounter;
		Button* startGameButton;
		Button* quitGameButton;
		Text* titleText;


		//Booleans and Variables
		std::string arialFont = "res/fonts/arial.ttf";


		//SFML
		sf::Event sfEvent;
};

#endif