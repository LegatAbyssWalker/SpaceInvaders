#include "UFO.h"

#include "MoreInfo.h"

UFO::UFO(sf::Texture& texture, int speed) : Entity(texture), speed(speed) {

	entity.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	entity.setScale(1 * 1.5, 1 * 1.5);
}

void UFO::update(size_t timeNumber) {
	sf::Vector2<float> movement(0.f, 0.f);

	auto elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - tp).count();

	//Moves if the duration is larger than the timeNumber;
	if (elapsed >= 4 && left == true) {
		movement.x -= speed;
		ufoAppear.setSound(UFO_FX, 50, false);
	}

	else if (elapsed >= 4 && left == false) {
		movement.x += speed;
		ufoAppear.setSound(UFO_FX, 50, false);
	}

	auto resetClock = std::chrono::steady_clock::now();

	//Check if passes triggers
	if (getX() <= 10 && left == true) {
		setPosition(sf::Vector2<float>(-50, SKY_HEIGHT));
		left = false;
		tp = resetClock;
		ufoAppear.stopSound();
	}

	if (getX() >= SCREEN_WIDTH - 10 && left == false) {
		setPosition(sf::Vector2<float>(SCREEN_WIDTH + 50, SKY_HEIGHT));
		left = true;
		tp = resetClock;
		ufoAppear.stopSound();
	}


	entity.move(movement);
	isOnScreen();
}

void UFO::ufoCollisionSound() {
	auto resetClock = std::chrono::steady_clock::now();
	ufoAppear.setSound(UFO_FX, 50, false);
	tp = resetClock;
}

bool UFO::isOnScreen() {
	if (getX() <= SCREEN_WIDTH && getX() >= 0) {
		return true;
	}
	return false;
}