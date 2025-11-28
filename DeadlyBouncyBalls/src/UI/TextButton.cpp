#include "UI/TextButton.h"

using namespace sf;

constexpr float NORMAL_SCALE = 1.f;
constexpr float HOVER_SCALE = 1.2f;

constexpr float SMOOTH_SCALING_MULTIPLIER = 0.2f;

constexpr unsigned int TextButton::BUTTON_SIZE = 50;
constexpr float TextButton::TITLE_BUTTON_SPACING = 200.f;
constexpr float TextButton::BUTTON_SPACING = 80.f;

TextButton::TextButton(const String& textString, const Font& font,
	unsigned int size, const Vector2f& position) :
	text(Text(font, textString, size)),
	normalColor(Color::White), hoverColor(Color::Yellow),
	isHovered(false)
{
	text.setFillColor(normalColor);

	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.size / 2.f);
	text.setPosition(position);
}

void TextButton::update(const RenderWindow& window)
{
	Vector2f mousePos = window.mapPixelToCoords(
		Mouse::getPosition(window));

	if (text.getGlobalBounds().contains(mousePos))
	{
		text.setFillColor(hoverColor);
		isHovered = true;
	}
	else
	{
		text.setFillColor(normalColor);
		isHovered = false;
	}

	float targetScale = isHovered ? HOVER_SCALE : NORMAL_SCALE;
	float currentScale = text.getScale().x;
	float scaleStep = (targetScale - currentScale) * SMOOTH_SCALING_MULTIPLIER;
	text.setScale(Vector2f(currentScale + scaleStep, currentScale + scaleStep));
}

void TextButton::draw(RenderWindow& window)
{
	window.draw(text);
}

void TextButton::setPosition(const sf::Vector2f& newPosition)
{
	text.setPosition(newPosition);
}

bool TextButton::isClicked(const RenderWindow& window) const
{
	return isHovered && Mouse::isButtonPressed(Mouse::Button::Left);
}