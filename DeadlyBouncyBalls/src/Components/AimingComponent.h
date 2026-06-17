#ifndef AIMING_COMPONENT_H
#define AIMING_COMPONENT_H

#include "Config/GameConfig.h"
#include "Utilities/Animation/AnimatedSprite.h"

#include <SFML/System/Vector2.hpp>

struct AimingComponent
{
	sf::Vector2f direction;
	sf::Vector2f target;
	bool resetAnimation = false;

	AnimatedSprite crosshair;

	AimingComponent(const sf::Texture& crosshairTexture)
		: crosshair(
			crosshairTexture,
			Config::Aiming::CROSSHAIR_ROW,
			Config::Aiming::CROSSHAIR_FRAME_SIZE,
			Config::Aiming::CROSSHAIR_FRAME_COUNT,
			Config::Aiming::CROSSHAIR_FRAME_DURATION,
			false
		)
	{
		crosshair.setScale({
			Config::Aiming::CROSSHAIR_SCALE,
			Config::Aiming::CROSSHAIR_SCALE
		});

		sf::FloatRect aimingIconBounds = crosshair.getLocalBounds();
		crosshair.setOrigin(sf::Vector2f(
			aimingIconBounds.size.x / 2.f,
			aimingIconBounds.size.y / 2.f
		));
	}
};

#endif // !AIMING_COMPONENT_H