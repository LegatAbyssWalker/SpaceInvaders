#ifndef ENTITY_H
#define ENTITY_H

#include "State.h"

class Entity {
	public:
		Entity(sf::Texture& texture);

		void renderTo(sf::RenderWindow& window);
		void setPosition(sf::Vector2<float> newPos);

		int getX();
		int getY();
		sf::FloatRect getGlobalBounds() const;

	protected:
		sf::Sprite entity;
};

#endif