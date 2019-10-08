#ifndef INVADERBULLET_H
#define INVADERBULLET_H

#include "Entity.h"
#include "State.h"
#include "MoreInfo.h"
#include "Animation.h"

class InvaderBullet : public Entity {
	public:
		InvaderBullet(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime, float speed);
	
		void update();
		void move(sf::Vector2<float> distance);

	private:
		Animation animation;
		float speed;
};

#endif