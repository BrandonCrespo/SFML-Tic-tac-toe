#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Sprite* background;
		sf::Sprite* title;
		sf::Sprite* playButton;
		sf::Sprite* playButtonOuter;
	};
}

