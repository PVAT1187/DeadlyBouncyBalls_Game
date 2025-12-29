#include "Core/App/Game.h"
#include "Core/GameWorld/GameWorld.h"

using namespace sf;

GameWorld::GameWorld(Game& game, const Vector2u& windowSize) :
	player(game.getAssets(), windowSize),
	ballManager(windowSize) {}

void GameWorld::update(float deltaTime, 
	const Vector2u& windowSize,
	const Vector2f& mousePosition)
{
	player.setMouseTarget(mousePosition);
	player.update(deltaTime, windowSize);
	ballManager.update(deltaTime, windowSize);
	combatSystem.update(player, ballManager);
}

void GameWorld::render(RenderWindow& window) const
{
	player.draw(window);
	ballManager.draw(window);
}

bool GameWorld::isGameOver() const
{
	return ballManager.isCollidingWithPlayer(player);
}