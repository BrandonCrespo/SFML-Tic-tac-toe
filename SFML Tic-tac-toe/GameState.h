#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"

#include "AI.h"

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

		void CheckAndPlacePiece();

		void CheckPlayerHasWon(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

		GameDataRef data;

		sf::Sprite* background;
		sf::Sprite* pauseButton;
		sf::Sprite* gridSprite;
		sf::Sprite* gridPieces[GRID_COLUMS][GRID_ROWS];
		int gridArray[GRID_COLUMS][GRID_ROWS];

		int turn;
		int gameState;

		AI* ai;
	};
}

