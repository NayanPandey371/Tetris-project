#pragma once
#include "Play.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Game engine class
class Game
{
protected:
	//window
	sf::RenderWindow* window;
	sf::Event e;

	Play play;

	char state[20] = "play";

	//Initializer functions
	void initvariable();
	void initwindow();
public:
	//Constructor/Destructor
	Game();
	~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void UpdateEvents();
	void render();
	void update();
};

