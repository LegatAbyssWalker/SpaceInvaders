#ifndef TEXT_H
#define TEXT_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

class Text {
	public:
		Text(float posX, float posY, unsigned int characterSize, std::string fontFile, std::string text, sf::Color textColor);
		void renderTo(sf::RenderWindow& window);  

		void changePosition(float posX, float posY);

	private:
		sf::Font textFont;
		sf::Text text;
};

#endif