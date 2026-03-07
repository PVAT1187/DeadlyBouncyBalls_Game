#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>

class Renderer
{
	public:
		Renderer();

		void clear();
		void display();
		void close();

		void draw(const sf::Drawable& drawable);

		void showCursor(bool show);

		sf::Vector2u getWindowSize() const;
		sf::Vector2f getMousePosition() const;

		std::optional<sf::Event> pollEvent();

		bool isOpen() const;

	private:
		sf::RenderWindow window;
};

#endif // !RENDERER_H

