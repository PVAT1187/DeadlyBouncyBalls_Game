#include "Config/GameConfig.h"
#include "Core/App/Game.h"
#include "Screens/GameStart/GameStartScreen.h"
#include "Screens/GamePlay/GamePlayScreen.h"
#include "Screens/GameOver/GameOverScreen.h"

GamePlayScreen::GamePlayScreen(Game& game) :
	Screen(game),
	gameWorld(game.getAssets(), game.getRenderer().getWindowSize()),
	survivalTimeText(sf::Text(game.getAssets().getFont(), "", Config::UI::BODY_TEXT_SIZE)),
	scoreText(sf::Text(game.getAssets().getFont(), "", Config::UI::BODY_TEXT_SIZE)),
	survivalClock()
{
	game.getRenderer().showCursor(false);
	initText();
	survivalClock.restart();
}

void GamePlayScreen::handleEvent(const sf::Event& event)
{
	if (event.is<sf::Event::KeyPressed>() &&
		event.getIf<sf::Event::KeyPressed>()->code ==
		sf::Keyboard::Key::Escape)
	{
		if (!pauseOverlay)
		{
			pauseOverlay = std::make_unique<PauseMenuOverlay>(game);
			game.getRenderer().showCursor(true);
		}
		else
		{
			pauseOverlay.reset();
			game.getRenderer().showCursor(false);
		}
	}

	if (pauseOverlay)
	{
		pauseOverlay->handleEvent(event);
		
		if (pauseOverlay->hasSelectedOption())
		{
			switch (pauseOverlay->getSelectedOption())
			{
				case PauseMenuOption::RESUME:
					pauseOverlay.reset();
					game.getRenderer().showCursor(false);
					break;
				case PauseMenuOption::MAIN_MENU:
					game.switchScreen<GameStartScreen>();
					break;
			}
		}
	}
}

void GamePlayScreen::update(
	float deltaTime,
	const Input& Input)
{	
	if (pauseOverlay)
	{
		pauseOverlay->update(deltaTime, Input);
		return;
	}
	
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	int score = gameWorld.getScore();

	updateText(survivalTime, score);
	
	gameWorld.update(deltaTime, Input);
	if (gameWorld.isGameOver())
	{
		game.switchScreen<GameOverScreen>(survivalTime, score);
		return;
	}
}

void GamePlayScreen::render()
{
	auto& renderer = game.getRenderer();
	
	gameWorld.render(renderer);
	renderer.draw(survivalTimeText);
	renderer.draw(scoreText);

	if (pauseOverlay)
		pauseOverlay->render();
}

void GamePlayScreen::initText()
{
	sf::Vector2u windowSize = game.getRenderer().getWindowSize();
	
	survivalTimeText.setFillColor(sf::Color::White);
	survivalTimeText.setPosition(sf::Vector2f(0, 0));
	
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f(
		windowSize.x - Config::UI::SCORE_TEXT_OFFSET,
		0
	));
}

void GamePlayScreen::updateText(float survivalTime, int score)
{
	survivalTimeText.setString("Survival Time: " +
		std::to_string(survivalTime) + "s");

	scoreText.setString("Score: " + std::to_string(score));
	sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setOrigin(sf::Vector2f(scoreTextBounds.size.x, 0));
}