#include "Apple.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, sf::RenderWindow& window)
	{
		// Init apple
		apple.applesPos = GetRandomPositionOnScreen(window);
		apple.applesShape.setRadius(APPLE_SIZE / 2.f);
		apple.applesShape.setFillColor(sf::Color::Blue);
		apple.applesShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apple.applesShape.setPosition(apple.applesPos.x, apple.applesPos.y);

		apple.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png");
		apple.sprite.setTexture(apple.appleTexture);
		apple.sprite.setPosition(apple.applesPos.x, apple.applesPos.y);
		SetSpriteSize(apple.sprite, 15.f, 15.f);
	}

	void DrawApples(Apple* apples, sf::RenderWindow& window)
	{
		for (int i{ 0 }; i < NUM_APPLES; i++)
		{
			window.draw(apples[i].sprite);
		}
	}
}

