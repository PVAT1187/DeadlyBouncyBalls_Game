#ifndef	PLAYER_H
#define PLAYER_H

#include "Components/MovementComponent.h"
#include "Components/AimingComponent.h"
#include "Components/ShootingComponent.h"
#include "Core/Input/InputCollector/InputCollector.h"
#include "Core/World/WorldBounds.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class GameAssets;
class Renderer;

class Player
{
	public:
		Player(const GameAssets& assets, 
			const WorldBounds& worldBounds);

		void update(float deltaTime);
		void draw(Renderer& renderer) const;

		const sf::Vector2f& getPosition() const;
		void setPosition(const sf::Vector2f& newPosition);

		float getRotation() const;
		void setRotation(float angleDegrees);

		sf::FloatRect getCollisionBounds() const;

		MovementComponent movement;
		AimingComponent aiming;
		ShootingComponent shooting;

	private:
		sf::Sprite player;

		sf::Vector2f position;
		sf::Vector2f collisionBoxSize;
};

#endif // !PLAYER_H