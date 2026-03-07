#include "Core/Rendering/Renderer.h"

using namespace sf;
using namespace std;

Renderer::Renderer() : 
	window(VideoMode::getDesktopMode(), "Deadly Bouncy Balls",
			Style::None) {}

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

void Renderer::draw(const Drawable& drawable)
{
	window.draw(drawable);
}

void Renderer::showCursor(bool show)
{
	window.setMouseCursorVisible(show);
}

Vector2u Renderer::getWindowSize() const
{
	return window.getSize();
}

Vector2f Renderer::getMousePosition() const
{
	return window.mapPixelToCoords(Mouse::getPosition(window));
}

optional<Event> Renderer::pollEvent()
{
	return window.pollEvent();
}

bool Renderer::isOpen() const
{
	return window.isOpen();
}