#pragma once

#include <memory>
#include <stack>

#include "State.h"

namespace ShowTime
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();

		void ProcessStateChanges();

		StateRef& GetActiveState();

	private:
		std::stack<StateRef> states;
		StateRef newState;

		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};
}

