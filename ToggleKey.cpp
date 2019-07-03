#include "ToggleKey.h"




ToggleKey::ToggleKey(sf::Keyboard::Key) : key(key) {
}

bool ToggleKey::isKeyPressed() {
	if (delayTimer.getElapsedTime().asSeconds() > 0.2) {
		if (sf::Keyboard::isKeyPressed(key)) {
			delayTimer.restart();
			return true;
		}
	}
	return false;
}
