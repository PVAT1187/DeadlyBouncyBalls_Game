#ifndef TEXT_BUTTON_H
#define TEXT_BUTTON_H

#include "Core/Rendering/Renderer.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

class TextButton
{
	public:
		TextButton(const sf::String& textString, 
			const sf::Font& font,
			unsigned int size, 
			const sf::Vector2f& position);

		void update(const sf::Vector2f& mousePosition);
		void draw(Renderer& renderer) const;

		void setPosition(const sf::Vector2f& newPosition);

		bool isClicked() const;

	private:
		sf::Text buttonText;
		
		sf::Color normalColor;
		sf::Color hoverColor;

		bool isHovered;

		void updateHoverState(const sf::Vector2f& mousePosition);
		void updateScaling();
};

#endif // !TEXT_BUTTON_H

