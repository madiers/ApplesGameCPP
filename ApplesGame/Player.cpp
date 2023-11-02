#include "Player.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, sf::RenderWindow& window, float playerSize, float initialSpeed)
	{

		// Init Player Settings

		player.playerPosition = { window.getSize().x / 2.f, window.getSize().y / 2.f };
		player.playerSpeed = initialSpeed;
		player.playerDirection = PlayerDirection::Right;

		// Init player Shape

		player.playerShape.setSize(sf::Vector2f(playerSize, playerSize));
		player.playerShape.setFillColor(sf::Color::Red);
		player.playerShape.setOrigin(playerSize / 2.f, playerSize / 2.f);
		player.playerShape.setPosition(player.playerPosition.x, player.playerPosition.y);
	}
}

