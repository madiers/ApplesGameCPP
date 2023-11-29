#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameMode.h"

namespace ApplesGame
{
	enum UserGameSettingsBitMask;
	void ModeSelect(sf::RenderWindow& window, GameMode& gameMode);
}