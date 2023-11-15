#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Apple.h"
#include "SFML/Audio.hpp"

namespace ApplesGame
{
	struct Game
	{
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

		// Text
		sf::Text text;
		sf::Font font;

		//Sound Effects

		// Game over
		sf::SoundBuffer bufferDeath;
		sf::Sound soundDeath;

		// Apple Eaten
		sf::SoundBuffer bufferApple;
		sf::Sound soundApple;
		
	};

	void InitGame(Game& gameState, sf::RenderWindow& window);

	void UpdateGame(Game& gameState, float& deltaTime, sf::RenderWindow& window);

	void DrawGame(Game& gameState, sf::RenderWindow& window);

	void IsWallsCollide(Game& gameState, sf::RenderWindow& window);

	void GameOver(Game& gameState, sf::RenderWindow& window);
}

