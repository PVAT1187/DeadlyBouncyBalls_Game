#ifndef SCREEN_H
#define SCREEN_H

#include "TextButton.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Game;

class Screen
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render(sf::RenderWindow& window) = 0;

		virtual ~Screen() = default;

		static constexpr unsigned int TITLE_TEXT_SIZE = 100;
		static constexpr unsigned int BODY_TEXT_SIZE = 25;
		static constexpr float TEXT_SPACING = 125.f;

	protected:
		Game& game;
		sf::RenderWindow& window;

		Screen(Game& game, sf::RenderWindow& window) : 
			game(game), window(window) {}
};

#endif // !SCREEN_H
