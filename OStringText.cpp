#include "OStringText.h"


OStringText::OStringText(float posX, float posY, unsigned int characterSize, std::string fontFile, sf::Color textColor) {
	textFont.loadFromFile(fontFile);

	this->text.setFont(textFont);
	this->text.setPosition(posX, posY);
	this->characterSize = characterSize;
	this->text.setFillColor(textColor);
}

void OStringText::updateOText(std::string text, int variable) {
	this->text.setCharacterSize(characterSize);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);

	this->text.setString(text);

	ssText.str("");
	ssText << text << variable;
	this->text.setString(ssText.str());
}

void OStringText::renderTo(sf::RenderWindow& window) {
	window.draw(text);
}

void OStringText::changePosition(float posX, float posY) {
	this->text.setPosition(posX, posY);
}

void OStringText::changeColor(sf::Color textColor) {
	this->text.setFillColor(textColor);
}

void OStringText::changeCharacterSize(unsigned int characterSize) {
	this->characterSize = characterSize;
	this->text.setCharacterSize(this->characterSize);
}

void OStringText::changeFont(std::string fontFile) {
	textFont.loadFromFile(fontFile);
	this->text.setFont(textFont);
}

