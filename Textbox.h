#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "State.h"
#include <iostream>
#include <chrono>

using Duration = std::chrono::steady_clock::duration;

class Textbox : public sf::Transformable {
	public:
		Textbox(std::string fontFile, float posX, float posY, int characterSize, int boxWidth,
			sf::Color boxColor, sf::Color textColor, bool password);
		
		const sf::String& getString() const { return string; }
		void setString(const sf::String & str);
		bool handleEvent(const sf::Event sfEvent);
	
		int getBoxWidth() const { return textBoxWidth; }
		void setBoxWidth(int width);

		int getCursorPosition() const { return cursorPosition; }
		void setCursor(size_t position, bool updateSelection = true);

		size_t getSelectionPosition() const { return selectionPosition; }
		size_t leftPosition() const { return std::min(cursorPosition, selectionPosition); }
		size_t rightPosition() const { return std::max(cursorPosition, selectionPosition); }

		bool isPassword() const { return password; }
		void setIsPassword(bool password);

		void update(Duration newDuration);
		void renderTo(sf::RenderWindow& window);

	private:
		sf::Font font;
		sf::Text text;
		sf::String string;
		sf::RectangleShape rectangle;
		sf::RectangleShape cursor;
		sf::RectangleShape selection;
		Duration cursorBlink;


		size_t cursorPosition, selectionPosition;
		size_t findCursorPositionForX(float x);
		void updateCursorAndSelection();
		void typeString(const sf::String& str);
		void eraseSelection();

		bool password;
		bool mousePressed;
		int textBoxWidth;
};

#endif