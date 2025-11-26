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

		static const unsigned int TITLE_TEXT_SIZE = 100;
		static const unsigned int BODY_TEXT_SIZE = 25;

	protected:
		Game& game;

		Screen(Game& game) : game(game) {}
};

#endif // !SCREEN_H
