#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "DEFINITIONS.h"
#include "Game.h"

namespace ShowTime
{
	class AI
	{
	public:
		AI(int playerPiece, GameDataRef data);

		void PlacePiece(int (*gridArray)[GRID_COLUMS][GRID_ROWS], sf::Sprite* (*gridPieces)[GRID_COLUMS][GRID_ROWS], int* gameState);

	private:
		void CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int (*gridArray)[GRID_COLUMS][GRID_ROWS], sf::Sprite* (*gridPieces)[GRID_COLUMS][GRID_ROWS]);
	
		void CheckIfPieceIsEmpty(int X, int Y, int (*gridArray)[GRID_COLUMS][GRID_ROWS], sf::Sprite* (*gridPieces)[GRID_COLUMS][GRID_ROWS]);
	
		int aiPiece;
		int playerPiece;

		std::vector<std::array<int, 6>> checkMatchVector;

		GameDataRef data;
	};
}

