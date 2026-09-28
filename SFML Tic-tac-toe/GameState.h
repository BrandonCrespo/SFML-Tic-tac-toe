#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* background;
		sf::Sprite* pauseButton;

		int turn;
		int gameState;
	};
}

