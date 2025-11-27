#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "TextButton.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace UIUtils
{
	void colorAndCenterText(sf::Text& text, sf::RenderWindow& window);
	void positionButtons(const sf::Text& text,
		std::vector<TextButton*>& buttons,
		sf::RenderWindow& window);
};

#endif // !UI_UTILS_H
