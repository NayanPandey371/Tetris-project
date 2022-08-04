#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstring>


//Protected functions
void Game::initvariable()
{

	//Window pointer initialization
	this->window = nullptr;
}

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(720, 800), "Tetris", sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructors / Destructors
Game::Game()
{
	this->initvariable();
	this->initwindow();
}
Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::UpdateEvents()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->e.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
		play.Checkevent(e);
	}
}

//Functions
void Game::render()
{
	/*Render game objects
	--clear old frame
	--render objects
	--display frame in window
	*/
	this->window->clear();

	this->play.Render(this->window);
	if (strcmp(state, "play") == 0)
	{
		this->play.draw_shadow(this->window);
		this->play.draw_block(this->window);
		this->play.draw_Pblock(this->window);
		this->play.draw_world(this->window);
		this->play.clear_anm(this->window);
	}
	if (play.game_over())
	{
		this->play.draw_dead_block(this->window);
		strcpy_s(state, 9, "gameover");
	}
	this->window->display();
}

void Game::update()
{
	this->UpdateEvents();
	if (strcmp(state, "play") == 0)
		this->play.update();
}



