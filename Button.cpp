#include "Button.h"



Button::Button(float posX, float posY, float width, float height, unsigned int characterSize, std::string fontFile, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Color textColor, sf::Color textHoverColor) {
	this->buttonState = BTN_IDLE;

	this->shape.setSize(sf::Vector2<float>(width, height));
	this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
	this->shape.setPosition(sf::Vector2<float>(posX, posY));

	buttonFont.loadFromFile(fontFile);
	this->text.setFont(buttonFont);
	this->text.setCharacterSize(characterSize);
	this->text.setString(text);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setFillColor(textColor);
	this->text.setPosition(posX, posY);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->textHoverColor = textHoverColor;

	this->textColor = textColor;

	this->shape.setFillColor(this->idleColor);
}

const bool Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

void Button::update(const sf::Vector2<float> mousePos) {
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(textColor);
			break;

		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			break;

		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
	}
}

void Button::renderTo(sf::RenderWindow& window) {
	window.draw(this->shape);
	window.draw(this->text);
}
