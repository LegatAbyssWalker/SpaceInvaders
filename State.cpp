#include "State.h"



State::State(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: machine{ machine }
	, window{ window }
	, replacing{ replace } {
}

std::unique_ptr<State> State::nextState() {
	return std::move(next);
}

bool State::isReplacing() {
	return replacing;
}
