#include "Core/App/Game.h"
#include "Core/GameWorld/GameWorld.h"

using namespace sf;

GameWorld::GameWorld(Game& game, const Vector2u& windowSize) :
	assets(game.getAssets()),
	player(assets.getPlayerTexture(), assets.getAimingIconTexture(), assets.getBulletTexture()),
	ballManager(windowSize)
{
	player.getSprite().setPosition(
		Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));
}

void GameWorld::update(float deltaTime, 
	const Vector2u& windowSize,
	const Vector2f& mousePosition)
{
	player.setMouseTarget(mousePosition);
	player.update(deltaTime, windowSize);
	ballManager.update(deltaTime, windowSize);

	combatSystem.update(player.getShootingSystem(), ballManager);
}

void GameWorld::render(RenderWindow& window) const
{
	player.draw(window);
	ballManager.draw(window);
}

bool GameWorld::isGameOver() const
{
	return ballManager.hitsPlayer(player);
}