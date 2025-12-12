#ifndef  AIMING_SYSTEM_H
#define  AIMING_SYSTEM_H

#include <SFML/Graphics.hpp>

class AimingSystem
{
	public:
		AimingSystem(const sf::Texture& aimingIconTexture);

		void update(const sf::Vector2f& playerPosition, const sf::Vector2f& aimingTarget);
		void draw(sf::RenderWindow& window) const;

	private:
		sf::Sprite aimingIconSprite;
		sf::VertexArray aimingLine;

		void aimAtTarget(const sf::Vector2f& playerPosition, 
			const sf::Vector2f& aimingTarget);
};

#endif // ! AIMING_SYSTEM_H

