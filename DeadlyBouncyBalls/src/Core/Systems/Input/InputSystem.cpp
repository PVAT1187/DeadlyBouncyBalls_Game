#include "Core/Systems/Input/InputSystem.h"
#include "Core/Rendering/Renderer.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

using namespace sf;

InputState InputSystem::collect(Renderer& renderer) const
{
	InputState inputState;

	inputState.moveLeft = Keyboard::isKeyPressed(
		Keyboard::Scancode::A);
	inputState.moveRight = Keyboard::isKeyPressed(
		Keyboard::Scancode::D);
	inputState.moveUp = Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::W);
	inputState.moveDown = Keyboard::isKeyPressed(
		sf::Keyboard::Scancode::S);
	
	inputState.shoot = Mouse::isButtonPressed(
		Mouse::Button::Left);
	
	inputState.mousePosition = renderer.getMousePosition();

	return inputState;
}
