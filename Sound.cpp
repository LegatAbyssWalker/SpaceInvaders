#include "Sound.h"

void Sound::setSound(std::string soundName, size_t volume, bool loopSound) {
	soundBuffer.loadFromFile(soundName);
	sound.setBuffer(soundBuffer);

	sound.setVolume(volume);
	sound.setLoop(loopSound);

	sound.play();
}

void Sound::setMusic(std::string musicName, size_t volume, bool loopMusic) {
	music.openFromFile(musicName);

	music.setVolume(volume);
	music.setLoop(loopMusic);

	music.play();
}

void Sound::stopSound() {
	sound.stop();
}

void Sound::stopMusic() {
	music.stop();
}
