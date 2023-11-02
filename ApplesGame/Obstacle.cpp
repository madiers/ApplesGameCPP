#include "Obstacle.h"

namespace ApplesGame
{
	void InitObstacle(Obstacle& obstacle, sf::RenderWindow& window)
	{
		// Init Obstacles

		obstacle.obstaclePos = GetRandomPositionOnScreen(window);
		obstacle.obstacleShape.setSize({ OBSTACLE_SIZE,OBSTACLE_SIZE });
		obstacle.obstacleShape.setOrigin(obstacle.obstacleShape.getSize().x / 2.f,
			obstacle.obstacleShape.getSize().y / 2.f);
		obstacle.obstacleShape.setPosition(obstacle.obstaclePos.x,
			obstacle.obstaclePos.y);
		obstacle.obstacleShape.setFillColor(sf::Color::Magenta);
	}
}

