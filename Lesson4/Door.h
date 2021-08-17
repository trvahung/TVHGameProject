#pragma once
#include <stdio.h>
#include <string.h>
namespace Door {
	class Context;

	class State
	{
	protected:
		Context* m_context;
	public:
		char* m_name = new char[10];
		virtual ~State() {
			delete[] m_name;
		};
		void setContext(Context* context);
		virtual char* getStateName() = 0;
		virtual void DoorControl(char key) = 0;
	};

	class Context
	{
	private:
		State* m_state;
	public:
		Context(State* state) : m_state(nullptr) {
			this->TransitionTo(state);
		};
		~Context();
		void TransitionTo(State* state);
		void Control(char key);
		void DoorState();
	};

	class LockedState :
		public State
	{
	public:
		char* getStateName() override;
		void DoorControl(char key) override;
	};

	class ClosedState :
		public State
	{
	public:
		char* getStateName() override;
		void DoorControl(char key) override;
	};

	class OpenedState :
		public State
	{
	public:
		char* getStateName() override;
		void DoorControl(char key) override;
	};

}
