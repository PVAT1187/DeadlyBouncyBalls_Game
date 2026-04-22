#ifndef OVERLAY_H
#define OVERLAY_H

#include "Config/GameConfig.h"
#include "Core/Input/InputCollector/InputCollector.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Game;
class GameAssets;

class Overlay
{
	public:
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(float deltaTime, 
			const Input& Input) = 0;
		virtual void render() = 0;

		virtual ~Overlay() = default;

	protected:
		Game& game;
		sf::RectangleShape dimBackground;

		Overlay(Game& game) : game(game) {}

		void initDimBackground()
		{
			auto& renderer = game.getRenderer();
			
			dimBackground.setSize(
				static_cast<sf::Vector2f>(renderer.getWindowSize())
			);

			dimBackground.setFillColor(
				sf::Color(0, 0, 0, Config::UI::DIM_ALPHA)
			);
		}
};

#endif // !OVERLAY_H

