#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Vector2.hpp"

#include "FPSCounter.h"
#include "Random.h"
#include "PlaySound.h"
#include "Player.h"
#include "Invaders.h"
#include "PlayerBullet.h"
#include "InvaderBullet.h"
#include "Shield.h"
#include "UFO.h"

#include "State.h"
#include "MainMenuState.h"
class StateMachine;

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		~PlayingState();

		void updateKeyboardInputs(sf::Keyboard::Key key, bool isPressed);

		void updateEvents();
		void update();
		void render();

	private:
		//Vectors
		std::vector<PlaySound*> soundVector;
		std::vector<Player*> playerVector;
		std::vector<Invaders*> invaderVector;
		std::vector<Shield*> shieldVector;
		std::vector<UFO*> ufoVector;
		
		//Class objects
		Random<> random;
		FPSCounter fpsCounter;
		PlaySound playSound[5];
		Player player;
		Invaders invaders[15];
		PlayerBullet pBullet;
		InvaderBullet iBullet;
		Shield shield[3];
		UFO ufo;


		//Variables and Booleans
		const float invaderSpeed  = 2;
		const float bulletSpeed   = 9;
		const float ufoSpeed	  = 3;
		unsigned int pBulletCount = 0;

		int shooter			 = 0;
		int playerLives		 = 4;
		int playerScore		 = 0;
		int shieldProtection = 5;
		int enemyCount		 = 15;

		bool isMovingLeft   = false;
		bool isMovingRight  = false;
		bool isBulletFiring = false;

		bool isInvaderLeft  = false;
		bool isInvaderRight = false;
		bool isInvaderDown  = false;

		//SFML
		sf::Event sfEvent;
		sf::Clock dtClock, invaderClock, invaderDownClock, pBulletClock, iBulletClock, iBulletClock2, ufoClock, ufoSoundClock, deathClock;
		float	  dtTimer, invaderTimer, invaderDownTimer, pBulletTimer, iBulletTimer, iBulletTimer2, ufoTimer, ufoSoundTimer, deathTimer;
};

#endif