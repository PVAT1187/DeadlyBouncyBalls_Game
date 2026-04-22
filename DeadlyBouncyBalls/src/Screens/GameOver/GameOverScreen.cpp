#include "Config/GameConfig.h"
#include "Core/App/Game.h"
#include "Core/Input/Input.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"
#include "Utilities/UI/UIUtils.h"

GameOverScreen::GameOverScreen(
	Game& game, 
	float finalSurvivalTime, 
	int score) :
	Screen(game),
	gameOverText(sf::Text(game.getAssets().getFont(), "GAME OVER", Config::UI::TITLE_TEXT_SIZE)),
	finalSurvivalTimeText(sf::Text(game.getAssets().getFont(), "", Config::UI::BODY_TEXT_SIZE)),
	scoreText(sf::Text(game.getAssets().getFont(), "", Config::UI::BODY_TEXT_SIZE)),
	playAgainButton("PLAY AGAIN", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 }),
	mainMenuButton("MAIN MENU", game.getAssets().getFont(), Config::Button::BUTTON_SIZE, { 0, 0 })
{
	game.getRenderer().showCursor(true);
	
	initText(finalSurvivalTime, score);
	updateButtonPosition();
}

void GameOverScreen::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::MouseButtonPressed>() &&
		event.getIf<sf::Event::MouseButtonPressed>()->button == 
		sf::Mouse::Button::Left)
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
	const Input& Input)
{
	playAgainButton.update(Input.mousePosition);
	mainMenuButton.update(Input.mousePosition);
}

void GameOverScreen::render()
{
	auto& renderer = game.getRenderer();
	
	renderer.draw(gameOverText);
	renderer.draw(finalSurvivalTimeText);
	renderer.draw(scoreText);
	playAgainButton.draw(renderer);
	mainMenuButton.draw(renderer);
}

void GameOverScreen::initText(float finalSurvivalTime, int score)
{
	finalSurvivalTimeText.setString("Survived: " + 
		std::to_string(finalSurvivalTime) + "s");

	scoreText.setString("Score: " + std::to_string(score));

	UIUtils::centerText(
		gameOverText,
		game.getRenderer().getWindowSize()
	);

	UIUtils::centerText(
		finalSurvivalTimeText, 
		game.getRenderer().getWindowSize(),
		Config::UI::TITLE_BODY_SPACING
	);

	UIUtils::centerText(
		scoreText, 
		game.getRenderer().getWindowSize(),
		Config::UI::TITLE_BODY_SPACING + 
		Config::UI::BODY_TEXT_SPACING
	);
}

void GameOverScreen::updateButtonPosition()
{
	std::vector<TextButton*> buttons = { 
		&playAgainButton, 
		&mainMenuButton 
	};

	UIUtils::positionButtons(
		gameOverText, 
		buttons, 
		game.getRenderer().getWindowSize()
	);
} 