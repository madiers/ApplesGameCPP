#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ApplesGame
{
	struct GameMode
	{
	private:
		bool isInfiniteApple;
		bool isAcceleratable;
	public:
		sf::Text Prompt;
		sf::Text firstMode;
		sf::Text secondMode;
		sf::Text thirdMode;
		sf::Text fourthMode;
		sf::Font font;

		void SetIsInfiniteApple(bool isInifinite) { isInfiniteApple = isInifinite; };
		void SetisAcceleratable(bool isAccelerate) { isAcceleratable = isAccelerate; };
		bool GetIsInfiniteApple() { return this->isInfiniteApple; };
		bool GetIsAcceleratable() { return this->isAcceleratable; };
	};
	enum UserGameSettingsBitMask;
	void ModeSelect(sf::RenderWindow& window, GameMode& gameMode);
}