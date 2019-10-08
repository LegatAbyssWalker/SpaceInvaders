#include "Shield.h"


Shield::Shield(sf::Texture& texture)
	: Entity(texture) {

	entity.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Shield::shieldProtection() {
	shieldProtectionAccount--;
}

int Shield::shieldProtectionNumber() {
	return shieldProtectionAccount;
}

bool Shield::isOnScreen() {
	if (getX() <= SCREEN_WIDTH && getX() >= 0) {
		return true;
	}
	return false;
}
