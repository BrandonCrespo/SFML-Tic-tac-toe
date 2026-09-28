#include <sstream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "MainMenuState.h"


#include <iostream>

namespace ShowTime
{
	GameOverState::GameOverState(GameDataRef data) :
		data(data),
		retryButton(nullptr),
		homeButton(nullptr)
	{

	}

	void GameOverState::Init()
	{
		data->assets.LoadTexture("Retry Button", RETRY_BUTTON_FILEPATH);
		data->assets.LoadTexture("Home Button", HOME_BUTTON_FILEPATH);

		retryButton = new sf::Sprite(data->assets.GetTexture("Retry Button"));
		homeButton = new sf::Sprite(data->assets.GetTexture("Home Button"));

		retryButton->setPosition(sf::Vector2f((data->window.getSize().x / 2.f) - (retryButton->getLocalBounds().size.x / 2.f), (data->window.getSize().y / 3.f) - (retryButton->getLocalBounds().size.y / 2.f)));
		homeButton->setPosition(sf::Vector2f((data->window.getSize().x / 2.f) - (homeButton->getLocalBounds().size.x / 2.f), (data->window.getSize().y / 3.f * 2.f) - (homeButton->getLocalBounds().size.y / 2.f)));
	}

	void GameOverState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*retryButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new GameState(data)), true);
			}

			if (data->input.IsSpriteClicked(*homeButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new MainMenuState(data)), true);
			}
		}
	}
	void GameOverState::Update(float dt)
	{

	}
	void GameOverState::Draw(float dt)
	{
		data->window.clear(sf::Color::Red);

		data->window.draw(*retryButton);
		data->window.draw(*homeButton);

		data->window.display();
	}
}