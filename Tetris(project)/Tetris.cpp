#include <iostream>
#include "Game.h"
#include "Play.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "home_scr.h"
int main()
{
	
	Game game;//INITIALIZES CONSTRUCTOR FROM GAME,since a play type data is declared in protected of game, it automatically initialized constructor of play class
	//Game loop
	while (game.getWindowIsOpen())
	{
		{
			//Update
			game.update();

			//Render
			game.render();
			//home.draw_bacground(this->window);
		}

	}
	return 0;
}