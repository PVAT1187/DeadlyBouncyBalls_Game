#include "Config/Constants/GameConstants.h"
#include "UI/Buttons/TextButton.h"

using namespace sf;

TextButton::TextButton(const String& textString, const Font& font,
	unsigned int size, const Vector2f& position) :
	buttonText(Text(font, textString, size)),
	normalColor(Color::White), hoverColor(Color::Yellow),
	isHovered(false)
{
	buttonText.setFillColor(normalColor);

	FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.size / 2.f);
	buttonText.setPosition(position);
}

void TextButton::update(const Vector2f& mousePosition)
{
	updateHoverState(mousePosition);
	updateScaling();
}

void TextButton::draw(Renderer& renderer) const
{
	renderer.draw(buttonText);
}

void TextButton::setPosition(const Vector2f& newPosition)
{
	buttonText.setPosition(newPosition);
}

bool TextButton::isClicked() const
{
	return isHovered && Mouse::isButtonPressed(Mouse::Button::Left);
}

void TextButton::updateHoverState(const Vector2f& mousePosition)
{
	isHovered = buttonText.getGlobalBounds().contains(mousePosition);
	buttonText.setFillColor(isHovered ? hoverColor : normalColor);
}

void TextButton::updateScaling()
{
	float targetScale = isHovered ? HOVER_SCALE : NORMAL_SCALE;
	float currentScale = buttonText.getScale().x;
	float scaleStep = (targetScale - currentScale) * SMOOTH_SCALING_MULTIPLIER;
	float newScale = currentScale + scaleStep;
	buttonText.setScale(Vector2f(newScale, newScale));
}