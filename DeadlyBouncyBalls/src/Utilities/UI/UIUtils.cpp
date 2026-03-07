#include "Config/Constants/GameConstants.h"
#include "Utilities/UI/UIUtils.h"

using namespace sf;
using namespace std;

void UIUtils::centerText(Text& text, const Vector2u& windowSize,
	float verticalOffset)
{
	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(Vector2f(
		textBounds.position.x + textBounds.size.x / 2.f,
		textBounds.position.y + textBounds.size.y / 2.f));
	text.setPosition(Vector2f(
		windowSize.x / 2.f, 
		windowSize.y / 2.f + verticalOffset));
}

void UIUtils::positionButtons(const Text& text,
	vector<TextButton*>& buttons, const Vector2u& windowSize)
{
	float centerX = windowSize.x / 2.f;
	float startY = text.getPosition().y + TITLE_BUTTON_SPACING;

	if (buttons.empty())
		return;

	size_t buttonsSize = buttons.size();
	for (size_t i = 0; i < buttonsSize; ++i)
	{
		float y = startY + i * BUTTON_SPACING;
		buttons[i]->setPosition({ centerX, y });
	}
}