#include "Player.h"
#include "Constants.h"

namespace ApplesGame
{
	void InitPlayer(Player& player, sf::RenderWindow& window, float playerSize, float initialSpeed)
	{

		// Init Player Settings

		player.playerPosition = { window.getSize().x / 2.f, window.getSize().y / 2.f };
		player.playerSpeed = initialSpeed;
		player.playerDirection = PlayerDirection::Right;

		// Init player Shape
		player.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png");
		player.sprite.setTexture(player.playerTexture);
		SetSpriteSize(player.sprite, 15.f, 15.f);
	}
	void ChangeDirection(Player& player, float& deltaTime)
	{
		// Check on KeyPressed
		// I don't like Switch Case	так что и не использовал

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.playerDirection = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.playerDirection = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.playerDirection = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.playerDirection = PlayerDirection::Down;
		}

		if (player.playerDirection == PlayerDirection::Right) // Right
		{
			player.playerPosition.x += player.playerSpeed * deltaTime;
			player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
			player.sprite.setRotation(0.f);
		}
		else if (player.playerDirection == PlayerDirection::Left) // Left
		{
			player.playerPosition.x -= player.playerSpeed * deltaTime;
			player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
			player.sprite.setRotation(180.f);
		}
		else if (player.playerDirection == PlayerDirection::Up) // Up
		{
			player.playerPosition.y -= player.playerSpeed * deltaTime;
			player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
			player.sprite.setRotation(-90.f);
		}
		else if (player.playerDirection == PlayerDirection::Down) // Down
		{
			player.playerPosition.y += player.playerSpeed * deltaTime;
			player.sprite.setPosition(player.playerPosition.x, player.playerPosition.y);
			player.sprite.setRotation(90.f);
		}
	}
	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		window.draw(player.sprite);
	}
}

