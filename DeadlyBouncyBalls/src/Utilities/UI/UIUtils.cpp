#include "Config/GameConfig.h"
#include "Utilities/UI/UIUtils.h"

void UIUtils::centerText(
	sf::Text& text, 
	const sf::Vector2u& windowSize,
	float verticalOffset)
{
	sf::FloatRect textBounds = text.getLocalBounds();

	text.setOrigin(sf::Vector2f(
		textBounds.position.x + textBounds.size.x / 2.f,
		textBounds.position.y + textBounds.size.y / 2.f
	));

	text.setPosition(sf::Vector2f(
		windowSize.x / 2.f, 
		windowSize.y / 2.f + verticalOffset
	));
}

void UIUtils::positionButtons(
	const sf::Text& text,
	std::vector<TextButton*>& buttons, 
	const sf::Vector2u& windowSize)
{
	float centerX = windowSize.x / 2.f;
	float startY = text.getPosition().y + 
		Config::UI::TITLE_BUTTON_SPACING;

	if (buttons.empty())
		return;

	size_t buttonsSize = buttons.size();
	for (size_t i = 0; i < buttonsSize; ++i)
	{
		float y = startY + i * Config::UI::BUTTON_SPACING;
		buttons[i]->setPosition({ centerX, y });
	}
}