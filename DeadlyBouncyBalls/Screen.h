#ifndef SCREEN_H
#define SCREEN_H

class Game;

#include <SFML/Graphics.hpp>

class Screen
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render(sf::RenderWindow& window) = 0;

		virtual ~Screen() = default;

	protected:
		Game& game;

		Screen(Game& game) : game(game) {}
};

#endif // !SCREEN_H
