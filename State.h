#ifndef STATE_H
#define STATE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#include <memory>

class StateMachine;

class State {
	public:
		State(StateMachine& machine, sf::RenderWindow& window, bool replace = true);
		virtual ~State() = default;

		State(const State&) = delete;
		State& operator = (const State&) = delete;

		virtual void updateEvents() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		std::unique_ptr<State> nextState();
		
		bool isReplacing();


	protected:
		StateMachine& machine;
		sf::RenderWindow& window;

		bool replacing;

		std::unique_ptr<State> next;
};

#endif