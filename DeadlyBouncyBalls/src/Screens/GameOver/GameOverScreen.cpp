#include "Config/Constants/GameConstants.h"
#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;
using namespace UIUtils;

GameOverScreen::GameOverScreen(Game& game, float finalSurvivalTime) :
	Screen(game),
	gameOverText(Text(game.getAssets().getFont(), "GAME OVER", TITLE_TEXT_SIZE)),
	finalSurvivalTimeText(Text(game.getAssets().getFont(), "", BODY_TEXT_SIZE)),
	playAgainButton("PLAY AGAIN", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getAssets().getFont(), BUTTON_SIZE, { 0, 0 })
{
	game.getRenderer().showCursor(true);
	
	initGameOverText();
	initFinalSurvivalTimeText(finalSurvivalTime);
	updateButtonPosition();
}

void GameOverScreen::handleEvent(const Event& event) 
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		if (playAgainButton.isClicked())
		{
			game.switchScreen<GamePlayScreen>();
		}
		else if (mainMenuButton.isClicked())
		{
			game.switchScreen<GameStartScreen>();
		}
	}
}

void GameOverScreen::update(float deltaTime,
	const InputState& inputState)
{
	playAgainButton.update(inputState.mousePosition);
	mainMenuButton.update(inputState.mousePosition);
}

void GameOverScreen::render()
{
	auto& renderer = game.getRenderer();
	
	renderer.draw(gameOverText);
	renderer.draw(finalSurvivalTimeText);
	playAgainButton.draw(renderer);
	mainMenuButton.draw(renderer);
}

void GameOverScreen::initGameOverText()
{
	centerText(gameOverText, game.getRenderer().getWindowSize());
}

void GameOverScreen::initFinalSurvivalTimeText(float finalSurvivalTime)
{
	finalSurvivalTimeText.setString("Survived: " + 
		to_string(finalSurvivalTime) + "s");
	centerText(finalSurvivalTimeText, 
		game.getRenderer().getWindowSize(),
		TITLE_BODY_SPACING);
}

void GameOverScreen::updateButtonPosition()
{
	vector<TextButton*> buttons = { &playAgainButton, &mainMenuButton };
	positionButtons(gameOverText, buttons, 
		game.getRenderer().getWindowSize());
} 