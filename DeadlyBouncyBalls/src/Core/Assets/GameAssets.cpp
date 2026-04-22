#include "Core/Assets/GameAssets.h"

void GameAssets::load()
{
	if (!font.openFromFile("assets/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");
	
	if (!playerTexture.loadFromFile(
		"assets/PNG/Player/player_sprite.png"))
		throw std::runtime_error("Failed to load player texture!");

	if (!crosshairTexture.loadFromFile(
		"assets/PNG/Icons/crosshair_spritesheet.png"))
		throw std::runtime_error("Failed to load aiming icon texture!");

	if (!bulletTexture.loadFromFile(
		"assets/PNG/Icons/bullet_sprite.png"))
		throw std::runtime_error("Failed to load bullet icon texture!");
}

const sf::Font& GameAssets::getFont() const
{
	return font;
}

const sf::Texture& GameAssets::getTexture(TextureId textureId) const
{
	switch (textureId)
	{
		case TextureId::PLAYER_TEXTURE:
			return playerTexture;
		case TextureId::CROSSHAIR_TEXTURE:
			return crosshairTexture;
		case TextureId::BULLET_TEXTURE:
			return bulletTexture;
	}
}