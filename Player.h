#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include <iostream>

class Player {
	public:
		Player();

		void renderTo(sf::RenderWindow& window);
		void setPlayerPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);
		int getX();
		int getY();
		void updateBorderBounds();
		sf::FloatRect getGlobalBounds();

	private:
		sf::Texture texture;
		sf::Sprite player;
};

#endif