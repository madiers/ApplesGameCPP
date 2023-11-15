#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "SFML/Audio.hpp"

namespace ApplesGame
{
	struct Apple
	{
		Position2D applesPos;
		sf::CircleShape applesShape;
		sf::Texture appleTexture;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, sf::RenderWindow& window);

	void DrawApples(Apple* apples, sf::RenderWindow& window);

}
