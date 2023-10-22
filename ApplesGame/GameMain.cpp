// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Math.h"
#include "Player.h"


// Window
const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH { 1200 };
const int SCRENN_HEIGHT{ 600 };
bool isGameRunning{ true };
int seed = (int)time(nullptr);


// Player
const float INITIAL_SPEED{ 100.f }; // Pixel per second
const float PLAYER_SIZE{ 20.f };

// Apples
const int NUM_APPLES{ 20 };
const float APPLE_SIZE{ 20.f };




// Obstacles
const float OBSTACLE_SIZE{ 20.f };
 const int NUM_OBSTACLES{ 5 };

// Game Structs






struct Apple
{
	Position2D applesPos;
	sf::CircleShape applesShape;
};



struct Obstacle
{
	Position2D obstaclePos;
	sf::RectangleShape obstacleShape;
};






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

};


void InitApple(Apple& apple, sf::RenderWindow& window)
{
	// Init apple

	apple.applesPos = GetRandomPositionOnScreen(window);
	apple.applesShape.setRadius(APPLE_SIZE / 2.f);
	apple.applesShape.setFillColor(sf::Color::Blue);
	apple.applesShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	apple.applesShape.setPosition(apple.applesPos.x, apple.applesPos.y);
	
}

void InitObstacle(Obstacle& obstacle, sf::RenderWindow& window)
{
	// Init Obstacles

	obstacle.obstaclePos = GetRandomPositionOnScreen(window);
	obstacle.obstacleShape.setSize({OBSTACLE_SIZE,OBSTACLE_SIZE});
	obstacle.obstacleShape.setOrigin(obstacle.obstacleShape.getSize().x / 2.f,
		obstacle.obstacleShape.getSize().y / 2.f);
	obstacle.obstacleShape.setPosition(obstacle.obstaclePos.x,
		obstacle.obstaclePos.y);
	obstacle.obstacleShape.setFillColor(sf::Color::Magenta);
}


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
		//apple = gameState.apples[i];
		if (IsRectCircleCollide(gameState.player.playerPosition, 
			gameState.player.playerShape.getSize().x, 
			gameState.apples[i].applesPos,
			gameState.apples[i].applesShape.getRadius()))
		{
			gameState.numEatenApples++;

			// Acceleratre Player with each eaten apple
			gameState.player.playerSpeed += 0.5f;


			//Respawn the apple
			gameState.apples[i].applesPos = GetRandomPositionOnScreen(window);
			gameState.apples[i].applesShape.setPosition(gameState.apples[i].applesPos.x, gameState.apples[i].applesPos.y);
		}
	}


	// Check on obstacle Collision

	for (size_t i = 0; i < NUM_OBSTACLES; i++)
	{
		
		if (IsRectCollinde(gameState.player.playerPosition, {PLAYER_SIZE, PLAYER_SIZE}, gameState.obstacles[i].obstaclePos,
			{OBSTACLE_SIZE, OBSTACLE_SIZE}))
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

void DeinitializeGame(Game& gameState)
{

}


int main()
{
	// Window Initialization

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCRENN_HEIGHT), "Apples Game");
	window.setFramerateLimit(60);
	

	Game gameState;
	
	do
	{
		// Initialization

		InitGame(gameState, window);

		// Init game clock
		sf::Clock gameClock;
		float lastTime = gameClock.getElapsedTime().asSeconds();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					isGameRunning = false;
				}
			}


			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Close on cross clicked


			window.clear();
			UpdateGame(gameState, deltaTime, window);
			window.display();

		}
	} while (isGameRunning);

	DeinitializeGame(gameState);

	return 0;
}

