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

	bool IsRectCollide(Position2D& rectPos1, Vector2D rectSize1, Position2D& rectPos2, Vector2D rectSize2)
	{
		const float dx = abs(rectPos1.x - rectPos2.x);
		const float dy = abs(rectPos1.y - rectPos2.y);

		return (dx <= (rectSize1.x + rectSize2.x) / 2.f &&
			dy <= (rectSize1.y + rectSize2.y) / 2.f);
	}

	


	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	bool IsSpritesCollide(sf::Sprite& sprite1, sf::Sprite& sprite2)
	{

		float dx = abs(sprite1.getPosition().x - sprite2.getPosition().x);
		float dy = abs(sprite1.getPosition().y - sprite2.getPosition().y);

		return (dx <= (sprite1.getScale().x + sprite2.getScale().x) / 2.f &&
			dy <= (sprite1.getScale().y + sprite2.getScale().y) / 2.f);

	}
}

