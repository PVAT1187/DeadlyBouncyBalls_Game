#include "Config/GameConfig.h"
#include "Core/App/Game.h"
#include "Core/Input/Input.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Utilities/UI/UIUtils.h"

GameStartScreen::GameStartScreen(Game& game) :
	Screen(game),
	gameTitleText(sf::Text(game.getAssets().getFont(), "DEADLY BOUNCY BALLS", Config::UI::TITLE_TEXT_SIZE)),
	playButton("PLAY", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 })
{
	initGameTitleText();
	updateButtonPosition();
}

void GameStartScreen::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseButtonPressed>() &&
		event.getIf<sf::Event::MouseButtonPressed>()->button == 
		sf::Mouse::Button::Left)
	{
		if (playButton.isClicked())
		{
			game.switchScreen<TutorialScreen>();
		}
		else if (quitButton.isClicked())
		{
			game.getRenderer().close();
		}
	}
}

void GameStartScreen::update(
	float deltaTime,
	const Input& Input)
{
	playButton.update(Input.mousePosition);
	quitButton.update(Input.mousePosition);
}

void GameStartScreen::render()
{
	auto& renderer = game.getRenderer();

	renderer.draw(gameTitleText);
	playButton.draw(renderer);
	quitButton.draw(renderer);
}

void GameStartScreen::initGameTitleText()
{
	UIUtils::centerText(
		gameTitleText, 
		game.getRenderer().getWindowSize()
	);
}

void GameStartScreen::updateButtonPosition()
{
	std::vector<TextButton*> buttons = { 
		&playButton, 
		&quitButton
	};

	UIUtils::positionButtons(
		gameTitleText, 
		buttons,
		game.getRenderer().getWindowSize()
	);
}