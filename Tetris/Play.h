#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class Play
{
private:
	//Initialize game variables
	const float cell_size = 40.0;
	const int w_cnt = 10;
	const int h_cnt = 20;

	int world[20][10];
	int world_temp[20][10] = {0};

	int next;//to initialize with a random block on new block as (kind=next in new block function)
	int px, py;//preview
	int kind;// block kind (block from 1 to 7)
	int cx, cy;
	int sx, sy;
	int cl_row;

	int block[7][4][4] = 
	{
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,
	};
	int block_board[7][4][4];
	int check_line[20] = { 0 };

	sf::Clock clock;
	sf::Clock clock1;

	bool line_check = false;
	bool stop_animation = false;
	bool game_over_check = false;

	//Initialize game objects
	sf::RectangleShape cell, grid, explode, shadow, preview_border, preview_border1, p_block, dead_block;
	sf::Texture texture;
	sf::Vector2u textureSize;

	//Initialize game objects
	void initGameObj();
public:
	//Initialize game variables
	Play();

	//Functions for the game logic
	void rotate();
	bool game_over();
	void new_block();
	void preview_block();
	bool check_block();
	void clear_lines();
	void clear_lines_d();
	bool go_down();

	//Update
	void update();
	
	//Render
	void Render(sf::RenderTarget* target);
	void p_draw();
	void draw_cell(sf::RenderTarget* target);

	void Checkevent(sf::Event ev);

	bool shadow_check();
	void draw_shadow(sf::RenderTarget* target);
	void clear_anm(sf::RenderTarget* target);
	void draw_block(sf::RenderTarget* target);
	void draw_world(sf::RenderTarget* target);
	void draw_Pblock(sf::RenderTarget* target);

	void draw_dead_block(sf::RenderTarget* target);

};


