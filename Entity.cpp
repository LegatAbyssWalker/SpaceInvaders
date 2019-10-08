#include "Entity.h"

#include "MoreInfo.h"


Entity::Entity(sf::Texture& texture) {
	entity.setTexture(texture);
}

void Entity::renderTo(sf::RenderWindow& window) {
	window.draw(entity);
}

void Entity::setPosition(sf::Vector2<float> newPos) {
	entity.setPosition(newPos);
}

int Entity::getX() {
	return entity.getPosition().x;
}

int Entity::getY() {
	return entity.getPosition().y;
}

sf::FloatRect Entity::getGlobalBounds() const {
	return entity.getGlobalBounds();
}
