#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Game;

	struct Apple
	{
		Position2D applesPos;
<<<<<<< Updated upstream
		sf::CircleShape applesShape;
=======
		//sf::CircleShape applesShape;

		sf::Sprite sprtie;

>>>>>>> Stashed changes
	};

	void InitApple(Apple& apple, sf::RenderWindow& window);

	void DrawApple(Game& gameState, sf::RenderWindow& window);
}
