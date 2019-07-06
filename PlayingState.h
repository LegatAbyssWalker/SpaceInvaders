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
		Random<> randomInvader, randomPoints;
		FPSCounter fpsCounter;
		Text* verisonText;
		PlaySound playSound[5];
		OStringText* scoreText;

		Player* player;
		Invaders* invaders[18];
		PlayerBullet pBullet;
		InvaderBullet iBullet;
		Shield shield[4];
		UFO ufo;


		//Variables and Booleans
		unsigned int pBulletCount = 0;

		const int initialInvaderX		 = 340;
		int changedInvaderX				 = 340;
		const int invaderInEachRow		 = 5;
		const unsigned int invaderPoints = 20;

		int rowCount    = 3;
		int enemyCount  = 15;
		int enemyKilled = 0;
		int shieldCount = 4;
		int soundCount  = 5;

		int invaderShooter	 = 0;
		int playerLives		 = 3;
		int playerScore		 = 0;
		int randomUFOPoints  = 0;
		int shieldProtection = SHIELD_PROTECTION;

		bool isMovingLeft   = false;
		bool isMovingRight  = false;
		bool isBulletFiring = false;

		bool isInvaderLeft  = true;
		bool isInvaderRight = false;
		bool isInvaderDown  = false;
		int invaderDownTick = 0;

		//SFML
		sf::Event sfEvent;
		sf::Texture playerTexture, invaderTexture[3];
		sf::Clock dtClock, invaderClock, invaderDownClock, iBulletClock, iBulletClock2, ufoClock, ufoSoundClock;
		float	  dtTimer, invaderTimer, invaderDownTimer, iBulletTimer, iBulletTimer2, ufoTimer, ufoSoundTimer;
};

#endif