#include "GamePlayScreen.h"
#include "Game.h"

#include <iostream>

using namespace sf;
using namespace std;

const VideoMode& DESKTOP_MODE = VideoMode::getDesktopMode();

GamePlayScreen::GamePlayScreen(Game& game, RenderWindow& window) :
	game(game),
	window(window),
	player(window),
	ball(window),
	font(),
	survivalClock(),
	survivalTimeText(Text(font, "", 25))
{
	initFont();
	initSurvivalTimeText();

	survivalClock.restart();
}

void GamePlayScreen::handleEvent(const Event& event)
{
	if (event.is<Event::MouseButtonPressed>() &&
		event.getIf<Event::MouseButtonPressed>()->button == Mouse::Button::Left)
	{
		player.rotate(90.f);
	}
}

void GamePlayScreen::update(float deltaTime)
{
	float survivalTime = survivalClock.getElapsedTime().asSeconds();
	survivalTimeText.setString("Survival Time: " +
		to_string(survivalTime) + "s");

	ball.update(deltaTime, window);
	player.update(window);
	
	if (ball.isCollidingWithPlayer(player))
	{
		game.switchToGameOverScreen(survivalTime);
	}
}

void GamePlayScreen::render(RenderWindow& window)
{
	player.draw(window);
	ball.draw(window);
	window.draw(survivalTimeText);
}

void GamePlayScreen::initFont()
{
	if (!font.openFromFile("C:/Users/pvat2/source/Personal Projects/DeadlyBouncyBalls/assets/fonts/arial.ttf"))
	{
		cerr << "Failed to load font!" << endl;
	}
}

void GamePlayScreen::initSurvivalTimeText()
{
	survivalTimeText.setFont(font);
	survivalTimeText.setFillColor(Color::White);

	FloatRect survivalTimeTextBounds = survivalTimeText.getLocalBounds();
	survivalTimeText.setOrigin(survivalTimeTextBounds.size / 2.f);
	survivalTimeText.setPosition(Vector2f(0, 0));
}