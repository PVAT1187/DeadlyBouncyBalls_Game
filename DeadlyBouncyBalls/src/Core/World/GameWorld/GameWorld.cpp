#include "Config/Constants/GameConstants.h"
#include "Core/World/GameWorld/GameWorld.h"
#include "Core/Rendering/Renderer.h"
#include "Utilities/Math/MathUtils.h"

using namespace sf;
using namespace MathUtils;

GameWorld::GameWorld(const GameAssets& assets,
	const Vector2u& windowSize) :
	worldBounds(windowSize),
	boundarySystem(worldBounds),
	player(assets, worldBounds),
	ballManager(worldBounds),
	gameOver(false) {}

void GameWorld::update(float deltaTime,
	const InputState& inputState)
{
	player.update(deltaTime, inputState);
	boundarySystem.apply(player);
	
	ballManager.update(deltaTime);
	boundarySystem.apply(ballManager);

	combatSystem.update(player, ballManager);
	if (combatSystem.isPlayerHit()) 
		gameOver = true;
}

void GameWorld::render(Renderer& renderer) const
{
	player.draw(renderer);
	ballManager.draw(renderer);
}

bool GameWorld::isGameOver() const
{
	return gameOver;
}