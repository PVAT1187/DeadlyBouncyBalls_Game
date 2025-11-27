#include "UIUtils.h"

using namespace sf;
using namespace std;

void UIUtils::colorAndCenterText(Text& text, RenderWindow& window)
{
	text.setFillColor(Color::White);

	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.size / 2.f);
	text.setPosition(
		static_cast<Vector2f>(window.getSize()) / 2.f);
}

void UIUtils::positionButtons(const Text& text,
	vector<TextButton*>& buttons, RenderWindow& window)
{
	float centerX = window.getSize().x / 2.f;
	float startY = text.getPosition().y + TextButton::TITLE_BUTTON_SPACING;

	buttons[0]->setPosition({ centerX, startY });

	size_t buttonsSize = buttons.size();
	for (size_t i = 1; i < buttonsSize; ++i)
	{
		float y = startY + TextButton::BUTTON_SPACING;
		buttons[i]->setPosition({ centerX, y });
	}
}