#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Overlays/Tutorial/TutorialOverlay.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

TutorialOverlay::TutorialOverlay(Game& game,
	RenderWindow& window) :
	Overlay(game, window, &game.getAssets()),
	tutorialOverlayTitle(Text(assets->getFont(), "TUTORIAL", TITLE_TEXT_SIZE)),
	continueButton("CONTINUE", assets->getFont(), BUTTON_SIZE, { 0, 0 })
{
	initDimBackground();
	initTutorialOverlayTitle();
	initInstructions();
	updateButtonPosition();
}

void TutorialOverlay::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (continueButton.isClicked(window))
		{
			game.switchScreen<GamePlayScreen>(window);
		}
	}
}

void TutorialOverlay::update()
{
	continueButton.update(window);
}

void TutorialOverlay::render(RenderWindow& window)
{
	window.draw(dimBackground);
	window.draw(tutorialOverlayTitle);
	
	for (const auto& instruction : instructions)
	{
		window.draw(instruction);
	}
		
	continueButton.draw(window);
}


void TutorialOverlay::initTutorialOverlayTitle()
{
	centerText(tutorialOverlayTitle, window, -TITLE_BODY_SPACING);
}

void TutorialOverlay::initInstructions()
{
	vector<string> instructionLines = {
		"Your goal is to dodge the balls and try to survive as long as possible!",
		"Learn the basic control:",
		"Move: WASD",
		"Aim : Mouse cursor",
		"Shoot : Left mouse button"
	};
	
	float verticalOffset = -TITLE_INSTRUCTION_SPACING *
		static_cast<float>(instructionLines.size() / 2);

	for (const auto& line : instructionLines)
	{
		Text instruction(assets->getFont(), line, BODY_TEXT_SIZE);
		centerText(instruction, window, verticalOffset);
		verticalOffset += INSTRUCTION_SPACING;
		instructions.push_back(instruction);
	}
}

void TutorialOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = { &continueButton };

	Text lastInstruction = instructions.back();
	positionButtons(lastInstruction, buttons, window);
}