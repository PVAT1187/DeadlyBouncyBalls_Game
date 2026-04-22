#include "Core/Rendering/Renderer.h"

Renderer::Renderer() : 
	window(
		sf::VideoMode::getDesktopMode(),
		"Deadly Bouncy Balls",
		sf::Style::None
	) {}

void Renderer::clear()
{
	window.clear();
}

void Renderer::display()
{
	window.display();
}

void Renderer::close()
{
	window.close();
}

void Renderer::draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Renderer::showCursor(bool show)
{
	window.setMouseCursorVisible(show);
}

sf::Vector2u Renderer::getWindowSize() const
{
	return window.getSize();
}

sf::Vector2f Renderer::getMousePosition() const
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

std::optional<sf::Event> Renderer::pollEvent()
{
	return window.pollEvent();
}

bool Renderer::isOpen() const
{
	return window.isOpen();
}