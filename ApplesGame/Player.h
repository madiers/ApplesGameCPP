#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D playerPosition;
		float playerSpeed{INITIAL_SPEED};
		PlayerDirection playerDirection{PlayerDirection::Right};
		sf::Texture playerTexture;
		sf::Sprite sprite;
	};

	void InitPlayer(Player& player, sf::RenderWindow& window, float playerSize, float initialSpeed);

	void ChangeDirection(Player& player, float& deltaTime);

	void DrawPlayer(Player& player, sf::RenderWindow& window);
}
