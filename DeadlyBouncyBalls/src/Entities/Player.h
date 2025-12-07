#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player(const sf::Texture& texture);

		void update(const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window) const;

		const sf::Sprite& getSprite() const;
		sf::Sprite& getSprite();

		sf::FloatRect getCollisionBounds() const;

	private:
		sf::Sprite sprite;

		void clampToWindow(const sf::RenderWindow& window);
		void followMouse(const sf::RenderWindow& window);
};

#endif // !PLAYER_H