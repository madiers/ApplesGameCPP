#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
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
	float playerSpeed;
	PlayerDirection playerDirection;
	sf::RectangleShape playerShape;
};

void InitPlayer(Player& player, sf::RenderWindow& window, float playerSize, float initialSpeed);