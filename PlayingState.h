#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Vector2.hpp"

#include "FPSCounter.h"
#include "Player.h"
#include "Invaders.h"
#include "Random.h"

#include "State.h"
#include "MainMenuState.h"


class StateMachine;


class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~PlayingState();

		void handleKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		//Vectors
		std::vector<Invaders*> invaderVector;


		//Class objects
		Random<> random;

		FPSCounter fpsCounter;
		Player player;
		Invaders invaders[5];


		//Variables and Booleans
		const int playerSpeed = 5;
		const int bulletSpeed = 7;
		const float invaderSpeed = 0.3;

		bool isMovingLeft   = false;
		bool isMovingRight  = false;
		bool isBulletFiring = false;

		bool isInvaderLeft  = false;
		bool isInvaderRight = false;
		bool isInvaderDown  = false;

		//SFML 
		sf::Event sfEvent;
		sf::Clock invaderClock;
		float invaderTimer;
};

#endif