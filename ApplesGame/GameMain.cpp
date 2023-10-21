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

int main()
{
	// Window Initialization


	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCRENN_HEIGHT), "Apples Game");
	window.setFramerateLimit(60);

	do
	{
		// Player Initialization

		Position2D playerPosition{ SCREEN_WIDTH / 2.f, SCRENN_HEIGHT / 2.f };

		// float playerX{ SCREEN_WIDTH / 2.f };
		// float playerY{ SCRENN_HEIGHT / 2.f };
		float playerSpeed{ INITIAL_SPEED };
		PlayerDirection playerDirection{ PlayerDirection::Right };
		PlayerDirection& playerDirectionPtr = playerDirection;


		// Init player Shape
		sf::RectangleShape playerShape;
		playerShape.setSize(sf::Vector2f(APPLE_SIZE, APPLE_SIZE));
		playerShape.setFillColor(sf::Color::Red);
		playerShape.setOrigin(PLAYER_SIZE/2.f, PLAYER_SIZE/2.f);
		playerShape.setPosition(playerPosition.x, playerPosition.y);


		// Init apples
		
		Position2D applesX[NUM_APPLES];
		Position2D applesY[NUM_APPLES];
		bool isAppleEaten[NUM_APPLES];

		sf::CircleShape applesShape[NUM_APPLES];
		
		// Init Obstacles
		float obstacleX[NUM_OBSTACLES];
		float obstacleY[NUM_OBSTACLES];

		sf::RectangleShape obstacleShapes[NUM_OBSTACLES];

		for (size_t i = 0; i < NUM_OBSTACLES; i++)
		{
			obstacleX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
			obstacleY[i] = rand() / (float)RAND_MAX * SCRENN_HEIGHT;

			obstacleShapes[i].setSize(sf::Vector2f(rand() / (float)RAND_MAX * 100, (rand() / (float)RAND_MAX * 100)));
			obstacleShapes[i].setOrigin(obstacleShapes[i].getSize().x / 2.f, obstacleShapes[i].getSize().y / 2.f);

			obstacleShapes[i].setPosition(obstacleX[i], obstacleY[i]);

			obstacleShapes[i].setFillColor(sf::Color::Magenta);
		}

		for (int i = 0; i < NUM_APPLES; i++)
		{
			isAppleEaten[i] = false;

			applesX[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
			applesY[i].y = rand() / (float)RAND_MAX * SCRENN_HEIGHT;

			applesShape[i].setRadius(APPLE_SIZE/2.f);
			applesShape[i].setFillColor(sf::Color::Blue);
			applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
			applesShape[i].setPosition(applesX[i].x, applesY[i].y);
		}

		int numEatenApples{ 0 };


		// Init game clock
		sf::Clock gameClock;
		float lastTime = gameClock.getElapsedTime().asSeconds();




		while (window.isOpen())
		{

	
			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;


			// Close on cross clicked

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					isGameRunning = false;
				}

			}

			// Chack on KeyPressed
			// I don't like Switch Case	так что и не использовал


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerDirection = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerDirection = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerDirection = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerDirection = PlayerDirection::Down;
			}

		
			if (playerDirection == PlayerDirection::Right) // Right
			{
				playerPosition.x += playerSpeed * deltaTime;
			}
			else if (playerDirection == PlayerDirection::Left) // Left
			{
				playerPosition.x -= playerSpeed * deltaTime;
			}
			else if (playerDirection == PlayerDirection::Up) // Up
			{
				playerPosition.y -= playerSpeed * deltaTime;
			}
			else if (playerDirection == PlayerDirection::Down) // Down
			{
				playerPosition.y += playerSpeed * deltaTime;
			}


			if ((playerPosition.x + playerShape.getSize().x / 2.f) > window.getSize().x || (playerPosition.x - playerShape.getSize().x / 2.f) < 0)
			{
				playerShape.setFillColor(sf::Color::Blue);
				break;
			}

			if ((playerPosition.y + playerShape.getSize().y / 2.f) > window.getSize().y || (playerPosition.y - playerShape.getSize().y / 2.f) < 0)
			{
				playerShape.setFillColor(sf::Color::Blue);
				break;
			}

			// Check on apples collision

			for (size_t i = 0; i < NUM_APPLES; i++)
			{
				/*if (!isAppleEaten[i])
				{
					float dx = abs(playerX - applesX[i]);
					float dy = abs(playerY - applesY[i]);

					if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
						dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
					{
						isAppleEaten[i] = true;
						numEatenApples++;
					}*/

				float sqDistance = (playerPosition.x - applesX[i].x) * (playerPosition.x - applesX[i].x) +
					(playerPosition.y - applesY[i].y) * (playerPosition.y - applesY[i].y);

				float sqRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
			
				if( sqDistance <= sqRadiusSum)
				{
					//isAppleEaten[i] = true;
					numEatenApples++;

					// Acceleratre Player with each eaten apple
					playerSpeed += 0.5f;

					//Respawn the apple

					applesX[i].x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesY[i].y = rand() / (float)RAND_MAX * SCRENN_HEIGHT;
					applesShape[i].setPosition(applesX[i].x, applesY[i].y);
				}
			}


			// Check on obstacle Collision

						

			for (size_t i = 0; i < NUM_OBSTACLES; i++)
			{
				float dx = abs(playerPosition.x - obstacleX[i]);
				float dy = abs(playerPosition.y - obstacleY[i]);

				if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
					dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
				{
					break;
				}
			}

			// -------------DRAW--------------

			window.clear();
			playerShape.setPosition(playerPosition.x, playerPosition.y);





			// Draw Apples
		
			for (int i{ 0 }; i < NUM_APPLES; i++)
			{
				if (!isAppleEaten[i])
				{
					window.draw(applesShape[i]);
				}
			}

			// Draw Obstacles

			for (size_t i = 0; i < NUM_OBSTACLES; i++)
			{
				window.draw(obstacleShapes[i]);
			}


			// Draw Player

			window.draw(playerShape);
			window.display();
		}
	} while (isGameRunning);
	return 0;
}

