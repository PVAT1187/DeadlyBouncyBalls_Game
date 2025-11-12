#include "Game.h"

using namespace sf;

Game::Game() :
	window(VideoMode(DESKTOP_MODE), "Deadly Bouncy Balls", 
		Style::None),
	player(window),
	ball(window)
{

}

void Game::run()
{

}