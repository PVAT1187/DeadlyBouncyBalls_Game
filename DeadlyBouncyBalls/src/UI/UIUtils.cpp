#include "Core/GameConstants.h"
#include "UI/UIUtils.h"

using namespace sf;
using namespace std;

void UIUtils::centerTitleText(Text& text, RenderWindow& window)
{
	text.setFillColor(Color::White);

	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.size / 2.f);
	text.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}

void UIUtils::centerBodyText(sf::Text& text, sf::RenderWindow& window,
	float verticalOffset)
{
	text.setFillColor(Color::White);

	Vector2f centerPosition = static_cast<Vector2f>
		(window.getSize()) / 2.f;
	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.size / 2.f);
	text.setPosition(Vector2f(
		centerPosition.x, centerPosition.y + verticalOffset));
}

void UIUtils::positionButtons(const Text& text,
	vector<TextButton*>& buttons, RenderWindow& window)
{
	float centerX = window.getSize().x / 2.f;
	float startY = text.getPosition().y + TITLE_BUTTON_SPACING;

	buttons[0]->setPosition({ centerX, startY });

	size_t buttonsSize = buttons.size();
	for (size_t i = 1; i < buttonsSize; ++i)
	{
		float y = startY + BUTTON_SPACING;
		buttons[i]->setPosition({ centerX, y });
	}
}