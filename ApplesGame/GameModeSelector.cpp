#include "SFML/Graphics.hpp"
#include "GameModeSelector.h"
#include "Constants.h"

namespace ApplesGame
{
	struct GameMode
	{
		private:
			bool isInfiniteApple{ false };
			bool isAcceleratable{ false };
		public:
			sf::Text Prompt;
			sf::Font font;
			void SetIsInfiniteApple(bool isInifinite) { isInfiniteApple = isInifinite; };
			void SetisAcceleratable(bool isAccelerate) { isAcceleratable = isAccelerate; };
			bool GetIsInfiniteApple() { return this->isInfiniteApple; };
			bool GetIsAcceleratable() { return this->isAcceleratable; };
		};

	void ModeSelect(sf::RenderWindow& window)
	{
		GameMode gameMode;

		gameMode.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Medium.ttf");
		gameMode.Prompt.setFont(gameMode.font);
		gameMode.Prompt.setString("Select Game Mode:\n 1 - 20 Apples | 2 - Infinte Apples \n 3 - Accelerate | 4 - Same Speed");
		gameMode.Prompt.setFillColor(sf::Color::White);
		gameMode.Prompt.setPosition(SCREEN_WIDTH / 12.f, SCRENN_HEIGHT / 6.f);

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
					isChosen = true;
					break;
					exit(0);
				}
			}
			window.clear();
			window.draw(gameMode.Prompt);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				isChosen = true;
				break;
			}

		}
	}
}