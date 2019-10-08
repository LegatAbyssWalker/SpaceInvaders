#include "InvaderBullet.h"



InvaderBullet::InvaderBullet(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed)
	: Entity(*texture), animation( texture, imageCount, switchTime ) {

	entity.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void InvaderBullet::update() {
	//Animation
	animation.updateAnimation(false, NULL);
	entity.setTextureRect(animation.uvRect);
}

void InvaderBullet::move(sf::Vector2<float> distance) {
	entity.move(distance);
}
