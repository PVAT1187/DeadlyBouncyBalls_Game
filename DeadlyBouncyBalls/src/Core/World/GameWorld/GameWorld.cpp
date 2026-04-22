#include "Core/Assets/GameAssets.h"
#include "Core/World/GameWorld/GameWorld.h"
#include "Core/Events/GameEvents.h"
#include "Core/Rendering/Renderer.h"

GameWorld::GameWorld(
	const GameAssets& assets,
	const sf::Vector2u& windowSize) :
	worldBounds(windowSize),
	player(assets, worldBounds),
	ballManager(worldBounds),
	bulletManager(assets),
	combatSystem(eventBus),
	score(0),
	gameOver(false) 
{
	eventBus.subscribe<PlayerHit>(
		[this](const PlayerHit&) 
		{
			gameOver = true;
		});

	eventBus.subscribe<BallHit>(
		[this](const BallHit& event)
		{
			pendingBallHits.push_back(event.ballIndex);
		});

	eventBus.subscribe<BulletHit>(
		[this](const BulletHit& event)
		{
			bulletManager.remove(event.bulletIndex);
		});
}

void GameWorld::update(
	float deltaTime,
	const Input& Input)
{
	movementSystem.apply(player, Input, deltaTime);
	aimingSystem.apply(player, Input, deltaTime);
	shootingSystem.apply(
		player,
		bulletManager,
		Input,
		deltaTime
	);
	boundarySystem.apply(player, worldBounds);

	bulletManager.update(deltaTime);
	
	ballManager.update(deltaTime);
	boundarySystem.apply(ballManager, worldBounds);

	combatSystem.update(
		player,
		ballManager,
		bulletManager
	);

	eventBus.dispatch();
	processPendingBallHits();
}

void GameWorld::render(Renderer& renderer) const
{
	player.draw(renderer);
	ballManager.draw(renderer);
	bulletManager.draw(renderer);
}

int GameWorld::getScore() const
{
	return score;
}

bool GameWorld::isGameOver() const
{
	return gameOver;
}

void GameWorld::processPendingBallHits()
{
	std::sort(pendingBallHits.begin(), pendingBallHits.end());

	pendingBallHits.erase(
		std::unique(
			pendingBallHits.begin(),
			pendingBallHits.end()
		),
		pendingBallHits.end()
	);

	for (size_t index : pendingBallHits)
	{
		if (ballManager.splitBallOnHit(index))
		{
			score += 1;
		}
	}
	pendingBallHits.clear();
}