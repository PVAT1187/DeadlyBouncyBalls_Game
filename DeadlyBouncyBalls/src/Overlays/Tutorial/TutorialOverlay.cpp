#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Overlays/Tutorial/TutorialOverlay.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

TutorialOverlay::TutorialOverlay(Game& game) :
	Overlay(game),
	tutorialOverlayTitle(Text(game.getAssets().getFont(), "TUTORIAL", TITLE_TEXT_SIZE)),
	continueButton("CONTINUE", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 }),
	finished(false)
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
		if (continueButton.isClicked())
		{
			finished = true;
		}
	}
}

void TutorialOverlay::update(float deltaTime,
	const InputState& inputState)
{
	continueButton.update(inputState.mousePosition);
}

void TutorialOverlay::render()
{
	auto& renderer = game.getRenderer();
	
	renderer.draw(dimBackground);
	renderer.draw(tutorialOverlayTitle);
	
	for (const auto& instruction : instructions)
	{
		renderer.draw(instruction);
	}
		
	continueButton.draw(renderer);
}

bool TutorialOverlay::isFinished() const
{
	return finished;
}

void TutorialOverlay::initTutorialOverlayTitle()
{
	centerText(tutorialOverlayTitle, 
		game.getRenderer().getWindowSize(),
		-TITLE_BODY_SPACING);
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
		(static_cast<float>(instructionLines.size() / 2));

	for (const auto& line : instructionLines)
	{
		Text instruction(game.getAssets().getFont(), line, BODY_TEXT_SIZE);
		centerText(instruction, game.getRenderer().getWindowSize(),
			verticalOffset);
		verticalOffset += INSTRUCTION_SPACING;
		instructions.push_back(instruction);
	}
}

void TutorialOverlay::updateButtonPosition()
{
	vector<TextButton*> buttons = { &continueButton };

	const Text& lastInstruction = instructions.back();
	positionButtons(lastInstruction, buttons, 
		game.getRenderer().getWindowSize());
}