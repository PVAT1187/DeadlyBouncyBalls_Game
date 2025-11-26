#ifndef PLAYER_H
#define PLAYER_H

#include <sfml/Graphics.hpp>

class Player
{
	public:
		Player(const sf::RenderWindow& window);

		void rotate(float angle);
		void update(const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window) const;

		const sf::RectangleShape& getRectangle() const;

	private:
		sf::RectangleShape rectangle;
};

#endif // !PLAYER_H