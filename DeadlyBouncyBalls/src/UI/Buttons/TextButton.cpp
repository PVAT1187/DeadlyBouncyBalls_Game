#include "Config/GameConfig.h"
#include "UI/Buttons/TextButton.h"

TextButton::TextButton(
	const sf::String& textString, 
	const sf::Font& font,
	unsigned int size, 
	const sf::Vector2f& position) :
	buttonText(sf::Text(font, textString, size)),
	normalColor(sf::Color::White), hoverColor(sf::Color::Yellow),
	isHovered(false)
{
	buttonText.setFillColor(normalColor);

	sf::FloatRect textBounds = buttonText.getLocalBounds();
	buttonText.setOrigin(textBounds.size / 2.f);
	buttonText.setPosition(position);
}

void TextButton::update(const sf::Vector2f& mousePosition)
{
	updateHoverState(mousePosition);
	updateScaling();
}

void TextButton::draw(Renderer& renderer) const
{
	renderer.draw(buttonText);
}

void TextButton::setPosition(const sf::Vector2f& newPosition)
{
	buttonText.setPosition(newPosition);
}

bool TextButton::isClicked() const
{
	return isHovered && 
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void TextButton::updateHoverState(const sf::Vector2f& mousePosition)
{
	isHovered = buttonText.getGlobalBounds().contains(mousePosition);
	buttonText.setFillColor(isHovered ? hoverColor : normalColor);
}

void TextButton::updateScaling()
{
	float targetScale = isHovered ? 
		Config::Button::HOVER_SCALE : 
		Config::Button::NORMAL_SCALE;
	float currentScale = buttonText.getScale().x;
	float scaleStep = 
		(targetScale - currentScale) * 
		Config::Button::SMOOTH_SCALING_MULTIPLIER;
	float newScale = currentScale + scaleStep;
	buttonText.setScale(sf::Vector2f(newScale, newScale));
}