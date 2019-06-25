#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation {
	public:
		Animation(sf::Texture* texture, sf::Vector2<unsigned> imageCount, float switchTime);
		
		void update(int row, float deltaTime, bool faceRight);


	public:
		sf::IntRect uvRect;

	private:
		sf::Vector2<unsigned> imageCount, currentImage;

		float totalTime, switchTime;
	};

#endif