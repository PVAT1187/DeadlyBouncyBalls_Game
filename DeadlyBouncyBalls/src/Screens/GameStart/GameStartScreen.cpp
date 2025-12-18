#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GameDemo/GameDemoScreen.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game, window, &game.getAssets()),
	gameTitleText(Text(assets->getFont(), "DEADLY BOUNCY BALLS", TITLE_TEXT_SIZE)),
	playButton("PLAY", assets->getFont(), BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", assets->getFont(), BUTTON_SIZE, { 0, 0 })
{
	initGameTitleText();
	updateButtonPosition();
}

void GameStartScreen::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (playButton.isClicked(window))
		{
			game.switchScreen<GameDemoScreen>(window);
		}
		else if (quitButton.isClicked(window))
		{
			window.close();
		}
	}
}

void GameStartScreen::update(float deltaTime) 
{
	playButton.update(window);
	quitButton.update(window);
}

void GameStartScreen::render(RenderWindow& window)
{
	window.draw(gameTitleText);
	playButton.draw(window);
	quitButton.draw(window);
}

void GameStartScreen::initGameTitleText()
{
	centerTitleText(gameTitleText, window);
}

void GameStartScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = {&playButton, &quitButton};
	positionButtons(gameTitleText, buttons, window);
}