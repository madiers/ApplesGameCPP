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

	Position2D GetRandomPositionOnScreen(sf::RenderWindow& window);

	bool IsRectCollide(Position2D& rectPos1, Vector2D rectSize1,
		Position2D& rectPos2, Vector2D rectSize2);



	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	
	bool IsSpritesCollide(sf::Sprite& sprite1, sf::Sprite& sprite2);

}
