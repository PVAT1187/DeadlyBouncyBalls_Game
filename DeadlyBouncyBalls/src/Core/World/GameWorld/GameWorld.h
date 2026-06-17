#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Core/Assets/GameAssets.h"
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
#include "Entities/Collectibles/StarManager.h"

class Renderer;

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
		GameAssets assets;
		WorldBounds worldBounds;
		EventBus eventBus;

		BoundarySystem boundarySystem;

		Player player;
		BallManager ballManager;
		BulletManager bulletManager;
		StarManager starManager;

		MovementSystem movementSystem;
		AimingSystem aimingSystem;
		ShootingSystem shootingSystem;
		CombatSystem combatSystem;

		int score;
		bool gameOver;

		std::vector<size_t> pendingBallHits;
		std::vector<size_t> pendingStarHits;

		void processPendingBallHits();
		void processPendingStarHits();
};

#endif // !GAME_PLAY_H

