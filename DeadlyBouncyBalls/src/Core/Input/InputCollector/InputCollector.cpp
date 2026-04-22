#include "Core/Rendering/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/Input/InputCollector/InputCollector.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Input InputCollector::collect(Renderer& renderer) const
{
	Input Input{};

	Input.moveLeft = sf::Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::A);
	Input.moveRight = sf::Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::D);
	Input.moveUp = sf::Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::W);
	Input.moveDown = sf::Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::S);
	
	Input.shoot = sf::Mouse::isButtonPressed(
		sf::Mouse::Button::Left);
	
	Input.mousePosition = renderer.getMousePosition();

	return Input;
}
