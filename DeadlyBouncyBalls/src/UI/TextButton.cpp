#include "GameConstants.h"
#include "UI/TextButton.h"

using namespace sf;

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
	updateHoverState(window);
	updateScaling();
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

void TextButton::updateHoverState(const sf::RenderWindow& window)
{
	Vector2f mousePos = window.mapPixelToCoords(
		Mouse::getPosition(window));
	isHovered = text.getGlobalBounds().contains(mousePos);
	text.setFillColor(isHovered ? hoverColor : normalColor);
}

void TextButton::updateScaling()
{
	float targetScale = isHovered ? HOVER_SCALE : NORMAL_SCALE;
	float currentScale = text.getScale().x;
	float scaleStep = (targetScale - currentScale) * SMOOTH_SCALING_MULTIPLIER;
	float newScale = currentScale + scaleStep;
	text.setScale(Vector2f(newScale, newScale));
}