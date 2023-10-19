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
		float playerX{ SCREEN_WIDTH / 2.f };
		float playerY{ SCRENN_HEIGHT / 2.f };
		float playerSpeed{ INITIAL_SPEED };
		int playerDirection{ 0 }; // 0 - Right, 1 - Up, 2 - Left, 3 - Down 
		int& playerDirectionPtr = playerDirection;


		// Init player Shape
		sf::RectangleShape playerShape;
		playerShape.setSize(sf::Vector2f(APPLE_SIZE, APPLE_SIZE));
		playerShape.setFillColor(sf::Color::Red);
		playerShape.setOrigin(PLAYER_SIZE/2.f, PLAYER_SIZE/2.f);
		playerShape.setPosition(playerX, playerY);


		// Init apples
		float applesX[NUM_APPLES];
		float applesY[NUM_APPLES];
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

			applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
			applesY[i] = rand() / (float)RAND_MAX * SCRENN_HEIGHT;

			applesShape[i].setRadius(APPLE_SIZE/2.f);
			applesShape[i].setFillColor(sf::Color::Blue);
			applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
			applesShape[i].setPosition(applesX[i], applesY[i]);
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerDirection = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerDirection = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerDirection = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerDirection = 3;
			}

		
			if (playerDirection == 0) // Right
			{
				playerX += playerSpeed * deltaTime;
			}
			else if (playerDirection == 2) // Left
			{
				playerX -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 1) // Up
			{
				playerY -= playerSpeed * deltaTime;
			}
			else if (playerDirection == 3) // Down
			{
				playerY += playerSpeed * deltaTime;
			}


			if ((playerX + playerShape.getSize().x / 2.f) > window.getSize().x || (playerX - playerShape.getSize().x / 2.f) < 0)
			{
				playerShape.setFillColor(sf::Color::Blue);
				break;
			}

			if ((playerY + playerShape.getSize().y / 2.f) > window.getSize().y || (playerY - playerShape.getSize().y / 2.f) < 0)
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

				float sqDistance = (playerX - applesX[i]) * (playerX - applesX[i]) +
					(playerY - applesY[i]) * (playerY - applesY[i]);

				float sqRadiusSum = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4;
			
				if( sqDistance <= sqRadiusSum)
				{
					//isAppleEaten[i] = true;
					numEatenApples++;

					// Acceleratre Player with each eaten apple
					playerSpeed += 0.5f;

					//Respawn the apple

					applesX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
					applesY[i] = rand() / (float)RAND_MAX * SCRENN_HEIGHT;
					applesShape[i].setPosition(applesX[i], applesY[i]);
				}
			}


			// Check on obstacle Collision

						

			for (size_t i = 0; i < NUM_OBSTACLES; i++)
			{
				float dx = abs(playerX - obstacleX[i]);
				float dy = abs(playerY - obstacleY[i]);

				if (dx <= (APPLE_SIZE + PLAYER_SIZE) / 2.f &&
					dy <= (APPLE_SIZE + PLAYER_SIZE) / 2.f)
				{
					break;
				}
			}

			// -------------DRAW--------------

			window.clear();
			playerShape.setPosition(playerX, playerY);





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

