// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include "Game.h"
#include "GameModeSelector.h"



int seed = (int)time(nullptr);

bool isGameRunning{ true };



int main()
{
	using namespace ApplesGame;
	// Window Initialization

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCRENN_HEIGHT), "Apples Game");
	
	Game gameState;
	ModeSelect(window);
	
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
					return 0;
				}
			}


			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Close on cross clicked


			window.clear();
			UpdateGame(gameState, deltaTime, window);
			DrawGame(gameState, window);
			window.display();

		}
	} while (isGameRunning);

	//DeinitializeGame(gameState);

	return 0;
}

