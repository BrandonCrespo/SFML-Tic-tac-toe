#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ShowTime
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		void Init() override;
		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

	private:
		GameDataRef data;

		sf::Clock clock;

		sf::Sprite* background;
	};
}

