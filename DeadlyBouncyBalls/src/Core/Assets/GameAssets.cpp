#include "Core/Assets/GameAssets.h"

using namespace sf;
using namespace std;

void GameAssets::loadFont()
{
	if (!font.openFromFile("assets/fonts/arial.ttf"))
		throw runtime_error("Failed to load font!");
}

void GameAssets::loadAssets()
{
	if (!playerTexture.loadFromFile("assets/PNG/Player/player_sprite.png"))
		throw runtime_error("Failed to load player texture!");

	if (!aimingIconTexture.loadFromFile("assets/PNG/Icons/crosshair_spritesheet.png"))
		throw runtime_error("Failed to load aiming icon texture!");

	if (!bulletTexture.loadFromFile("assets/PNG/Icons/bullet_sprite.png"))
		throw runtime_error("Failed to load bullet icon texture!");
}

const Font& GameAssets::getFont() const
{
	return font;
}

const Texture& GameAssets::getPlayerTexture() const
{
	return playerTexture;
}

const Texture& GameAssets::getAimingIconTexture() const
{
	return aimingIconTexture;
}

const Texture& GameAssets::getBulletTexture() const
{
	return bulletTexture;
}