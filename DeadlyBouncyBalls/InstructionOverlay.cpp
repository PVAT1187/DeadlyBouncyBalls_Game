#include "InstructionOverlay.h"
#include "UIUtils.h"
#include "Game.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

InstructionOverlay::InstructionOverlay(Game& game, RenderWindow& window) :
	Overlay(game, window),
	instructionOverlayTitle(Text(game.getFont(), "HOW TO PLAY", Screen::TITLE_TEXT_SIZE)),
	instructions(Text(game.getFont(), "", Screen::BODY_TEXT_SIZE)),
	continueButton("CONTINUE", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	initDimBackground();
	initInstructionOverlayTitle();
	initInstructionText();
	updateButtonPosition();
}

void InstructionOverlay::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (continueButton.isClicked(window))
		{
			game.switchToGamePlayScreen();
		}
	}
}

void InstructionOverlay::update() 
{
	continueButton.update(window);
}

void InstructionOverlay::render(RenderWindow& window)
{
	window.draw(dimBackground);
	window.draw(instructionOverlayTitle);
	window.draw(instructions);
	continueButton.draw(window);
}


void InstructionOverlay::initInstructionOverlayTitle()
{
	centerTitleText(instructionOverlayTitle, window);
}

void InstructionOverlay::initInstructionText()
{
	instructions.setString("Dodge the balls and Survive as long as possible\n");
	centerBodyText(instructions, window, Screen::TEXT_SPACING);
}

void InstructionOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = {&continueButton};
	positionButtons(instructionOverlayTitle, buttons, window);
}