#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

#include "PauseState.h"

namespace ShowTime
{
	GameState::GameState(GameDataRef data) :
		data(data),
		background(nullptr),
		pauseButton(nullptr)
	{

	}

	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Game Background"));
		pauseButton = new sf::Sprite(data->assets.GetTexture("Pause Button"));

		pauseButton->setPosition(sf::Vector2f(data->window.getSize().x - pauseButton->getLocalBounds().size.x, pauseButton->getPosition().y));
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

		data->window.display();
	}
}