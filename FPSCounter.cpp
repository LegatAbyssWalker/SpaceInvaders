#include "FPSCounter.h"



//Constructors/Destructors
FPSCounter::FPSCounter() {
	gameFont.loadFromFile("res/fonts/Arial.ttf");
	framerateCounter.setFont(gameFont);
	framerateCounter.setFillColor(sf::Color(255, 255, 0));
	framerateCounter.setCharacterSize(30);
	framerateCounter.setPosition(0, 0);
}

FPSCounter::~FPSCounter() {
	//
}



//Functions
void FPSCounter::renderTo(sf::RenderWindow& window) {
	window.draw(framerateCounter);
}

void FPSCounter::update() {
	fpsTime = fpsClock.getElapsedTime();

	ssFPS.str("");
	ssFPS << "FPS: " << 1.0f / fpsTime.asSeconds();
	framerateCounter.setString(ssFPS.str());

	fpsClock.restart().asSeconds();
}