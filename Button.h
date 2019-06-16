#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
	public:
		Button(float posX, float posY, float width, float height, unsigned int characterSize, std::string fontFile, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color textColor);

		//Button functionality
		const bool isPressed() const;

		void update(const sf::Vector2<float> mousePos);
		void renderTo(sf::RenderWindow& window);

	private:
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font buttonFont;
		sf::Text text;
	
		sf::Color idleColor, hoverColor, activeColor;
};

#endif