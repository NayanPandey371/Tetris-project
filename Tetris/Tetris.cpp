#include <iostream>
#include "Game.h"
#include "Play.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
	//Initializing Game engine
	Game game;
	//Game loop
	while (game.getWindowIsOpen())
	{
		//Update
		game.update();

		//Render
		game.render();

	}
	return 0;
}