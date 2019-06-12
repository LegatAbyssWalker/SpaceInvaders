#ifndef PLAYSOUND_H
#define PLAYSOUND_H

#include "SFML/Audio.hpp"

class PlaySound {
	public:
		PlaySound();

		//Functions
		void setSound(std::string soundName, unsigned int volume, bool loopSound);
		void setMusic(std::string musicName, unsigned int volume, bool loopMusic);
		void stopSound();
		void stopMusic();

	private:
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;

		sf::Music music;
};

#endif