#include "InputManager.h"

namespace ShowTime
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::FloatRect tempRect(object.getPosition(), object.getGlobalBounds().size);
			if (tempRect.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				return true;
			}
		}
		return false;
	}
	sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Vector2f(sf::Mouse::getPosition(window));
	}
}
