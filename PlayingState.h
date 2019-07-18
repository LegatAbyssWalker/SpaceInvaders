#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Vector2.hpp"

#include "FPSCounter.h"
#include "Text.h"
#include "MoreInfo.h"
#include "Random.h"
#include "PlaySound.h"
#include "OStringText.h"

#include "Player.h"
#include "Invaders.h"
#include "PlayerBullet.h"
#include "InvaderBullet.h"
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
		~PlayingState();

		void updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		//Variables and Booleans
		static const int invaderCount = 55;
		static const int shieldCount  = 4;
		static const int soundCount   = 5;
		static const int rowCount     = 5;
		float invaderSwitchTimer      = 0.45;
		unsigned int pBulletCount     = 0;
		const int initialInvaderX     = 100;
		int changedInvaderX           = 100;

		int enemyKilled        = 0;
		int invaderShooter     = 0;
		int playerLives        = 3;
		int playerScore        = 0;
		int randomUFOPoints	   = 0;
		int ufoPoints          = 0;
		int shieldProtection   = SHIELD_PROTECTION;

		int invaderSoundTick   = 0;
		int invaderDownTick    = 0;
		int invaderDownTickNum = 100;

		bool isPlayerShooting = false;
		bool isInvaderLeft    = false;
		bool isInvaderDown    = false;


		//Arrays
		std::array<PlaySound, 6> playSound;
		std::array<Shield, shieldCount> shieldArray;


		//Vectors
		std::vector<std::unique_ptr<Invaders>> invaderVector;


		//Class objects
		std::unique_ptr<Player> player = nullptr;
		std::unique_ptr<InvaderBullet> iBullet = nullptr;
		
		Random<> randomInvader, randomPoints;
		FPSCounter fpsCounter;
		Text versionText;
		OStringText scoreText;
		PlayerBullet pBullet;
		UFO ufo;


		//SFML
		sf::Event sfEvent;
		sf::Texture playerTexture, invaderTexture[3], iBulletTexture;
		sf::Clock dtClock, ufoClock;
		float	  dtTimer, ufoTimer;
};

#endif