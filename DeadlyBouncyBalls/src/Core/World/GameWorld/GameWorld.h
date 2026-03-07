#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Core/World/WorldBounds.h"
#include "Core/Systems/Boundary/BoundarySystem.h"
#include "Core/Systems/Combat/CombatSystem.h"
#include "Core/Systems/Input/InputSystem.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"

class Renderer;

class GameWorld
{
	public:
		GameWorld(const GameAssets& assets, 
			const sf::Vector2u& windowSize);

		void update(float deltaTime,
			const InputState& inputState);
		void render(Renderer& renderer) const;

		bool isGameOver() const;

	private:
		WorldBounds worldBounds;
		BoundarySystem boundarySystem;

		Player player;
		BallManager ballManager;
		CombatSystem combatSystem;

		bool gameOver;
};

#endif // !GAME_PLAY_H

