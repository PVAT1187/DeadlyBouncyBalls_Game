#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Entities/Player/Player.h"
#include "Entities/Enemies/BallManager.h"
#include "Systems/Combat/CombatSystem.h"

class Game;

class GameWorld
{
	public:
		GameWorld(Game& game, const sf::Vector2u& windowSize);

		void update(float deltaTime, 
			const sf::Vector2u& windowSize,
			const sf::Vector2f& mousePosition);
		void render(sf::RenderWindow& window) const;

		bool isGameOver() const;

	private:
		Player player;
		BallManager ballManager;
		CombatSystem combatSystem;
};

#endif // !GAME_PLAY_H

