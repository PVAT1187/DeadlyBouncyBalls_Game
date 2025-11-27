#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>

class Game;

class Overlay
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update() = 0;
		virtual void render(sf::RenderWindow& window) = 0;

		virtual ~Overlay() = default;

	protected:
		Game& game;
		sf::RenderWindow& window;

		sf::RectangleShape dimBackground;

		Overlay(Game& game, sf::RenderWindow& window) :
			game(game), window(window) {}

		void initDimBackground()
		{
			dimBackground.setSize(static_cast<sf::Vector2f>(window.getSize()));
			dimBackground.setFillColor(sf::Color(0, 0, 0, 150));
		}
};

#endif // !OVERLAY_H

