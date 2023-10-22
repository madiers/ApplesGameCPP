#include "Apple.h"
#include "Constants.h"

void InitApple(Apple& apple, sf::RenderWindow& window)
{
	// Init apple
	apple.applesPos = GetRandomPositionOnScreen(window);
	apple.applesShape.setRadius(APPLE_SIZE / 2.f);
	apple.applesShape.setFillColor(sf::Color::Blue);
	apple.applesShape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	apple.applesShape.setPosition(apple.applesPos.x, apple.applesPos.y);
}
