#include "GameStartScreen.h"
#include "Game.h"

using namespace sf;

GameStartScreen::GameStartScreen(Game& game, RenderWindow& window) :
	Screen(game),
	game(game),
	window(window),
	gameTitleText(Text(game.getFont(), "DEADLY BOUNCY BALLS", Screen::TITLE_TEXT_SIZE)),
	playButton("PLAY", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 }),
	quitButton("QUIT", game.getFont(), TextButton::BUTTON_SIZE, { 0, 0 })
{
	initGameTilteText();
	updateButtonPositon();
}

void GameStartScreen::handleEvent(const Event& event) {}

void GameStartScreen::update(float deltaTime) 
{
	playButton.update(window);
	quitButton.update(window);

	if (playButton.isClicked(window))
	{
		game.switchToGamePlayScreen();
	}
	else if (quitButton.isClicked(window))
	{
		window.close();
	}
}

void GameStartScreen::render(RenderWindow& window)
{
	window.draw(gameTitleText);
	playButton.draw(window);
	quitButton.draw(window);
}

void GameStartScreen::initGameTilteText()
{
	gameTitleText.setFillColor(Color::White);

	FloatRect gameTitleTextBounds = gameTitleText.getLocalBounds();
	gameTitleText.setOrigin(gameTitleTextBounds.size / 2.f);
	gameTitleText.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}


void GameStartScreen::updateButtonPositon()
{
	float startY = gameTitleText.getPosition().y + TextButton::TITLE_BUTTON_SPACING;

	playButton.setPosition({ window.getSize().x / 2.f, startY });
	quitButton.setPosition({ window.getSize().x / 2.f, startY + TextButton::BUTTON_SPACING });
}