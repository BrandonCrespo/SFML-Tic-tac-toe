#pragma once
#include <SFML/Graphics.hpp>

namespace ShowTime
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		sf::Vector2f GetMousePosition(sf::RenderWindow& window);
	};
}

