#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "Animation.h"
#include "ToggleKey.h"

#include <iostream>

class Player {
	public:
		Player(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
		
		void renderTo(sf::RenderWindow& window);
		void setPlayerPos(sf::Vector2<float> newPos);
		void updatePlayer();
		int getX();
		int getY();
		void updateBorderBounds();
		sf::FloatRect getGlobalBounds();

	private:
		Animation animation;
		float speed;


		sf::Sprite player, playerSpriteLives[3];
};

#endif