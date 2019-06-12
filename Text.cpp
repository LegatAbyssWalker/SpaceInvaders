#include "Text.h"


Text::Text(float posX, float posY, int characterSize, std::string fontFile, std::string text, sf::Color textColor) {
	textFont.loadFromFile(fontFile);

	this->text.setFont(textFont);
	this->text.setPosition(posX, posY);
	this->text.setCharacterSize(characterSize);
	this->text.setString(text);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setFillColor(textColor);
}

void Text::renderTo(sf::RenderWindow & window) {
	window.draw(text);
}