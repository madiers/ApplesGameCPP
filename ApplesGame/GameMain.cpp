// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH { 1200 };
const int SCRENN_HEIGHT{ 600 };
const float INITIAL_SPEED{ 100.f }; // Pixel per second
const float PLAYER_SIZE{ 20.f };
const int NUM_APPLES{ 20 };
const float APPLE_SIZE{ 20.f };




int main()
{

	//Initialization

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCRENN_HEIGHT), "Apples Game");
	window.setFramerateLimit(60);

	float playerX{ SCREEN_WIDTH / 2.f };
	float playerY{ SCRENN_HEIGHT / 2.f };
	float playerSpeed{ INITIAL_SPEED };
	int playerDirection{ 0 }; // 0 - Right, 1 - Up, 2 - Left, 3 - Down 
	int& playerDirectionPtr = playerDirection;


	// Init player
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

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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
		}

		if ((playerY + playerShape.getSize().y / 2.f) > window.getSize().y || (playerY - playerShape.getSize().y / 2.f) < 0)
		{
			playerShape.setFillColor(sf::Color::Blue);
		}

		// -------------DRAW--------------

		window.clear();
		playerShape.setPosition(playerX, playerY);



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
				isAppleEaten[i] = true;
				numEatenApples++;
				playerSpeed += 0.5f;
			}
		}



		// Draw Apples
		
		for (int i{ 0 }; i < NUM_APPLES; i++)
		{
			if (!isAppleEaten[i])
			{
				window.draw(applesShape[i]);
			}
		}



		// Draw Player

		window.draw(playerShape);
		window.display();
	}

	return 0;
}

