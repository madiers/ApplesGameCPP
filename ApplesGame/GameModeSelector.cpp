#include "SFML/Graphics.hpp"
#include "GameModeSelector.h"
#include "Constants.h"


namespace ApplesGame
{
	enum UserGameSettingsBitMask
	{
		AcceleratePlayer = 1 << 0,
		InifiniteApples = 1 << 1
	};

	void ModeSelect(sf::RenderWindow& window, GameMode& gameMode)
	{
		
		gameMode.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Medium.ttf");
		gameMode.Prompt.setFont(gameMode.font);

		//Set fonts
		gameMode.firstMode.setFont(gameMode.font);
		gameMode.secondMode.setFont(gameMode.font);
		gameMode.thirdMode.setFont(gameMode.font);
		gameMode.fourthMode.setFont(gameMode.font);

		//Set texts
		gameMode.Prompt.setString("Select Game Mode and press ENTER:");
		gameMode.firstMode.setString("1 - 20 Apples");
		gameMode.secondMode.setString("2 - Infinte Apples");
		gameMode.thirdMode.setString("3 - Accelerate");
		gameMode.fourthMode.setString("4 - Same Speed:");

		//Set Colors
		gameMode.Prompt.setFillColor(sf::Color::White);
		gameMode.firstMode.setFillColor(sf::Color::White);
		gameMode.secondMode.setFillColor(sf::Color::White);
		gameMode.thirdMode.setFillColor(sf::Color::White);
		gameMode.fourthMode.setFillColor(sf::Color::White);

		//Set positions
		gameMode.Prompt.setPosition(SCREEN_WIDTH / 12.f, (SCRENN_HEIGHT / 6.f) - 30.f);
		gameMode.firstMode.setPosition(SCREEN_WIDTH / 12.f, (SCRENN_HEIGHT / 6.f) + 30.f);
		gameMode.secondMode.setPosition(SCREEN_WIDTH / 12.f, (SCRENN_HEIGHT / 6.f) + 70.f);
		gameMode.thirdMode.setPosition(SCREEN_WIDTH / 12.f, (SCRENN_HEIGHT / 6.f) + 120.f);
		gameMode.fourthMode.setPosition(SCREEN_WIDTH / 12.f, (SCRENN_HEIGHT / 6.f) + 160.f);

		bool isChosen{ false };
		
		while (!isChosen || window.isOpen())
		{
			// Window Closed Event
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					exit(0);
					isChosen = true;
					break;
				}
			}

			window.clear();
			window.draw(gameMode.Prompt);
			window.draw(gameMode.firstMode);
			window.draw(gameMode.secondMode);
			window.draw(gameMode.thirdMode);
			window.draw(gameMode.fourthMode);
			window.display();
			
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				gameMode.firstMode.setFillColor(sf::Color::Red);
				gameMode.secondMode.setFillColor(sf::Color::White);
				//gameMode.SetIsInfiniteApple(false);

				window.draw(gameMode.firstMode);
			}			
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				gameMode.firstMode.setFillColor(sf::Color::White);
				gameMode.secondMode.setFillColor(sf::Color::Red);
				//gameMode.SetIsInfiniteApple(true);

				window.draw(gameMode.secondMode);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				gameMode.thirdMode.setFillColor(sf::Color::Red);
				gameMode.fourthMode.setFillColor(sf::Color::White);
				//gameMode.SetisAcceleratable(false);

				window.draw(gameMode.thirdMode);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				gameMode.thirdMode.setFillColor(sf::Color::White);
				gameMode.fourthMode.setFillColor(sf::Color::Red);
				//gameMode.SetisAcceleratable(true);
				
				window.draw(gameMode.fourthMode);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				isChosen = true;
				break;
			}


		}
	}
}