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
#include "PlaySound.h"
#include "PlayerBullet.h"
#include "InvaderBullet.h"
#include "Shield.h"
#include "UFO.h"

#include "WinMenuState.h"
#include "LoseMenuState.h"

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
		std::vector<Player*> playerVector;
		std::vector<Shield*> shieldVector;
		std::vector<UFO*> ufoVector;

		//Class objects
		PlaySound playSound;
		Random<> random;
		FPSCounter fpsCounter;
		Player player;
		Invaders invaders[15];
		PlayerBullet pBullet, p2Bullet;
		InvaderBullet iBullet;
		Shield shield[3];
		UFO ufo;

	
		//Variables and Booleans
		const int playerSpeed = 2;
		const float bulletSpeed = 9;
		const float invaderSpeed = 2;
		const float ufoSpeed = 3;
		unsigned int pBulletCount = 0;

		int shooter;
		int playerLives = 3;
		int playerScore = 0;
		int shieldProtection = 5;
		int enemyCount = 15;

		bool isMovingLeft   = false;
		bool isMovingRight  = false;
		bool isBulletFiring = false;

		bool isInvaderLeft  = false;
		bool isInvaderRight = false;
		bool isInvaderDown  = false;

		//SFML 
		sf::Event sfEvent;
		sf::Clock invaderClock, invaderDownClock, pBulletClock, iBulletClock, iBulletClock2, ufoClock, deathClock;
		float invaderTimer, invaderDownTimer, pBulletTimer, iBulletTimer, iBulletTimer2, ufoTimer, deathTimer;
};

#endif