#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		Position2D applesPos;
		sf::CircleShape applesShape;
	};

	void InitApple(Apple& apple, sf::RenderWindow& window);
}
