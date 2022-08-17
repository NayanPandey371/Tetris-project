#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<sstream>
#include<string>
#include<fstream>
#include "Play.h"


class store_data
{
private:
	int count = 0,temp=0,to_prevent_file_from_being_written_repeadtly=0; //final_score, data[5], temp, for_sort,
	int arr[6]={0};
	Text inst[20];
	Text scores[6];
	string instruct;
	fstream file;
	fstream file1;
	Font font3;
public:
	int score_check;
	store_data();
	void score_update();
	void instructions();
	void display_instructions(sf::RenderTarget* target);
	void display_highscores(sf::RenderTarget* target);
	
};


