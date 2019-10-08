#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "SFML/Graphics.hpp"

#include <memory>
#include <stack>

class State;

class StateMachine {
	public:
		StateMachine();
		
		void run(std::unique_ptr<State> state);

		void nextState();
		void lastState();

		void updateEvents();
		void update();
		void render();

		bool running();
		void quit();

		template <typename T>
		static std::unique_ptr<T> buildState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	private:
		//Stack of states
		std::stack<std::unique_ptr<State>> states;

		bool stateResume;
		bool stateRunning;
};

template <typename T>
std::unique_ptr<T> StateMachine::buildState(StateMachine& machine, sf::RenderWindow& window, bool replace) {
	return std::unique_ptr<T>(new T(machine, window, replace));
}

#endif