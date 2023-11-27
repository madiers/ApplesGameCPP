#include "SFML/Graphics.hpp"
#include "GameModeSelector.h"

namespace ApplesGame
{
	struct GameMode {
		private:
			bool isInfiniteApple;
			bool isAcceleratable;
		public:
			void SetIsInfiniteApple(bool isInifinite) { isInfiniteApple = isInifinite; };
			void SetisAcceleratable(bool isAccelerate) { isAcceleratable = isAccelerate; };
			bool GetIsInfiniteApple() { return this->isInfiniteApple; };
			bool GetIsAcceleratable() { return this->isAcceleratable; };
		};
}