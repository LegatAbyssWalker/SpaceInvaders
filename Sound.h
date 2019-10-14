#ifndef SOUND_H
#define SOUND_H

#include "SFML/Audio.hpp"

class Sound {
	public:
		void setSound(std::string soundName, size_t volume, bool loopSound);
		void setMusic(std::string musicName, size_t volume, bool loopMusic);
		void stopSound();
		void stopMusic();

	private:
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;

		sf::Music music;
};

#endif