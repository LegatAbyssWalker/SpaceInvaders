#include "FPSCounter.h"

#include "MoreInfo.h"


FPSCounter::FPSCounter() 
	: framerateCounter(65, 10, 30, ARIAL_FONT, sf::Color(255, 255, 0)){
}

void FPSCounter::renderTo(sf::RenderWindow& window) {
	framerateCounter.renderTo(window);
}

void FPSCounter::updateCounter() {
	fpsTimer = fpsClock.getElapsedTime();

	framerateCounter.updateOText("FPS: ", 1.0f / fpsTimer.asSeconds());
	fpsClock.restart().asSeconds();
}

