#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "UI/Buttons/TextButton.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace UIUtils
{
	void centerText(sf::Text& text, 
		const sf::Vector2u& windowSize,
		float verticalOffset = 0.f);
	void positionButtons(const sf::Text& text,
		std::vector<TextButton*>& buttons,
		const sf::Vector2u& windowSize);
};

#endif // !UI_UTILS_H
