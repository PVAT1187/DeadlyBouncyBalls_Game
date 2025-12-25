#ifndef  AIMING_SYSTEM_H
#define  AIMING_SYSTEM_H

#include "Utilities/Graphics/AnimatedSprite.h"

#include <SFML/Graphics.hpp>

class AimingSystem
{
	public:
		AimingSystem(const sf::Texture& crosshairTexture);

		void update(float deltaTime,
			const sf::Vector2f& playerPosition, 
			const sf::Vector2f& aimingTarget);
		void draw(sf::RenderWindow& window) const;

		void resetAnimation();

	private:
		AnimatedSprite crosshairSprite;
		sf::VertexArray aimingLine;

		void aimAtTarget(const sf::Vector2f& playerPosition, 
			const sf::Vector2f& aimingTarget);
};

#endif // !AIMING_SYSTEM_H

