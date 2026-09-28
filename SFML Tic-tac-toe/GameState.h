#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"

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
		void InitGridPieces();

		GameDataRef data;

		sf::Sprite* background;
		sf::Sprite* pauseButton;
		sf::Sprite* gridSprite;
		sf::Sprite* gridPieces[GRID_COLUMS][GRID_ROWS];
		int gridArray[GRID_COLUMS][GRID_ROWS];

		int turn;
		int gameState;
	};
}

