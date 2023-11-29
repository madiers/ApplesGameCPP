#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct GameMode
	{
		bool isInfiniteApple{ false };
		bool isAcceleratable{ false };

		sf::Text Prompt;
		sf::Text firstMode;
		sf::Text secondMode;
		sf::Text thirdMode;
		sf::Text fourthMode;
		sf::Font font;
	};
}