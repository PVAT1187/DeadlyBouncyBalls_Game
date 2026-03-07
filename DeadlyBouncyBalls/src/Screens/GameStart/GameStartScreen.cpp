#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/Tutorial/TutorialScreen.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

GameStartScreen::GameStartScreen(Game& game) :
	Screen(game),
	gameTitleText(Text(game.getAssets().getFont(), "DEADLY BOUNCY BALLS", TITLE_TEXT_SIZE)),
	playButton("PLAY", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 })
{
	initGameTitleText();
	updateButtonPosition();
}

void GameStartScreen::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
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

void GameStartScreen::update(float deltaTime,
	const InputState& inputState)
{
	playButton.update(inputState.mousePosition);
	quitButton.update(inputState.mousePosition);
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
	centerText(gameTitleText, game.getRenderer().getWindowSize());
}

void GameStartScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = {&playButton, &quitButton};
	positionButtons(gameTitleText, buttons, 
		game.getRenderer().getWindowSize());
}