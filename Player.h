#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Entity.h"
#include "Animation.h"
#include "OStringText.h"

#include <iostream>
#include <chrono>

class Player : public Entity {
	public:
		Player(sf::Texture& texture, float speed);

		void keyboardInputs(sf::Keyboard::Key key, bool isPressed);
		void updatePlayer();
		void updateLives(int lives);
		void updateBorderBounds();

		void extraRenderTo(sf::RenderWindow& window);

	private:
		OStringText playerLivesText;
		float speed;

		bool left, right;
};

#endif