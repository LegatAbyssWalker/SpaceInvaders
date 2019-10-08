#include "StateMachine.h"
#include "State.h"

#include <iostream>
#include <memory>


StateMachine::StateMachine()
	: stateResume{ false }
	, stateRunning{ false } {
}

void StateMachine::run(std::unique_ptr<State> state) {
	stateRunning = true;
	states.push(std::move(state));
}

void StateMachine::nextState() {
	if (stateResume) {
		//Cleanup current state
		if (!states.empty()) { states.pop(); }

		stateResume = false;
	}

	if (!states.empty()) {
		std::unique_ptr<State> temp = states.top()->nextState();

		if (temp != nullptr) {
			if (temp->isReplacing()) {
				states.pop();
			}

			states.push(std::move(temp));
		}
	}
}

void StateMachine::lastState() {
	stateResume = true;
}

void StateMachine::updateEvents() {
	states.top()->updateEvents();
}

void StateMachine::update() {
	states.top()->update();
}

void StateMachine::render() {
	states.top()->render();
}

bool StateMachine::running() {
	return stateRunning;
}

void StateMachine::quit() {
	stateRunning = false;
}

