#ifndef SHIELD_H
#define SHIELD_H

#include "State.h"
#include "Entity.h"
#include "MoreInfo.h"

#include <iostream>

class Shield : public Entity {
	public:
		Shield(sf::Texture& texture);
		Shield(Shield&) = delete;

		void shieldProtection();
		int shieldProtectionNumber();

		bool isOnScreen();

	private:
		int shieldProtectionAccount = SHIELD_PROTECTION;
};

#endif