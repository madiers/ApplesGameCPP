﻿#include "Game.h"

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

		// Text

		gameState.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Medium.ttf");
		gameState.text.setFont(gameState.font);
		gameState.text.setString("Apples Eaten: ");
		gameState.text.setFillColor(sf::Color::White);
		gameState.text.setPosition(SCREEN_WIDTH / 2.f, SCRENN_HEIGHT / 6.f);
		gameState.text.setCharacterSize(24);

		// Sound
		gameState.bufferDeath.loadFromFile(RESOURCES_PATH + "\\Death.wav");
		gameState.soundDeath.setBuffer(gameState.bufferDeath);

		gameState.bufferApple.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav");
		gameState.soundApple.setBuffer(gameState.bufferApple);

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


		CheckDirection(gameState.player, deltaTime);

		IsWallsCollide(gameState, window);

		// Check on apples collision
		//Apple apple;

		for (size_t i = 0; i < NUM_APPLES; i++)
		{

			if (IsRectCollinde(gameState.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, gameState.apples[i].applesPos,
				{ APPLE_SIZE, APPLE_SIZE }))
			{
				gameState.numEatenApples++;
				gameState.soundApple.play();

				// Acceleratre Player with each eaten apple
				gameState.player.playerSpeed += 20.f;
				gameState.text.setString("Apples Eaten: " + std::to_string(gameState.numEatenApples));


				//Respawn the apple
				gameState.apples[i].applesPos = GetRandomPositionOnScreen(window);
				gameState.apples[i].sprite.setPosition(gameState.apples[i].applesPos.x, gameState.apples[i].applesPos.y);
			}
		}


		// Check on obstacle Collision

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{

			if (IsRectCollinde(gameState.player.playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, gameState.obstacles[i].obstaclePos,
				{ OBSTACLE_SIZE, OBSTACLE_SIZE }))
			{
				GameOver(gameState, window);

				break;
			}
		}



	}

	void DrawGame(Game& gameState, sf::RenderWindow& window)
	{

		// Draw Apples

		for (int i{ 0 }; i < NUM_APPLES; i++)
		{
			window.draw(gameState.apples[i].sprite);
		}

		// Draw Obstacles

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{
			window.draw(gameState.obstacles[i].sprite);
		}


		// Draw Player

		window.draw(gameState.player.sprite);

		// Draw Text
		window.draw(gameState.text);
	}

	void IsWallsCollide(Game& gameState, sf::RenderWindow& window)
	{
		if ((gameState.player.playerPosition.x + gameState.player.sprite.getScale().x / 2.f) > window.getSize().x ||
			(gameState.player.playerPosition.x - gameState.player.sprite.getScale().x / 2.f) < 0)
		{
			GameOver(gameState, window);
		}

		if ((gameState.player.playerPosition.y + gameState.player.sprite.getScale().y / 2.f) > window.getSize().y ||
			(gameState.player.playerPosition.y - gameState.player.sprite.getScale().y / 2.f) < 0)
		{
			GameOver(gameState, window);
		}

	}

	void GameOver(Game& gameState, sf::RenderWindow& window)
	{
		gameState.soundDeath.play();
		gameState.text.setString("Game Over!");
		window.clear();
		window.draw(gameState.text);
		sf::sleep(sf::seconds(2));
		sf::sleep(sf::seconds(2));
		//gameState.player.playerShape.setFillColor(sf::Color::Blue);
		InitGame(gameState, window);

	}

}
