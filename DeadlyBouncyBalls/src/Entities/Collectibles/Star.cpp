#include "Config/GameConfig.h"
#include "Core/Assets/GameAssets.h"
#include "Core/Rendering/Renderer.h"
#include "Core/World/WorldBounds.h"
#include "Entities/Collectibles/Star.h"
#include "Utilities/Random/RandomUtils.h"

Star::Star(
	const GameAssets& assets,
	const WorldBounds& worldBounds) :
	star(
		assets.getTexture(TextureId::STAR_TEXTURE),
		Config::Star::ROW,
		Config::Star::FRAME_SIZE,
		Config::Star::FRAME_COUNT,
		Config::Star::FRAME_DURATION
	),
	lifetime(Config::Star::LIFESPAN)
{
	float scale = RandomUtils::randomFloat(
		Config::Star::MIN_SCALE,
		Config::Star::MAX_SCALE
	);
	star.setScale({ scale, scale });

	sf::FloatRect starBounds = star.getLocalBounds();
	
	collisionBoxSize = sf::Vector2f(
		starBounds.size.x * scale,
		starBounds.size.y * scale
	);

	star.setOrigin(sf::Vector2f(
		starBounds.size.x / 2.f,
		starBounds.size.y / 2.f
	));

	position = sf::Vector2f(
		RandomUtils::randomFloat(
			worldBounds.left + collisionBoxSize.x / 2.f,
			worldBounds.right - collisionBoxSize.x / 2.f
		),
		RandomUtils::randomFloat(
			worldBounds.top + collisionBoxSize.y / 2.f,
			worldBounds.bottom - collisionBoxSize.y / 2.f
		)
	);
	star.setPosition(position);

	points = static_cast<int>(Config::Star::BASE_POINTS * scale);
}

void Star::update(float deltaTime)
{
	lifetime -= deltaTime;
	star.update(deltaTime);
}

void Star::draw(Renderer& renderer) const
{
	renderer.draw(star);
}

sf::Vector2f Star::getPosition() const
{
	return position;
}

int Star::getPoints() const
{
	return points;
}

sf::FloatRect Star::getCollisionBounds() const
{
	float shrunkWidth = 
		collisionBoxSize.x 
		* (1.f - Config::Star::SHRINK_FACTOR * 2.f);
	float shrunkHeight =
		collisionBoxSize.y
		* (1.f - Config::Star::SHRINK_FACTOR * 2.f);

	return sf::FloatRect(
		{ position.x - shrunkWidth / 2.f,
		  position.y - shrunkHeight / 2.f },
		{ shrunkWidth, shrunkHeight }
	);
}

bool Star::isExpired() const
{
	return lifetime <= 0.f;
}