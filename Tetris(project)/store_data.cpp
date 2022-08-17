#include "store_data.h"

void store_data::instructions()
{

	if (!font3.loadFromFile("texture/8bitlimr.ttf"))
		throw("Could not load font!");
	//Text inst[20];
	//string instruct;
	//fstream file;
	int i = 0;
	count = 0;
	file.open("Instructions.txt");
	if (!file)
	{
		//cout << "couldnot open file";
		exit(1);
	}
	while (getline(file, instruct))
	{
		inst[i].setFont(font3);
		inst[i].setCharacterSize(14);
		inst[i].setString(instruct);
		inst[i].setPosition(720 * 0.26, 800 * (0.34 + i * 0.02));
		inst[i].setFillColor(Color::Blue);
		//cout << instruct << endl;
		i++;
		count++;
	}
	file.close();
	if (!file1)//to open file if it doesn't exist
	{
		
		file1.open("score.txt",  ios::out |ios::binary );
		if (!file1)
		{
			exit(1);
			cout << "could't open file";
		}
		file1.close();
	}


	file1.open("score.txt", ios::in | ios::binary);
	

		for (int i = 0; i < 6; i++)
		{
			file1.read(reinterpret_cast<char*>(arr), sizeof(arr[i]));
			//cout << arr[i]<<endl;
		}

	file1.close();
	
	
	for (int i = 0; i < 5; i++)
	{
		scores[i].setFont(font3);
		scores[i].setCharacterSize(24);
		scores[i].setStyle(Text::Bold);
		scores[i].setPosition(720 * 0.45, 800 * (0.37 + i * 0.05));
		scores[i].setFillColor(Color::Blue);
	}
	scores[5].setFont(font3);
	scores[5].setCharacterSize(16);
	scores[5].setStyle(Text::Bold);
	scores[5].setPosition(720 * 0.40, 800 * (0.37 + 5 * 0.05));
	scores[5].setFillColor(Color::Blue);
	scores[5].setString("ecs to return...");
}

store_data::store_data()
{
	this->instructions();
}

void store_data::display_instructions(sf::RenderTarget* target)
{
	for (int i = 0; i < count; i++)
	target->draw(this->inst[i]);
}
void store_data::score_update()
{
	if (!(to_prevent_file_from_being_written_repeadtly == this->score_check))
	{
		to_prevent_file_from_being_written_repeadtly = this->score_check;

		arr[5] = this->score_check;//here this new score value is retured when game is over .now this is just written in the place of 6 th array so
		//below functions automatically sort them in descending order...and since 6 th array element in not displayed there isn't much of a problem
		
		file1.open("score.txt", ios::in | ios::binary);
		for (int i = 0; i < 6; i++)
		{
			file1.read(reinterpret_cast<char*>(arr), sizeof(arr[i]));
		}
		file1.close();
		


		for (int i = 0; i < 6; i++)
		{
			for (int j = i + 1; j < 6; j++)
			{
				if (arr[i] < arr[j])
				{
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
			//cout << arr[i] << endl;

		}
		
		file1.open("score.txt",ios::out |ios::app| ios::binary);
		for (int i = 0; i < 6; i++)
		{
			//i don't knwo if this is not how you wrtie on arry but this file is just writing one value...other values are not saved
			file1.write(reinterpret_cast<char*>(arr),sizeof(arr[i]));
			//cout << arr[i] << endl;

		}
		file1.close();

	}
}
void store_data::display_highscores(sf::RenderTarget* target)
{
	
	for (int i = 0; i < 5; i++)
	{
		scores[i].setString("" + to_string(i + 1) + "." + to_string(arr[i]));
		target->draw(this->scores[i]);
	}

	
	target->draw(this->scores[5]);

}