#include "FPSCounter.h"

#include "MoreInfo.h"

FPSCounter::FPSCounter() {
	gameFont.loadFromFile(arialFont);
	framerateCounter.setFont(gameFont);
	framerateCounter.setFillColor(sf::Color(255, 255, 0));
	framerateCounter.setCharacterSize(30);
	framerateCounter.setPosition(0, 0);
}

void FPSCounter::renderTo(sf::RenderWindow& window) {
	window.draw(framerateCounter);
}

void FPSCounter::updateCounter() {
	fpsTimer = fpsClock.getElapsedTime();

	ssFPS.str("");
	ssFPS << "FPS: " << 1.0f / fpsTimer.asSeconds();
	framerateCounter.setString(ssFPS.str());

	fpsClock.restart().asSeconds();
}
