#include "Obstacle.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitObstacle(Obstacle& obstacle, sf::RenderWindow& window)
	{
		// Init Obstacles

		obstacle.obstaclePos = GetRandomPositionOnScreen(window);

		obstacle.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png");
		obstacle.sprite.setTexture(obstacle.rockTexture);
		SetSpriteSize(obstacle.sprite, 15.f, 15.f);

		obstacle.obstacleShape.setSize({ OBSTACLE_SIZE,OBSTACLE_SIZE });
		obstacle.obstacleShape.setOrigin(obstacle.obstacleShape.getSize().x / 2.f,
			obstacle.obstacleShape.getSize().y / 2.f);
		obstacle.obstacleShape.setPosition(obstacle.obstaclePos.x,
			obstacle.obstaclePos.y);
		obstacle.obstacleShape.setFillColor(sf::Color::Magenta);

		obstacle.sprite.setPosition(obstacle.obstaclePos.x, obstacle.obstaclePos.y);
	}
	void DrawObstacle(Obstacle *obstacles, sf::RenderWindow& window)
	{
		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{
			window.draw(obstacles[i].sprite);
		}
	}
}

