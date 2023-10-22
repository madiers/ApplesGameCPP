#pragma once
#include <SFML/Graphics.hpp>

struct Vector2D
{
	float x{ 0 };
	float y{ 0 };
};

typedef Vector2D Position2D;

Position2D GetRandomPositionOnScreen(sf::RenderWindow& window);

bool IsRectCollinde(Position2D& rectPos1, Vector2D rectSize1,
	Position2D& rectPos2, Vector2D rectSize2);

bool IsRectCircleCollide(Position2D& rectPos, float rectSize, Position2D& circlePos, float circleRadius);