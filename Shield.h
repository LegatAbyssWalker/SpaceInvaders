#ifndef SHIELD_H
#define SHIELD_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include "MoreInfo.h"

class Shield {
	public:
		Shield();
		Shield(Shield&) = delete;
		
		void renderTo(sf::RenderWindow& window);
		void setShieldPos(sf::Vector2<float> newPos);
		int getX();
		int getY();
		sf::FloatRect getGlobalBounds() const;

		void shieldProtection(int num);
		int shieldProtectionNum();

	private:
		int shieldProtectionAccount = SHIELD_PROTECTION;

		sf::Texture texture;
		sf::Sprite shield;
};

#endif