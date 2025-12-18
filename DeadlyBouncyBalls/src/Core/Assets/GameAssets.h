#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <SFML/Graphics.hpp>

class GameAssets 
{
	public:
		void loadFont();
		void loadAssets();

		const sf::Font& getFont() const;

		const sf::Texture& getPlayerTexture() const;
		const sf::Texture& getAimingIconTexture() const;
		const sf::Texture& getBulletTexture() const;

	private:
		sf::Font font;
		
		sf::Texture playerTexture;
		sf::Texture aimingIconTexture;
		sf::Texture bulletTexture;
};

#endif // !GAME_ASSETS_H

