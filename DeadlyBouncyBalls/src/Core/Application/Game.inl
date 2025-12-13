#include "Core/Application/Game.h"

using namespace std;

template<typename ScreenType, typename... Arguments>
void Game::switchScreen(Arguments&&... arguments)
{
	currentScreen = make_unique<ScreenType>(*this, forward<Arguments>(arguments)...);
}