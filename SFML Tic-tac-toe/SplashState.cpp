#include <sstream>
#include "SplashState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace ShowTime
{
	SplashState::SplashState(GameDataRef data) :
		data(data),
		background(nullptr)
	{

	}

	void SplashState::Init()
	{
		data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		background = new sf::Sprite(data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput()
	{
		while (auto event = data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				data->window.close();
			}
		}
	}
	void SplashState::Update(float dt)
	{
		if (clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			data->machine.AddState(StateRef(new MainMenuState(data)), true);
		}
	}
	void SplashState::Draw(float dt)
	{
		data->window.clear();

		data->window.draw(*background);

		data->window.display();
	}
}