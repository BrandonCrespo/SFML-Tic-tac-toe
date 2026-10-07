#include <sstream>
#include "GameState.h"

#include <iostream>

#include "PauseState.h"
#include "GameOverState.h"

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr),
		pauseButton(nullptr),
		gridSprite(nullptr)
	{
		for (int x = 0; x < GRID_COLUMS; x++)
		{
			for (int y = 0; y < GRID_ROWS; y++)
			{
				gridPieces[x][y] = nullptr;
			}
		}
	}

	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		ai = new AI(turn, data);

		data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Background"));
		pauseButton = new sf::Sprite(data->assets.GetTexture("Pause Button"));
		gridSprite = new sf::Sprite(data->assets.GetTexture("Grid Sprite"));

		pauseButton->setPosition(sf::Vector2f(data->window.getSize().x - pauseButton->getLocalBounds().size.x, pauseButton->getPosition().y));
		gridSprite->setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - (gridSprite->getGlobalBounds().size.x / 2), (SCREEN_HEIGHT / 2) - (gridSprite->getGlobalBounds().size.y / 2)));
	
		InitGridPieces();

		for (int x = 0; x < GRID_COLUMS; x++)
		{
			for (int y = 0; y < GRID_ROWS; y++)
			{
				gridArray[x][y] = EMPTY_PIECE;
			}
		}
	}

	void GameState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*pauseButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new PauseState(data)), false);
			}
			else if(data->input.IsSpriteClicked(*gridSprite, sf::Mouse::Button::Left, data->window))
			{
				if (STATE_PLAYING == gameState)
				{
					CheckAndPlacePiece();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
		{
			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER)
			{
				data->machine.AddState(StateRef(new GameOverState(data, gameState)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		data->window.draw(*pauseButton);
		data->window.draw(*gridSprite);
		for (int x = 0; x < GRID_COLUMS; x++)
		{
			for (int y = 0; y < GRID_ROWS; y++)
			{
				data->window.draw(*gridPieces[x][y]);
			}
		}

		data->window.display();
	}

	void GameState::InitGridPieces()
	{
		sf::Vector2u tempSpriteSize = data->assets.GetTexture("X Piece").getSize();

		for (int x = 0; x < GRID_COLUMS; x++)
		{
			for (int y = 0; y < GRID_ROWS; y++)
			{
				gridPieces[x][y] = new sf::Sprite(data->assets.GetTexture("X Piece"));
				gridPieces[x][y]->setPosition(sf::Vector2f(gridSprite->getPosition().x + (tempSpriteSize.x * x) - 7, gridSprite->getPosition().y + (tempSpriteSize.y * y) - 7));
				gridPieces[x][y]->setColor(sf::Color(255, 255, 255, 0));
			}

		}
	}
	void GameState::CheckAndPlacePiece()
	{
		sf::Vector2f touchPoint = data->input.GetMousePosition(data->window);
		sf::FloatRect gridSize = gridSprite->getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.size.x) / 2.f, (SCREEN_HEIGHT - gridSize.size.y) / 2.f);
	
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.size.x / GRID_COLUMS, gridSize.size.y / GRID_ROWS);

		int column = 0, row = 0;

		if (gridLocalTouchPos.x < gridSectionSize.x)
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2)
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.size.x)
		{
			column = 3;
		}

		if (gridLocalTouchPos.y < gridSectionSize.y)
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.size.y)
		{
			row = 3;
		}

		if (gridArray[column-1][row-1] == EMPTY_PIECE)
		{
			gridArray[column - 1][row - 1] = turn;

			if (PLAYER_PIECE == turn)
			{
				gridPieces[column -1][row-1]->setTexture(data->assets.GetTexture("X Piece"));

				CheckPlayerHasWon(turn);
			}

			gridPieces[column - 1][row - 1]->setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::CheckPlayerHasWon(int turn)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn);

		if (STATE_WON != gameState)
		{
			gameState = STATE_AI_PLAYING;

			ai->PlacePiece(&gridArray, &gridPieces, &gameState);

			Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
			Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
			Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
			Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
			Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
		}


		int emptyNum = GRID_COLUMS * GRID_ROWS;

		for (int x = 0; x < GRID_COLUMS; x++)
		{
			for (int y = 0; y < GRID_ROWS; y++)
			{
				if (EMPTY_PIECE != gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}

		if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState))
		{
			gameState = STATE_DRAW;
		}

		if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
		{
			clock.restart();
		}

		std::cout << gameState << std::endl;
	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3])
		{
			std::string winningPieceStr;

			if (O_PIECE == pieceToCheck)
			{
				winningPieceStr = "O Winning Piece";
			}
			else
			{
				winningPieceStr = "X Winning Piece";
			}

			gridPieces[x1][y1]->setTexture(data->assets.GetTexture(winningPieceStr));
			gridPieces[x2][y2]->setTexture(data->assets.GetTexture(winningPieceStr));
			gridPieces[x3][y3]->setTexture(data->assets.GetTexture(winningPieceStr));

			if (PLAYER_PIECE == pieceToCheck)
			{
				gameState = STATE_WON;
			}
			else
			{
				gameState = STATE_LOSE;
			}
		}
	}
}