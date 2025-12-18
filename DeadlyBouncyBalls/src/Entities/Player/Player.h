#ifndef PLAYER_H
#define PLAYER_H

#include "Core/Systems/Aiming/AimingSystem.h"
#include "Core/Systems/Shooting/ShootingSystem.h"
#include "Entities/Entity.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
	public:
		Player(const sf::Texture& playerTexture, 
			const sf::Texture& aimingIconTexture,
			const sf::Texture& bulletTexture);

		void update(float deltaTime, const sf::Vector2u& windowSize) override;
		void draw(sf::RenderWindow& window) const override;

		void setMouseTarget(const sf::Vector2f& target);

		const sf::Sprite& getSprite() const;
		sf::Sprite& getSprite();

		sf::FloatRect getCollisionBounds() const;
		ShootingSystem& getShootingSystem();

	private:
		sf::Sprite playerSprite;

		sf::Vector2f mouseTarget;
		AimingSystem aimingSystem;
		ShootingSystem shootingSystem;

		void move(float deltaTime);
		void clampToWindow(const sf::Vector2u& windowSize);
		void rotate(float deltaTime, const sf::Vector2f& rotationTarget);
		
		void shoot(float deltaTime, const sf::Vector2f& playerPosition);
};

#endif // !PLAYER_H