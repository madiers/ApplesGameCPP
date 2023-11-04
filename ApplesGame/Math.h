#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D
	{
		float x{ 0 };
		float y{ 0 };
	};

	typedef Vector2D Position2D;

<<<<<<< Updated upstream
=======
	void SetSpriteSize(sf::Sprite& sprite, float Width, float Height);

	void SetSpriteRelativeOrigin(sf::Sprite sprite, float originX, float originY);

	void SetSpriteCenterOrigin(sf::Sprite& sprite);

>>>>>>> Stashed changes
	Position2D GetRandomPositionOnScreen(sf::RenderWindow& window);

	bool IsRectCollinde(Position2D& rectPos1, Vector2D rectSize1,
		Position2D& rectPos2, Vector2D rectSize2);

	bool IsRectCircleCollide(Position2D& rectPos, float rectSize, Position2D& circlePos, float circleRadius);
}
