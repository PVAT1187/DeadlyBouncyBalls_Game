#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

enum class TextureId
{
	PLAYER_TEXTURE,
	CROSSHAIR_TEXTURE,
	BULLET_TEXTURE,
	STAR_TEXTURE
};

class GameAssets 
{
	public:
		void load();

		const sf::Font& getFont() const;
		
		const sf::Texture& getTexture(TextureId textureId) const;

	private:
		sf::Font font;
		
		sf::Texture playerTexture;
		sf::Texture crosshairTexture;
		sf::Texture bulletTexture;
		sf::Texture starTexture;
};

#endif // !GAME_ASSETS_H

