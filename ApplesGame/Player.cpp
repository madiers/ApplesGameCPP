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

		//SetSpriteRelativeOrigin(player.sprite, player.sprite.getScale().x / 2.f, player.sprite.getScale().y / 2.f);
		

		//player.playerShape.setSize(sf::Vector2f(playerSize, playerSize));
		//player.playerShape.setFillColor(sf::Color::Red);
		//player.playerShape.setOrigin(playerSize / 2.f, playerSize / 2.f);
		//player.playerShape.setPosition(player.playerPosition.x, player.playerPosition.y);
	}
	void CheckDirection(Player& player, float& deltaTime)
	{
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
}

