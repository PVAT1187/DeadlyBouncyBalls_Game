#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "UI/Buttons/TextButton.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace UIUtils
{
	void centerTitleText(sf::Text& text, sf::RenderWindow& window);
	void centerBodyText(sf::Text& text, sf::RenderWindow& window,
		float verticalOffset);
	void positionButtons(const sf::Text& text,
		std::vector<TextButton*>& buttons,
		sf::RenderWindow& window);
};

#endif // !UI_UTILS_H
