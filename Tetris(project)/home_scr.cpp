#include "home_scr.h"
bool home_scr::get_into_game(sf::RenderTarget* target)
{
	return false;
}
home_scr::home_scr()
{
	this->initilization();
}
void home_scr::initilization()
{
	this->shape.setSize(sf::Vector2f(720, 800)); //for falling blocks themselves in the game
	this->background.loadFromFile("texture/22117.jpg");
	this->shape.setTexture(&background);

	if (!font3.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");

	up_down = 0;
	mode = 0;
	playText.setFont(font3);
	playText.setCharacterSize(24);
	playText.setStyle(Text::Bold);
	playText.setString("PLAY");
	playText.setPosition(720 * 0.45, 800 * 0.4);
	playText.setFillColor(Color::Red);

	HighScores.setFont(font3);
	HighScores.setCharacterSize(24);
	HighScores.setStyle(Text::Bold);
	HighScores.setString("HIGH SCORES");
	HighScores.setPosition(720 * 0.45, 800 * 0.45);
	HighScores.setFillColor(Color::Blue);

	Instructions.setFont(font3);
	Instructions.setCharacterSize(24);
	Instructions.setStyle(Text::Bold);
	Instructions.setString("INSTRUCTIONS");
	Instructions.setPosition(720 * 0.45, 800 * 0.5);
	Instructions.setFillColor(Color::Blue);

	sound.setFont(font3);
	sound.setCharacterSize(24);
	sound.setStyle(Text::Bold);
	sound.setString("SOUND ON");
	sound.setPosition(720 * 0.45, 800 * 0.55);
	sound.setFillColor(Color::Blue);

	for (int i = 0; i < 10; i++)
	{
		volume[i].setFont(font3);
		volume[i].setCharacterSize(24);
		volume[i].setStyle(Text::Bold);
		volume[i].setString("I");
		volume[i].setFillColor(Color::Blue);
		volume[i].setPosition(720 * (0.65 + i * 0.01), 800 * 0.55);
	}
	for (int i = 0; i < volume_control; i++)
	{
		volume[i].setFillColor(Color::Red);
	}
	for (int i = volume_control; i < 10; i++)
	{
		volume[i].setFillColor(Color::Blue);
	}

	exit.setFont(font3);
	exit.setCharacterSize(24);
	exit.setStyle(Text::Bold);
	exit.setString("EXIT");
	exit.setPosition(720 * 0.45, 800 * 0.6);
	exit.setFillColor(Color::Blue);


}
void home_scr::draw_background(sf::RenderTarget* target)
{
	target->draw(this->shape);
}


void home_scr::draw_background_options(sf::RenderTarget* target)
{
	
	target->draw(this->HighScores);
	target->draw(this->Instructions);
	target->draw(this->sound);
	target->draw(this->exit);
	target->draw(this->playText);
	for (int i = 0; i < 10; i++)
	{
		target->draw(this->volume[i]);
	}
}



int home_scr::volume_level(sf::RenderTarget* target)
{
	return volume_control;
}
void home_scr::Checkevent(sf::Event evt)
{
	if (evt.type == sf::Event::KeyPressed)
	{
	    /* if (this->mode == 1 && evt.key.code == sf::Keyboard::Escape)
	     {
		this->mode = 0;
	     }*/
		 if (mode == 0 && evt.key.code == sf::Keyboard::Down)
		{

			if (this->up_down == 0)
			{
				playText.setFillColor(Color::Blue);
				HighScores.setFillColor(Color::Red);
				this->up_down = up_down + 1;

			}

			else if (this->up_down == 1)
			{
				HighScores.setFillColor(Color::Blue);
				Instructions.setFillColor(Color::Red);
				this->up_down = up_down + 1;

			}
			else if (this->up_down == 2)
			{
				Instructions.setFillColor(Color::Blue);
				sound.setFillColor(Color::Red);
				this->up_down = up_down + 1;

			}
			else if (this->up_down == 3)
			{
				sound.setFillColor(Color::Blue);
				exit.setFillColor(Color::Red);
				this->up_down = up_down + 1;
			}
			else if (this->up_down == 4)
			{
				playText.setFillColor(Color::Red);
				exit.setFillColor(Color::Blue);
				this->up_down = 0;
			}
		}
		else if (mode == 0 && evt.key.code == sf::Keyboard::Up)
		{

			if (this->up_down == 0)
			{
				playText.setFillColor(Color::Blue);
				exit.setFillColor(Color::Red);
				this->up_down = 4;

			}

			else if (this->up_down == 1)
			{
				HighScores.setFillColor(Color::Blue);
				playText.setFillColor(Color::Red);

				this->up_down = up_down - 1;

			}
			else if (this->up_down == 2)
			{
				Instructions.setFillColor(Color::Blue);
				HighScores.setFillColor(Color::Red);

				this->up_down = up_down - 1;

			}
			else if (this->up_down == 3)
			{
				sound.setFillColor(Color::Blue);
				Instructions.setFillColor(Color::Red);

				this->up_down = up_down - 1;
			}
			else if (this->up_down == 4)
			{
				sound.setFillColor(Color::Red);
				exit.setFillColor(Color::Blue);
				this->up_down = up_down - 1;
			}
		}
		if (mode == 0 && up_down == 0 && evt.key.code == Keyboard::Return)
		{
			playText_check = true;
		}
		else if (mode == 0 && up_down == 1 && evt.key.code == Keyboard::Return)
		{
			HighScores_check = true;
		}
		else if (mode == 0 && up_down == 2 && evt.key.code == Keyboard::Return)
		{
			Instructions_check = true;
		}
		else if (mode == 0 && up_down == 3 && evt.key.code == Keyboard::Return)
		{
			sound_check = true;
		}
		else if (mode == 0 && up_down == 4 && evt.key.code == Keyboard::Return)
		{
			exit_check = true;
		}
		else if (mode == 0 && up_down==3 && evt.key.code == sf::Keyboard::Right)
		{
			if (this->volume_control == 0)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 1)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			
			}
			else if (this->volume_control == 2)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
		
			}
			else if (this->volume_control == 3)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			
			}
			else if (this->volume_control == 4)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			
			else if (this->volume_control == 5)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 6)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 7)
			{
				volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 8)
			{
			volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 9)
			{
			volume_control += 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
		}
		else if (mode == 0 && up_down == 3  && evt.key.code == sf::Keyboard::Left)
		{
			if (this->volume_control == 1)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}

			}
			else if (this->volume_control == 2)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}

			}
			else if (this->volume_control == 3)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}

			}
			else if (this->volume_control == 4)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}

			else if (this->volume_control == 5)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 6)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 7)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 8)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 9)
			{
				volume_control -=1 ;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
			else if (this->volume_control == 10)
			{
				volume_control -= 1;
				for (int i = 0; i < volume_control; i++)
				{
					volume[i].setFillColor(Color::Red);
				}
				for (int i = volume_control; i < 10; i++)
				{
					volume[i].setFillColor(Color::Blue);
				}
			}
 
		}
		
	}
}
