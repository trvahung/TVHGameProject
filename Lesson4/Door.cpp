#include "Door.h"
using namespace Door;
//class State
void State::setContext(Context* context) {
	this->m_context = context;
}

//class Context
Context::~Context() {
	delete m_state;
}

void Context::TransitionTo(State* state) {
	//printf("Transition to %s\n", state->getStateName());
	if (this->m_state != nullptr)
		delete this->m_state;
	this->m_state = state;
	this->m_state->setContext(this);
}

void Context::DoorState() {
	printf("Door is %s\n", this->m_state->getStateName());
}

void Context::Control(char key) {
	this->m_state->DoorControl(key);
}

//class LockedState
char* LockedState::getStateName() {
	strcpy(m_name, "LOCKED");
	return m_name;
}

void LockedState::DoorControl(char key) {
	if (key == 'l') {
		this->m_context->TransitionTo(new ClosedState);
	}
	if (key == 'o') {
		printf("Door is locked, cannot open\n");
	}
}

//class ClosedState
char* ClosedState::getStateName() {
	strcpy(m_name, "CLOSED");
	return m_name;
}

void ClosedState::DoorControl(char key) {
	if (key == 'l') {
		this->m_context->TransitionTo(new LockedState);
	}
	if (key == 'o') {
		this->m_context->TransitionTo(new OpenedState);
	}
}

//class OpenState
char* OpenedState::getStateName() {
	strcpy(m_name, "OPENED");
	return m_name;
}

void OpenedState::DoorControl(char key) {
	if (key == 'l') {
		printf("Door is opened, cannot lock\n");
	}
	if (key == 'o') {
		this->m_context->TransitionTo(new ClosedState);
	}
}