#ifndef UFO_H
#define UFO_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

class UFO {
	public:
		UFO();
		
		void renderTo(sf::RenderWindow& window);
		void setUFOPos(sf::Vector2<float> newPos);
		void moveTo(sf::Vector2<float> distance);
		int getX();
		int getY();
		sf::FloatRect getGlobalBounds();

 	private:
		sf::Texture texture;
		sf::Sprite ufo;
};

#endif