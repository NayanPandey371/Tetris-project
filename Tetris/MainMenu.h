#pragma once

#include <SFML/Graphics.hpp>

class MainMenu
{
private:
	sf::Font font;
	sf::Text txt;
	void maininit();
	void helper(sf::RenderTarget* target, sf::Text name, char* path);
public:
	MainMenu();
	void render(sf::RenderTarget* target);
	void update();
};

