#include "Core/App/Game.h"

template<typename ScreenType, typename... Arguments>
void Game::switchScreen(Arguments&&... arguments)
{
	currentScreen = std::make_unique<ScreenType>(
		*this, 
		std::forward<Arguments>(arguments)...
	);
}