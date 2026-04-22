#ifndef SCREEN_H
#define SCREEN_H

#include "Core/Input/InputCollector/InputCollector.h"

#include <SFML/Window/Event.hpp>

class Game;

class Screen
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float deltaTime, 
			const Input& Input) = 0;
		virtual void render() = 0;

		virtual ~Screen() = default;

	protected:
		Game& game;

		Screen(Game& game) : game(game) {}
};

#endif // !SCREEN_H
