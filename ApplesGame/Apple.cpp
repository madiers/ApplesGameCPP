#include "Apple.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, sf::RenderWindow& window)
	{
		// Init apple
		apple.applesPos = GetRandomPositionOnScreen(window);
		//apple.applesShape.setRadius(APPLE_SIZE / 2.f);
		//apple.applesShape.setFillColor(sf::Color::Blue);
		//apple.applesShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
		apple.sprtie.setPosition(apple.applesPos.x, apple.applesPos.y);
		SetSpriteSize(apple.sprtie, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprtie, 0.5f, 0.5f);
	}

	void DrawApple(Game& gameState, sf::RenderWindow& window)
	{
		for (int i{ 0 }; i < NUM_APPLES; i++)
		{
			window.draw(gameState.apples[i].sprtie);
		}
	}
}

