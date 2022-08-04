#include "Play.h"

void Play::initGameObj()
{
	this->cell.setSize(sf::Vector2f(cell_size, cell_size));//for falling blocks themselves in the game
	this->texture.loadFromFile("texture/image.png");
	this->cell.setTexture(&texture);
	this->textureSize = texture.getSize();
	this->textureSize.x /= 10;
	this->textureSize.y /= 1;

	this->texture.setSmooth(false);

	this->grid.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));// for grid//change value and see changes
	this->dead_block.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));//for block seen after game over

	this->dead_block.setTexture(&texture);

	

	this->explode.setSize(sf::Vector2f(cell_size - 15, cell_size - 15));//size is 25 // explode is not quite appporiate name...it is acutally 
	//for line clearing animation 

	this->explode.setTexture(&texture);

	this->shadow.setSize(sf::Vector2f(cell_size - 2, cell_size - 2));

	this->preview_border.setSize(sf::Vector2f(320, h_cnt * cell_size));// to get that white line that seperates the grid from side window
	preview_border.setFillColor(sf::Color(100, 100, 100, 150));
	preview_border.setOutlineThickness(1);
	preview_border.setPosition(w_cnt * cell_size, 0);

	this->preview_border1.setSize(sf::Vector2f(cell_size * 4, cell_size * 4));//to get the preview block window border(that white border)
	preview_border1.setFillColor(sf::Color(25, 0, 0, 255));
	preview_border1.setOutlineThickness(-1);
	preview_border1.setPosition((w_cnt + 2) * cell_size, cell_size * 2);
}


Play::Play()
{
	int kind = rand() % 7;
	new_block();
	preview_block();
	this->initGameObj();
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
				block_board[i][j][k] = block[i][j][k];
		}
	}
}

bool Play::game_over()
{
	int temp2 = 4;
	if (kind == 0)
		temp2 = 3; //because(____) this starts from 3
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		if (block_board[kind][y][x])
			if (world_temp[y][x + temp2])
			{
				return true;//newly added to fix some bug..added on july 26
			}
	return false;
};

void Play::new_block()
{
	kind = next, cx = 4, cy = 0;//cx is set to 4 so to make blocks fall from the center from the top of the grid...if cx=0,block fall from left most part
	for (int y = 0; y < 4; y++)//kind=next because kind should be the block seen in the preview window(next is for preview window..read comment below)
		for (int x = 0; x < 4; x++)
			block_board[kind][y][x] = block[kind][y][x];// we are writing value is block_board()() to cause that delay effect..ask me if confused
	if (kind == 0)
		cx--;
}

void Play::preview_block()
{
	next = rand() % 7;//(next is used for block for preview window)
	px = w_cnt + 2 + 1;
	py = 2 + 1;
	if (next == 0)//for this(----) block to get it to center in the preview window
	{
		px--;//remove this px-- and run the program and look for(----) this block in preview window...you will see why it is added
	}
}

bool Play::check_block()
{
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
	{
		if (block_board[kind][y][x] == 0) continue;
		if (x + cx < 0 || x + cx >= w_cnt || y + cy >= h_cnt) return false; // hit wall
		if (world[cy + y][cx + x]) return false;//hit another block
	}
	return true;
}



void Play::clear_lines_d()
{
	for (int y = h_cnt - 1; y >= 0; y--)for (int x = 0; x < w_cnt; x++)
	{

		world[y][x] = world_temp[y][x];
	}
	stop_animation = true;
}


void Play::rotate()
{
	int len = 0; //to check rotation block size
	int temp[4][4];// check rotation block size
	int d[4][4] = { 0 };
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
	{
		temp[y][x] = block_board[kind][y][x];
		if (block_board[kind][y][x])
			len = std::max(std::max(x, y) + 1, len);
	}

	//rotate conter-clock wise 90 degree
	for (int y = 0; y < len; y++)for (int x = 0; x < len; x++)
		if (block_board[kind][y][x])
			d[len - 1 - x][y] = 1;// d[x][len - 1 - y] for clockwise if we add clockwise button as well
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		block_board[kind][y][x] = d[y][x];
	if (!check_block())
		for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
			block_board[kind][y][x] = temp[y][x];
}

void Play::update()
{
	if (!check_block())
	{
		new_block();
		preview_block();
	}
	static float prev = clock.getElapsedTime().asSeconds();
	if (clock.getElapsedTime().asSeconds() - prev >= 0.5)
	{
		prev = clock.getElapsedTime().asSeconds();
		go_down();
	}
	clear_lines();
	static float prev1 = clock1.getElapsedTime().asSeconds();
	if (clock.getElapsedTime().asSeconds() - prev1 >= 0.4)
	{
		prev1 = clock1.getElapsedTime().asSeconds();
		if (line_check == true)
		{
			clear_lines_d();
			line_check = false;
		}
	}
	if (game_over_check)//ask about this to me..this is newly added to address a pretty big bug
	{
		int temp = 4;//this part is new in slight change 2(from here to 'there' down)
		if (kind == 0)
			temp = 3;//because this block(----) starts from cx=3 and other block from cx=4
		for (int yy = 0; yy < 4; yy++)for (int xx = 0; xx < 4; xx++)
		{//this loop updates the value of world for the block that causes gameover,that final block is also displayed by this function
			if (block_board[kind][yy][xx])
			{
				world[yy][xx + temp] = kind + 1;//we can write just 1 here..next+1 is not necesary..i did it to test for some bug
			}
			//there
		}

		

	}
}

void Play::clear_lines()
{
	int var;//this variable is to store the row number that are cleared to this array check_line[] )

	int to = h_cnt - 1;
	//from bottom line to top line...
	for (int from = h_cnt - 1; from >= 0; from--)
	{
		int cnt = 0;
		for (int x = 0; x < w_cnt; x++)
			if (world[from][x])cnt++;

		if (cnt < w_cnt)
		{
			if (to != from)
				line_check = true;
			for (int x = 0; x < w_cnt; x++)
			{
				world_temp[to][x] = world[from][x];
			}
			to--;
		}
	}
}
/*
	for (int to = h_cnt - 1; to >= 0; to--) //removes block if needed
	{
		var = to;
		int cnt = 0;
		for (int x = 0; x < w_cnt; x++)
			if (world[to][x])
				cnt++;
		if (cnt == w_cnt)
		{
			for (int x = 0; x < w_cnt; x++)
			{
				world[to][x] = 0;
				check_line[var] = 1;//since multiple row can be cleared at once,,this takes value 1 if row is to vleared and 0 otherwise
				//goes for all 20 rows,this variable is again use below in animation drawing function..it reads value for which row to clear from this variable
				stop_animation = false;
			}
		}
		else
			check_line[var] = 0;
	}

}
*/
void Play::Render(sf::RenderTarget* target)
{
	for (int a = 0; a < w_cnt; a++)for (int b = 0; b < h_cnt; b++)
	{
		this->grid.setPosition(cell_size * static_cast<float> (a), cell_size * static_cast<float> (b));
		this->grid.setFillColor(sf::Color(50, 50, 100, 250));
		target->draw(this->grid);
	}
	target->draw(this->preview_border);
	target->draw(this->preview_border1);
}


void Play::draw_block(sf::RenderTarget* target)
{
	this->cell.setTextureRect(sf::IntRect(textureSize.x * kind, textureSize.y * 0, textureSize.x, textureSize.y));
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if(block_board[kind][y][x])
			{
				this->cell.setPosition(sf::Vector2f((cx + x) * cell_size, (cy + y) * cell_size));//cy increase by 1 every 0.5 sec to drop block continuiosly
				target->draw(this->cell);
			}
		}
	}
}


void Play::draw_world(sf::RenderTarget* target)
{
	for (int y = 0; y < h_cnt; y++)for (int x = 0; x < w_cnt; x++)
		if (world[y][x])
		{
			cell.setTextureRect(sf::IntRect(textureSize.x * (world[y][x] - 1), textureSize.y * 0, textureSize.x, textureSize.y));
			cell.setPosition(sf::Vector2f(x * cell_size, y * cell_size));
			target->draw(cell);
		}
}


bool Play::go_down()
{
	cy++;	
	if (!check_block())
	{
		cy--;
		for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
			if (block_board[kind][y][x])
			{
				//if (!game_over_check)
				world[cy + y][cx + x] = kind + 1;//+1 to avoid 0 because kind starts from zero...ask me if not clear
				//solved!! now gameover takes world_temp value...
			}
		return false;
	}
	return true;
};

bool Play::shadow_check()
{
	sx = cx;
	for (int y = 0; y < 4; y++)for (int x = 0; x < 4; x++)
		{
			if (block_board[kind][y][x])
			{
				if (y + sy >= h_cnt)
				{
					sy--;
					return false;
				}
				if (world[sy + y][cx + x])
				{
					sy--;
					return false;
				}
			}
		}
	return true;
}

void Play::draw_shadow(sf::RenderTarget* target)
{
	shadow.setFillColor(sf::Color(100, 100, 100, 255));
	while (shadow_check())
		sy++;
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{	
			if (block_board[kind][y][x])
			{
				shadow.setPosition(sf::Vector2f((sx + x) * cell_size, (sy + y) * cell_size));
				target->draw(shadow);
			}
		}
	sy = cy;//this needs to be explained by me...ask me!!
}

void Play::clear_anm(sf::RenderTarget* target)
{
	for (int j = 0; j < 20; j++)
		if (check_line[j] == 1)
			for (int x = 0; x < w_cnt; x++)
			{
				this->explode.setTextureRect(sf::IntRect(textureSize.x * 9, 0, textureSize.x, textureSize.y));
				this->explode.setPosition(sf::Vector2f(x * cell_size + 7.5, j * cell_size + 7.5));
				target->draw(explode);
			}
}



void Play::draw_Pblock(sf::RenderTarget* target)
{
	this->cell.setTextureRect(sf::IntRect(textureSize.x * next, textureSize.y * 0, textureSize.x, textureSize.y));

	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{
			if (block[next][y][x])
			{
				cell.setPosition(sf::Vector2f((px + x) * (cell_size), (py + y) * (cell_size)));
				target->draw(cell);
			}
		}
}
void Play::draw_dead_block(sf::RenderTarget* target)
{
	for (int b = 0; b < h_cnt; b++) for (int a = 0; a < w_cnt; a++)//finally,the dead block
	{
		if (world[b][a])
		{
			dead_block.setTextureRect(sf::IntRect(textureSize.x * 8, 0, textureSize.x, textureSize.y));
			dead_block.setPosition(cell_size * static_cast<float>(a), cell_size * static_cast<float>(b));

			target->draw(dead_block);
		}
	}
}
void Play::Checkevent(sf::Event e)
{
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Left)
			{
				cx--;
				if (check_block() == false) cx++;
			}
			else if (e.key.code == sf::Keyboard::Right)
			{
				cx++;
				if (check_block() == false) cx--;
			}
			else if (e.key.code == sf::Keyboard::Down)
			{
				go_down();
			}
			else if (e.key.code == sf::Keyboard::Space)
			{
				//clear_lines_d();// this is necessary, you can ask me
				while (go_down() == true);
			}
			else if (e.key.code == sf::Keyboard::Up)
				rotate();
			/*
			else if (e.key.code == sf::Keyboard::N)//new game shortcut for now
			{

				for (int y = 0; y < h_cnt; y++)for (int x = 0; x < w_cnt; x++)
				{
					world[y][x] = 0;
					world_temp[y][x] = 0;//this also has to be updated because game_over takes world_temp value.
				}
				game_over_check = false;
				new_block();

				preview_block();
			}
			*/
		}
	}
