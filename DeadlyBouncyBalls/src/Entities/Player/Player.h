#ifndef PLAYER_H
#define PLAYER_H

#include "Core/Assets/GameAssets.h"
#include "Core/Systems/Aiming/AimingSystem.h"
#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
	public:
		Player(const GameAssets& assets, const sf::Vector2u& windowSize);

		void update(float deltaTime, const sf::Vector2u& windowSize) override;
		void draw(sf::RenderWindow& window) const override;

		sf::FloatRect getCollisionBounds() const;
		std::vector<Bullet>& getBullets();

		void setMouseTarget(const sf::Vector2f& target);

	private:
		sf::Sprite playerSprite;

		sf::Vector2f mouseTarget;
		AimingSystem aimingSystem;
		ShootingSystem shootingSystem;

		void move(float deltaTime);
		void clampToWindow(const sf::Vector2u& windowSize);
		void rotate(float deltaTime, const sf::Vector2f& rotationTarget);
		bool shoot(float deltaTime, const sf::Vector2f& playerPosition);
};

#endif // !PLAYER_H