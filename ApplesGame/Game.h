#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Apple.h"

namespace ApplesGame
{
	struct Game
	{
<<<<<<< Updated upstream
=======
		// Textures
		sf::Texture playerTexture;
		sf::Texture appleTexture;

>>>>>>> Stashed changes
		// Player
		Player player;

		// Apples
		//Position2D applesPos[NUM_APPLES];
		//sf::CircleShape applesShape[NUM_APPLES];

		Apple apples[NUM_APPLES];

		// Scores 
		int numEatenApples{ 0 };

		// Obstacles
		Obstacle obstacles[NUM_OBSTACLES];

	};

	void InitGame(Game& gameState, sf::RenderWindow& window);

	void UpdateGame(Game& gameState, float& deltaTime, sf::RenderWindow& window);
}

