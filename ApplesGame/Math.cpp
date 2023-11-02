#include "Math.h"

namespace ApplesGame
{
	Position2D GetRandomPositionOnScreen(sf::RenderWindow& window)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * window.getSize().x;
		result.y = rand() / (float)RAND_MAX * window.getSize().y;
		return result;
	}

	bool IsRectCollinde(Position2D& rectPos1, Vector2D rectSize1, Position2D& rectPos2, Vector2D rectSize2)
	{
		float dx = abs(rectPos1.x - rectPos2.x);
		float dy = abs(rectPos1.y - rectPos2.y);

		return (dx <= (rectSize1.x + rectSize2.x) / 2.f &&
			dy <= (rectSize1.y + rectSize2.y) / 2.f);
	}

	bool IsRectCircleCollide(Position2D& rectPos, float rectSize, Position2D& circlePos, float circleRadius)
	{
		float sqDistance = (rectPos.x - circlePos.x) * (rectPos.x - circlePos.x) +
			(rectPos.y - circlePos.y) * (rectPos.y - circlePos.y);

		float sqRadiusSum = (rectSize + circleRadius) * (rectSize + circleRadius) / 4;

		return sqDistance <= sqRadiusSum;
	}
}

