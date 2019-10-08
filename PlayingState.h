#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "FPSCounter.h"
#include "Text.h"
#include "MoreInfo.h"
#include "Random.h"
#include "PlaySound.h"
#include "OStringText.h"
#include "Textbox.h"

#include "Player.h"
#include "PlayerBullet.h"
#include "InvaderManager.h"
#include "Shield.h"
#include "UFO.h"

#include "State.h"
#include "MainMenuState.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

		void updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();

		//Variables Functions
		void resetPBulletPosition() { pBullet->setPosition(sf::Vector2<float>(BULLET_ORIGIN, BULLET_ORIGIN)); }
		void resetUFOPosition() { ufo->setPosition(sf::Vector2<float>(SCREEN_WIDTH + 50, SKY_HEIGHT)); }


	private:
		//Booleans and Variables
		static const int shieldCount = 4;
		int invaderCount = INVADER_COUNT;
		int enemyKilled  = 0;
		int playerLives  = 3;
		int playerScore  = 0;
		int ufoTimerSave = 0;


		bool playerShooting = false;


		//Class objects
		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<PlayerBullet> pBullet = nullptr;
		std::unique_ptr<UFO> ufo = nullptr;

		std::vector<std::unique_ptr<Shield>> shieldVector;

		std::array<Random<>, 2> random;
		std::array<PlaySound, 2> sound;
		InvaderManager invaderManager;
		FPSCounter fpsCounter;
		Text versionText;
		OStringText scoreText;


		//SFML
		std::array<sf::Texture, 3> invaderTexture;
		sf::Texture playerTexture, ufoTexture, shieldTexture, pBulletTexture;

		sf::Event sfEvent;
		sf::Clock dtClock;
		float	  dtTimer;
};


#endif