#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Core/World/WorldBounds.h"
#include "Core/Events/EventBus/EventBus.h"
#include "Core/Systems/Boundary/BoundarySystem.h"
#include "Core/Systems/Movement/MovementSystem.h"
#include "Core/Systems/Aiming/AimingSystem.h"
#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Core/Systems/Combat/CombatSystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Entities/Projectiles/BulletManager.h"

class Renderer;
class GameAssets;

class GameWorld
{
	public:
		GameWorld(const GameAssets& assets, 
			const sf::Vector2u& windowSize);

		void update(float deltaTime,
			const Input& Input);
		void render(Renderer& renderer) const;

		int getScore() const;

		bool isGameOver() const;

	private:
		WorldBounds worldBounds;
		EventBus eventBus;

		BoundarySystem boundarySystem;

		Player player;
		BallManager ballManager;
		BulletManager bulletManager;

		MovementSystem movementSystem;
		AimingSystem aimingSystem;
		ShootingSystem shootingSystem;
		CombatSystem combatSystem;

		int score;
		std::vector<size_t> pendingBallHits;
		bool gameOver;

		void processPendingBallHits();
};

#endif // !GAME_PLAY_H

