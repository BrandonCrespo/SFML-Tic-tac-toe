#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int gameOverState);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* retryButton;
		sf::Sprite* homeButton;

		int gameState;
	};
}

