#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "UI/Buttons/TextButton.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace UIUtils
{
	void centerText(sf::Text& text, sf::RenderWindow& window,
		float verticalOffset = 0.f);
	void positionButtons(const sf::Text& text,
		std::vector<TextButton*>& buttons,
		sf::RenderWindow& window);
};

#endif // !UI_UTILS_H
