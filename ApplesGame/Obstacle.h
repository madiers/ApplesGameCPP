#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Obstacle
	{
		Position2D obstaclePos;
		sf::RectangleShape obstacleShape;
	};

	void InitObstacle(Obstacle& obstacle, sf::RenderWindow& window);
}