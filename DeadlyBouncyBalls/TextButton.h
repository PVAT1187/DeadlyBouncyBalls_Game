#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "SFML/Graphics.hpp"

class TextButton
{
	public:
		TextButton(const sf::String& textString, const sf::Font& font,
			unsigned int size, const sf::Vector2f& position);

		void update(const sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);

		void setPosition(const sf::Vector2f& newPosition);

		bool isClicked(const sf::RenderWindow& window) const;

		static const unsigned int BUTTON_SIZE;
		static const float TITLE_BUTTON_SPACING;
		static const float BUTTON_SPACING;

	private:
		sf::Text text;
		
		sf::Color normalColor;
		sf::Color hoverColor;

		bool isHovered;
};

#endif // !TEXT_BUTTON_H

