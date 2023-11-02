#include "Game.h"

namespace ApplesGame
{

	void InitGame(Game& gameState, sf::RenderWindow& window)
	{
		InitPlayer(gameState.player, window, PLAYER_SIZE, INITIAL_SPEED);

		for (size_t i = 0; i < NUM_APPLES; i++)
		{
			InitApple(gameState.apples[i], window);
		}

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{
			InitObstacle(gameState.obstacles[i], window);
		}

		int numEatenApples{ 0 };
	}

	void UpdateGame(Game& gameState, float& deltaTime, sf::RenderWindow& window)
	{
		// Check on KeyPressed
		// I don't like Switch Case	так что и не использовал


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameState.player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameState.player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameState.player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameState.player.playerDirection = PlayerDirection::Down;
		}


		if (gameState.player.playerDirection == PlayerDirection::Right) // Right
		{
			gameState.player.playerPosition.x += gameState.player.playerSpeed * deltaTime;
		}
		else if (gameState.player.playerDirection == PlayerDirection::Left) // Left
		{
			gameState.player.playerPosition.x -= gameState.player.playerSpeed * deltaTime;
		}
		else if (gameState.player.playerDirection == PlayerDirection::Up) // Up
		{
			gameState.player.playerPosition.y -= gameState.player.playerSpeed * deltaTime;
		}
		else if (gameState.player.playerDirection == PlayerDirection::Down) // Down
		{
			gameState.player.playerPosition.y += gameState.player.playerSpeed * deltaTime;
		}

		// Walls Collide

		if ((gameState.player.playerPosition.x + gameState.player.playerShape.getSize().x / 2.f) > window.getSize().x ||
			(gameState.player.playerPosition.x - gameState.player.playerShape.getSize().x / 2.f) < 0)
		{
			gameState.player.playerShape.setFillColor(sf::Color::Blue);
			InitGame(gameState, window);
		}

		if ((gameState.player.playerPosition.y + gameState.player.playerShape.getSize().y / 2.f) > window.getSize().y ||
			(gameState.player.playerPosition.y - gameState.player.playerShape.getSize().y / 2.f) < 0)
		{
			gameState.player.playerShape.setFillColor(sf::Color::Blue);
			InitGame(gameState, window);
		}

		// Check on apples collision
		//Apple apple;

		for (size_t i = 0; i < NUM_APPLES; i++)
		{

			if (IsRectCircleCollide(gameState.player.playerPosition,
				gameState.player.playerShape.getSize().x,
				gameState.apples[i].applesPos,
				gameState.apples[i].applesShape.getRadius()))
			{
				gameState.numEatenApples++;

				// Acceleratre Player with each eaten apple
				gameState.player.playerSpeed += 20.f;


				//Respawn the apple
				gameState.apples[i].applesPos = GetRandomPositionOnScreen(window);
				gameState.apples[i].applesShape.setPosition(gameState.apples[i].applesPos.x, gameState.apples[i].applesPos.y);
			}
		}


		// Check on obstacle Collision

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{

			if (IsRectCollinde(gameState.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, gameState.obstacles[i].obstaclePos,
				{ OBSTACLE_SIZE, OBSTACLE_SIZE }))
			{
				InitGame(gameState, window);
				break;
			}
		}



		// -------------DRAW--------------

		gameState.player.playerShape.setPosition(gameState.player.playerPosition.x, gameState.player.playerPosition.y);


		// Draw Apples

		for (int i{ 0 }; i < NUM_APPLES; i++)
		{
			window.draw(gameState.apples[i].applesShape);
		}

		// Draw Obstacles

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{
			window.draw(gameState.obstacles[i].obstacleShape);
		}


		// Draw Player

		window.draw(gameState.player.playerShape);

	}

}
