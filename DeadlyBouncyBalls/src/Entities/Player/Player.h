#ifndef PLAYER_H
#define PLAYER_H

#include "Core/Systems/Aiming/AimingSystem.h"
#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Core/Systems/Input/InputSystem.h"
#include "Core/World/WorldBounds.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class GameAssets;

class Player
{
	public:
		Player(const GameAssets& assets, 
			const WorldBounds& worldBounds);

		void update(float deltaTime, const InputState& inputState);
		void draw(Renderer& renderer) const;

		sf::FloatRect getCollisionBounds() const;
		std::vector<Bullet>& getBullets();

		const sf::Vector2f& getPosition() const;

		void setPosition(const sf::Vector2f& newPosition);

	private:
		sf::Sprite playerSprite;

		AimingSystem aimingSystem;
		ShootingSystem shootingSystem;

		void move(float deltaTime, const InputState& inputState);
		void rotate(float deltaTime, const InputState& inputState);
		bool shoot(float deltaTime, 
			const sf::Vector2f& playerPosition,
			const InputState& inputState);
};

#endif // !PLAYER_H