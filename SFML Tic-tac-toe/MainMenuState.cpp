#include <sstream>
#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	MainMenuState::MainMenuState(GameDataRef data) :
		data(data),
		background(nullptr),
		title(nullptr),
		playButton(nullptr),
		playButtonOuter(nullptr)
	{

	}

	void MainMenuState::Init()
	{
		data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);
		data->assets.LoadTexture("Play Button", MAIN_MENU_PLAY_BUTTON_FILEPATH);
		data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Main Menu Background"));
		title = new sf::Sprite(data->assets.GetTexture("Game Title"));
		playButton = new sf::Sprite(data->assets.GetTexture("Play Button"));
		playButtonOuter = new sf::Sprite(data->assets.GetTexture("Play Button Outer"));

		title->setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f) - (title->getGlobalBounds().size.x / 2.f), title->getGlobalBounds().size.y * 0.1));
		playButton->setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f) - (playButton->getGlobalBounds().size.x / 2.f), (SCREEN_HEIGTH / 2) - (playButton->getGlobalBounds().size.y / 2.f)));
		playButtonOuter->setPosition(sf::Vector2f((SCREEN_WIDTH / 2.f) - (playButtonOuter->getGlobalBounds().size.x / 2.f), (SCREEN_HEIGTH / 2) - (playButtonOuter->getGlobalBounds().size.y / 2.f)));
	}

	void MainMenuState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}

			if (data->input.IsSpriteClicked(*playButton, sf::Mouse::Button::Left, data->window))
			{
				data->machine.AddState(StateRef(new GameState(data)), true);
			}
		}
	}
	void MainMenuState::Update(float dt)
	{

	}
	void MainMenuState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);
		data->window.draw(*title);
		data->window.draw(*playButton);
		data->window.draw(*playButtonOuter);

		data->window.display();
	}
}