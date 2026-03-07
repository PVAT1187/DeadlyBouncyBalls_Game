#ifndef SCREEN_H
#define SCREEN_H

#include "Core/Systems/Input/InputSystem.h"

#include <SFML/Window/Event.hpp>

class Game;

class Screen
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float deltaTime, 
			const InputState& inputState) = 0;
		virtual void render() = 0;

		virtual ~Screen() = default;

	protected:
		Game& game;

		Screen(Game& game) : game(game) {}
};

#endif // !SCREEN_H
