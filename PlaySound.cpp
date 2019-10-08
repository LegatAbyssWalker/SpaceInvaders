#include "PlaySound.h"

void PlaySound::setSound(std::string soundName, size_t volume, bool loopSound) {
	soundBuffer.loadFromFile(soundName);
	sound.setBuffer(soundBuffer);

	sound.setVolume(volume);
	sound.setLoop(loopSound);

	sound.play();
}

void PlaySound::setMusic(std::string musicName, size_t volume, bool loopMusic) {
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
