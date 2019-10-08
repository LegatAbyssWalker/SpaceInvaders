#include "Textbox.h"

#include "MoreInfo.h"

constexpr auto CursorPeriod = std::chrono::milliseconds(500);

Textbox::Textbox(std::string fontFile, float posX, float posY, int characterSize, int boxWidth,
	sf::Color boxColor, sf::Color textColor, bool password)
	: text("", font, 16), password(password) {

	setPosition(posX, posY);
	text.setPosition(getPosition());
	font.loadFromFile(fontFile);
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setFillColor(textColor);

	setBoxWidth(boxWidth);
	rectangle.setFillColor(boxColor);
	rectangle.setPosition(text.getPosition() - sf::Vector2<float>(1, 1));
	
	cursor.setFillColor(sf::Color(0, 0, 0));
	cursor.setSize(sf::Vector2<float>(1, text.getCharacterSize()));
	setCursor(-1);

	selection.setFillColor(sf::Color(128, 128, 255));

}

void Textbox::setString(const sf::String& str) {
	string = str;
	if (!password) { text.setString(str); }
	else {
		std::string passwordString(str.getSize(), '*');
		text.setString(passwordString);
	}
}

bool Textbox::handleEvent(const sf::Event sfEvent) {
	switch (sfEvent.type) {
		case sf::Event::KeyPressed: {
			if (cursorPosition == -1) {
				return false;
			}

			switch (sfEvent.key.code) {
				case sf::Keyboard::Left: {
					size_t pos = std::max(cursorPosition, size_t(1)) - 1;
					setCursor(pos, !sfEvent.key.shift);
					return true;
				}

				case sf::Keyboard::Right: {
					size_t pos = std::min(cursorPosition + 1, string.getSize());
					setCursor(pos, !sfEvent.key.shift);
					return true;
				}

				case sf::Keyboard::Home:
					setCursor(0, !sfEvent.key.shift);
					return true;

				case sf::Keyboard::End:
					setCursor(string.getSize(), !sfEvent.key.shift);
					return true;

				case sf::Keyboard::Backspace:
					if (cursorPosition != selectionPosition) {
						eraseSelection:
							eraseSelection();
					}

					else if (cursorPosition > 0) {
						cursorPosition--;
						string.erase(cursorPosition);
						setString(string);
						setCursor(cursorPosition);
					}
					return true;

				case sf::Keyboard::Delete:
					if (cursorPosition != selectionPosition) { eraseSelection(); }
					else if (cursorPosition < string.getSize()) {
						string.erase(cursorPosition);
						setString(string);
					}

				case sf::Keyboard::V:
					if (sfEvent.key.control) {
						typeString(sf::Clipboard::getString());
						return true;
					}
					else { return false; }

				case sf::Keyboard::X:
				case sf::Keyboard::C:
					if (sfEvent.key.control) {
						sf::Clipboard::setString(string.substring(leftPosition(), rightPosition() - leftPosition()));
						if (sfEvent.key.code == sf::Keyboard::X) { eraseSelection(); }
						return true;
					}
					else { return false; }

				case sf::Keyboard::A:
					if (sfEvent.key.control) {
						selectionPosition = 0;
						setCursor(string.getSize(), false);
						return true;
					}
					else { return false; }
			}
			return false;
	}

		case sf::Event::TextEntered: {
			if (cursorPosition == -1) { return false; }

			auto code = sfEvent.text.unicode;
			if (code > 30 && (code < 127 || code > 159)) {
				typeString(sf::String(code));
			}
			return true;
		}

		case sf::Event::MouseButtonPressed: {
			auto x = sfEvent.mouseButton.x;
			auto y = sfEvent.mouseButton.y;

			//Check if we're inside the box
			auto pos = getPosition();
			if (x >= pos.x && y >= pos.y && x < pos.x + textBoxWidth && y < pos.y + text.getCharacterSize() + 2) {
				setCursor(findCursorPositionForX(x));
				mousePressed = true;
				return true;
				//The return true means that the textbox will swallow the sfEvent
			}
			else {
				setCursor(-1);
				return false;
			}
		}

		case sf::Event::MouseButtonReleased: {
			if (mousePressed) {
				mousePressed = false;
				return true;
			}
			else { return false; }
		}

		case sf::Event::MouseMoved: {
			if (mousePressed) {
				setCursor(findCursorPositionForX(sfEvent.mouseMove.x), false);
				return true;
			}
			else { return false; }
		}
	}
	return false;
}

void Textbox::typeString(const sf::String& str) {
	auto size = string.getSize();

	string.replace(leftPosition(), rightPosition() - leftPosition(), str);
	setString(string);
	setCursor(leftPosition() + str.getSize());

	auto x = text.findCharacterPos(string.getSize()).x - text.getPosition().x;
	if (x > textBoxWidth) {
		auto pos = findCursorPositionForX(text.getPosition().x + textBoxWidth);
		string.erase(pos, string.getSize() - pos);
		setString(string);
		setCursor(pos);
	}
}

void Textbox::eraseSelection() {
	string.erase(leftPosition(), rightPosition() - leftPosition());
	setString(string);
	setCursor(leftPosition());
}

void Textbox::setBoxWidth(int width) {
	textBoxWidth = width;
	auto height = text.getFont()->getLineSpacing(text.getCharacterSize());
	rectangle.setSize(sf::Vector2<float>(width, height + 2));
}

void Textbox::setCursor(size_t position, bool updateSelection) {
	cursorPosition = position;
	if (updateSelection) { selectionPosition = position; }

	updateCursorAndSelection();
}

void Textbox::setIsPassword(bool password) {
	this->password = password;
	setString(string);
}

size_t Textbox::findCursorPositionForX(float x) {
	size_t pos;
	for (pos = string.getSize(); pos > 0; pos--) {
		if (text.findCharacterPos(pos).x <= x) {
			break;
		}
	}

	return pos;
}

void Textbox::updateCursorAndSelection() {
	if (cursorPosition != -1) {
		cursor.setPosition(text.findCharacterPos(cursorPosition));
	}
	if (cursorPosition != selectionPosition) {
		auto pos1 = text.findCharacterPos(leftPosition());
		auto pos2 = text.findCharacterPos(rightPosition());

		selection.setPosition(pos1);
		selection.setSize(sf::Vector2<float>(pos2.x - pos1.x, text.getCharacterSize()));
	}
}

void Textbox::update(Duration newDuration) {
	if (cursorPosition == -1) { cursorBlink = Duration(); }
	else { 
		cursorBlink += newDuration; 
		if (cursorBlink > 2 * CursorPeriod) {
			cursorBlink -= 2 * CursorPeriod;
		}
	}
}

void Textbox::renderTo(sf::RenderWindow& window) {
	window.draw(rectangle);

	if (selectionPosition != cursorPosition) { window.draw(selection); }

	window.draw(text);

	if (cursorPosition != -1 && cursorBlink > CursorPeriod) { window.draw(cursor); }
}
