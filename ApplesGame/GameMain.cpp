// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>


// Window
const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH { 1200 };
const int SCRENN_HEIGHT{ 600 };
bool isGameRunning{ true };

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

struct Vector2D
{
	float x{ 0 };
	float y{ 0 };
};

enum class PlayerDirection
{
	Right = 0,
	Up,
	Left,
	Down
};

typedef Vector2D Position2D;


Position2D GetRandomPositionOnScreen(sf::RenderWindow& window)
{
	Position2D result;
	result.x = rand() / (float)RAND_MAX * window.getSize().x;
	result.y = rand() / (float)RAND_MAX * window.getSize().y;
	return result;
}


bool IsRectCollinde(Position2D& rectPos1, Vector2D rectSize1,
	Position2D& rectPos2, Vector2D rectSize2)
{
	float dx = abs(rectPos1.x - rectPos2.x);
	float dy = abs(rectPos1.y - rectPos2.y);

	return (dx <= (rectSize1.x + rectSize2.x) / 2.f &&
		dy <= (rectSize1.y + rectSize2.y) / 2.f);
}

bool IsRectCircleCollide(Position2D& rectPos, float rectSize, Position2D& circlePos, float circleRadius)
{
	float sqDistance = (rectPos.x - circlePos.x) * (rectPos.x - circlePos.x) +
		(rectPos.y - circlePos.y) * (rectPos.y - circlePos.y);

	float sqRadiusSum = (rectSize + circleRadius) * (rectSize + circleRadius) / 4;

	return sqDistance <= sqRadiusSum;
}

struct GameState
{
	// Player
	Position2D playerPosition;
	float playerSpeed{ INITIAL_SPEED };
	PlayerDirection playerDirection{ PlayerDirection::Right };
	sf::RectangleShape playerShape;
	
	// Apples
	Position2D applesPos[NUM_APPLES];
	sf::CircleShape applesShape[NUM_APPLES];

	// Scores 
	int numEatenApples{ 0 };

	// Obstacles
	Position2D obstaclePos[NUM_OBSTACLES];
	sf::RectangleShape obstacleShapes[NUM_OBSTACLES];
};

void InitGame(GameState& gameState, sf::RenderWindow& window)
{
	
	// Init Player Settings

	gameState.playerPosition = { window.getSize().x / 2.f, window.getSize().y / 2.f };
	gameState.playerSpeed = INITIAL_SPEED;
	gameState.playerDirection = PlayerDirection::Right;

	// Init player Shape

	gameState.playerShape.setSize(sf::Vector2f(APPLE_SIZE, APPLE_SIZE));
	gameState.playerShape.setFillColor(sf::Color::Red);
	gameState.playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);


	// Init apples



	for (int i = 0; i < NUM_APPLES; i++)
	{
		gameState.applesPos[i] = GetRandomPositionOnScreen(window);
		gameState.applesShape[i].setRadius(APPLE_SIZE / 2.f);
		gameState.applesShape[i].setFillColor(sf::Color::Blue);
		gameState.applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		gameState.applesShape[i].setPosition(gameState.applesPos[i].x, gameState.applesPos[i].y);
	}


	// Init Obstacles

	for (size_t i = 0; i < NUM_OBSTACLES; i++)
	{
		gameState.obstaclePos[i] = GetRandomPositionOnScreen(window);
		gameState.obstacleShapes[i].setSize({OBSTACLE_SIZE, OBSTACLE_SIZE});
		gameState.obstacleShapes[i].setOrigin(gameState.obstacleShapes[i].getSize().x / 2.f, gameState.obstacleShapes[i].getSize().y / 2.f);
		gameState.obstacleShapes[i].setPosition(gameState.obstaclePos[i].x, gameState.obstaclePos[i].y);
		gameState.obstacleShapes[i].setFillColor(sf::Color::Magenta);
	}

	int numEatenApples{ 0 };

}


void UpdateGame(GameState& gameState, float& deltaTime, sf::RenderWindow& window)
{
	// Check on KeyPressed
	// I don't like Switch Case	так что и не использовал


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameState.playerDirection = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameState.playerDirection = PlayerDirection::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameState.playerDirection = PlayerDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameState.playerDirection = PlayerDirection::Down;
	}


	if (gameState.playerDirection == PlayerDirection::Right) // Right
	{
		gameState.playerPosition.x += gameState.playerSpeed * deltaTime;
	}
	else if (gameState.playerDirection == PlayerDirection::Left) // Left
	{
		gameState.playerPosition.x -= gameState.playerSpeed * deltaTime;
	}
	else if (gameState.playerDirection == PlayerDirection::Up) // Up
	{
		gameState.playerPosition.y -= gameState.playerSpeed * deltaTime;
	}
	else if (gameState.playerDirection == PlayerDirection::Down) // Down
	{
		gameState.playerPosition.y += gameState.playerSpeed * deltaTime;
	}

	// Walls Collide

	if ((gameState.playerPosition.x + gameState.playerShape.getSize().x / 2.f) > window.getSize().x || (gameState.playerPosition.x - gameState.playerShape.getSize().x / 2.f) < 0)
	{
		gameState.playerShape.setFillColor(sf::Color::Blue);
		InitGame(gameState, window);
	}

	if ((gameState.playerPosition.y + gameState.playerShape.getSize().y / 2.f) > window.getSize().y || (gameState.playerPosition.y - gameState.playerShape.getSize().y / 2.f) < 0)
	{
		gameState.playerShape.setFillColor(sf::Color::Blue);
		InitGame(gameState, window);
	}

	// Check on apples collision

	for (size_t i = 0; i < NUM_APPLES; i++)
	{

		if (IsRectCircleCollide(gameState.playerPosition, gameState.playerShape.getSize().x, gameState.applesPos[i], 
			gameState.applesShape[i].getRadius()))
		{
			gameState.numEatenApples++;

			// Acceleratre Player with each eaten apple
			gameState.playerSpeed += 0.5f;

			//Respawn the apple

			gameState.applesPos[i] = GetRandomPositionOnScreen(window);
			gameState.applesShape[i].setPosition(gameState.applesPos[i].x, gameState.applesPos[i].y);
		}
	}


	// Check on obstacle Collision

	for (size_t i = 0; i < NUM_OBSTACLES; i++)
	{
		
		if (IsRectCollinde(gameState.playerPosition, {PLAYER_SIZE, PLAYER_SIZE}, gameState.obstaclePos[i], {OBSTACLE_SIZE, OBSTACLE_SIZE}))
		{
			InitGame(gameState, window);
			break;
		}
	}

	

	// -------------DRAW--------------

	gameState.playerShape.setPosition(gameState.playerPosition.x, gameState.playerPosition.y);


	// Draw Apples

	for (int i{ 0 }; i < NUM_APPLES; i++)
	{
		window.draw(gameState.applesShape[i]);
	}

	// Draw Obstacles

	for (size_t i = 0; i < NUM_OBSTACLES; i++)
	{
		window.draw(gameState.obstacleShapes[i]);
	}


	// Draw Player

	window.draw(gameState.playerShape);

}

void DeinitializeGame(GameState& gameState)
{

}


int main()
{
	// Window Initialization

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCRENN_HEIGHT), "Apples Game");
	window.setFramerateLimit(60);
	

	GameState gameState;
	
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

