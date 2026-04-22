#include "Config/GameConfig.h"
#include "Core/Assets/GameAssets.h"
#include "Core/Rendering/Renderer.h"
#include "Core/World/WorldBounds.h"
#include "Entities/Player/Player.h"

Player::Player(
    const GameAssets& assets,
    const WorldBounds& worldBounds) :
    player(assets.getTexture(TextureId::PLAYER_TEXTURE)),
	aiming(assets.getTexture(TextureId::CROSSHAIR_TEXTURE)),
    shooting({ 0.f, Config::Shooting::FIRE_COOLDOWN })
{
    player.setScale({
        Config::Player::SCALE,
        Config::Player::SCALE
    });

    sf::FloatRect spriteBounds = player.getLocalBounds();

    collisionBoxSize = sf::Vector2f(
        spriteBounds.size.x * Config::Player::SCALE,
        spriteBounds.size.y * Config::Player::SCALE
	);

    player.setOrigin(sf::Vector2f(
        spriteBounds.size.x / 2.f,
        spriteBounds.size.y / 2.f
    ));
    
    position = sf::Vector2f(
        worldBounds.right / 2.f,
        worldBounds.bottom / 2.f
    );

	player.setPosition(position);
}

void Player::update(float deltaTime) {}

void Player::draw(Renderer& renderer) const
{
    renderer.draw(player);
	renderer.draw(aiming.crosshair);
}

sf::FloatRect Player::getCollisionBounds() const
{
    float shrunkWidth = 
        collisionBoxSize.x 
        * (1.f - Config::Player::SHRINK_FACTOR * 2.f);
    float shrunkHeight = 
        collisionBoxSize.y 
        * (1.f - Config::Player::SHRINK_FACTOR * 2.f);

    return sf::FloatRect(
        { position.x - shrunkWidth / 2.f,
		  position.y - shrunkHeight / 2.f },
        { shrunkWidth, shrunkHeight }
    );
}

const sf::Vector2f& Player::getPosition() const
{
	return position;
}

void Player::setPosition(const sf::Vector2f& newPosition)
{
	position = newPosition;
	player.setPosition(position);
}

float Player::getRotation() const 
{
	return player.getRotation().asDegrees();
}

void Player::setRotation(float angleDegrees)
{
	player.setRotation(sf::degrees(angleDegrees));
}
