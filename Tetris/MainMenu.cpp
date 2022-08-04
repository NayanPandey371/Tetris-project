#include "MainMenu.h"

void MainMenu::maininit()
{
	
}

void MainMenu::helper(sf::RenderTarget* target, sf::Text name, char* path)
{
	name.setFont(font);
	name.setCharacterSize(24);
	name.setStyle(sf::Text::Bold);
	name.setString("New Game");
	name.setPosition(target->getSize().x * 0.2, target->getSize().y * 0.5);
}


MainMenu::MainMenu()
{
	this->maininit();
}
void MainMenu::render(sf::RenderTarget* target)
{
	
}

void MainMenu::update()
{
}
