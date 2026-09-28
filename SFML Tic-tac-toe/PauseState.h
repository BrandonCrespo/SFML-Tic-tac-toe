#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* background;
		sf::Sprite* resumeButton;
		sf::Sprite* homeButton;
	};
}

