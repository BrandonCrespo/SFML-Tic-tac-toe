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

		data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);

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
				CheckAndPlacePiece();
			}
		}
	}
	void GameState::Update(float dt)
	{

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

		int column, row;

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

				turn = AI_PIECE;
			}
			else if (AI_PIECE == turn)
			{
				gridPieces[column - 1][row - 1]->setTexture(data->assets.GetTexture("O Piece"));

				turn = PLAYER_PIECE;
			}

			gridPieces[column - 1][row - 1]->setColor(sf::Color(255, 255, 255, 255));
		}
	}
}