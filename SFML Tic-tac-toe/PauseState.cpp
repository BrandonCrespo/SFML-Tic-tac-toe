#include <sstream>
#include "PauseState.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "MainMenuState.h"


#include <iostream>

namespace ShowTime
{
	PauseState::PauseState(GameDataRef data) :
		data(data),
		background(nullptr),
		resumeButton(nullptr),
		homeButton(nullptr)
	{

	}

	void PauseState::Init()
	{
		data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Resume Button", RESUME_BUTTON_FILEPATH);
		data->assets.LoadTexture("Home Button", HOME_BUTTON_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Pause Background"));
		resumeButton = new sf::Sprite(data->assets.GetTexture("Resume Button"));
		homeButton = new sf::Sprite(data->assets.GetTexture("Home Button"));

		resumeButton->setPosition(sf::Vector2f((data->window.getSize().x / 2.f) - (resumeButton->getLocalBounds().size.x / 2.f), (data->window.getSize().y / 3.f) - (resumeButton->getLocalBounds().size.y / 2.f)));
		homeButton->setPosition(sf::Vector2f((data->window.getSize().x / 2.f) - (homeButton->getLocalBounds().size.x / 2.f), (data->window.getSize().y / 3.f * 2.f) - (homeButton->getLocalBounds().size.y / 2.f)));
	}

	void PauseState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*resumeButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.RemoveState();
			}

			if (data->input.IsSpriteClicked(*homeButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.RemoveState();

				data->machine.AddState(StateRef(new MainMenuState(data)), true);
			}
		}
	}
	void PauseState::Update(float dt)
	{

	}
	void PauseState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		data->window.draw(*resumeButton);
		data->window.draw(*homeButton);

		data->window.display();
	}
}