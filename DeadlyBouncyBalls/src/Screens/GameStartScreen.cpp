#include "Screens/GameStartScreen.h"
#include "UI/UIUtils.h"
#include "Core/Game.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game, window),
	gameTitleText(Text(game.getFont(), "DEADLY BOUNCY BALLS", Screen::TITLE_TEXT_SIZE)),
	playButton("PLAY", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	initGameTilteText();
	updateButtonPositon();
}

void GameStartScreen::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (playButton.isClicked(window))
		{
			game.switchToGameDemoScreen();
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

void GameStartScreen::initGameTilteText()
{
	centerTitleText(gameTitleText, window);
}


void GameStartScreen::updateButtonPositon()
{
	vector<TextButton*> buttons = {&playButton, &quitButton};
	positionButtons(gameTitleText, buttons, window);
}