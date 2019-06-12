#include "PlaySound.h"



PlaySound::PlaySound() {
	//
}

void PlaySound::setSound(std::string soundName, unsigned int volume, bool loopSound) {
	soundBuffer.loadFromFile(soundName);
	sound.setBuffer(soundBuffer);

	sound.setVolume(volume);
	sound.setLoop(loopSound);

	sound.play();
}

void PlaySound::setMusic(std::string musicName, unsigned int volume, bool loopMusic) {
	music.openFromFile(musicName);

	music.setVolume(volume);
	music.setLoop(loopMusic);

	music.play();
}

void PlaySound::stopSound() {
	sound.stop();
}

void PlaySound::stopMusic() {
	music.stop();
}