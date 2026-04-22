#include "Config/GameConfig.h"
#include "Core/App/Game.h"
#include "Core/Input/Input.h"
#include "Overlays/Tutorial/TutorialOverlay.h"
#include "Utilities/UI/UIUtils.h"

TutorialOverlay::TutorialOverlay(Game& game) :
	Overlay(game),
	tutorialOverlayTitle(sf::Text(game.getAssets().getFont(), "TUTORIAL", Config::UI::TITLE_TEXT_SIZE)),
	continueButton("CONTINUE", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 }),
	finished(false)
{
	initDimBackground();
	initTutorialOverlayTitle();
	initInstructions();
	updateButtonPosition();
}

void TutorialOverlay::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseButtonPressed>() &&
		event.getIf<sf::Event::MouseButtonPressed>()->button == 
		sf::Mouse::Button::Left)
	{
		if (continueButton.isClicked())
		{
			finished = true;
		}
	}
}

void TutorialOverlay::update(
	float deltaTime,
	const Input& Input)
{
	continueButton.update(Input.mousePosition);
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
	UIUtils::centerText(
		tutorialOverlayTitle, 
		game.getRenderer().getWindowSize(),
		-Config::UI::TITLE_BODY_SPACING
	);
}

void TutorialOverlay::initInstructions()
{
	std::vector<std::string> instructionLines = {
		"Your goal is to dodge the balls and try to survive as long as possible!",
		"Learn the basic control:",
		"Move: WASD",
		"Aim : Mouse cursor",
		"Shoot : Left mouse button"
	};
	
	float verticalOffset = -Config::UI::TITLE_INSTRUCTION_SPACING *
		(static_cast<float>(instructionLines.size()) / 2);

	for (const auto& line : instructionLines)
	{
		sf::Text instruction(
			game.getAssets().getFont(),
			line,
			Config::UI::BODY_TEXT_SIZE
		);

		UIUtils::centerText(
			instruction,
			game.getRenderer().getWindowSize(),
			verticalOffset
		);

		verticalOffset += Config::UI::BODY_TEXT_SPACING;
		instructions.push_back(instruction);
	}
}

void TutorialOverlay::updateButtonPosition()
{
	std::vector<TextButton*> buttons = { &continueButton };

	const sf::Text& lastInstruction = instructions.back();
	UIUtils::positionButtons(
		lastInstruction,
		buttons, 
		game.getRenderer().getWindowSize()
	);
}