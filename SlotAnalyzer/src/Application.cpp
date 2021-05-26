#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>


class SlotMachine {
private:
	int rows = 3;
	int cols = 5;

	std::vector<std::vector<int>> fruits;

	//how didnt i think of this the first time! coordinate-based definition of each payline
	std::vector<std::vector<std::pair<int, int>>> pattern{
		{{0,0}, {0,1}, {0,2}, {0,3}, {0,4}},
		{{1,0}, {1,1}, {1,2}, {1,3}, {1,4}},
		{{2,0}, {2,1}, {2,2}, {2,3}, {2,4}},
		{{0,0}, {1,1}, {2,2}, {1,3}, {0,4}},
		{{2,0}, {1,1}, {0,2}, {1,3}, {2,4}},
		{{1,0}, {2,1}, {1,2}, {2,3}, {1,4}},
	};

	//score 2d vec 
	std::vector<std::vector<int>> score = {
		{0,5,10,20,30},			//0
		{0,35,40,50,60},		//1
		{0,0,70,80,90},			//2
		{0,0,100,110,120},		//3
		{0,0,130,140,150},		//4
		{0,0,0,170,180},		//5
	};

	//simple fruitnames array
	const std::vector<std::string> fruitnames{ 
	"cherry",
	"orange",
	"lemon",
	"plum",
	"watermelon",
	"grape"
	};

public:

	//generate random figures
	void Generate() {
		fruits.clear();
		fruits.resize(cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				fruits[i].push_back(rand() % 5);
			}
		}
	}
	//print playfield
	void PrintMatrix() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << fruits[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}


	//evaluate score
	std::vector<std::pair<int, int>> Evaluate() {
		std::vector<int> lines;
		std::vector<std::pair<int, int>> fruitline(pattern.size());

		int lineLength = 1;
		int fruitType;
		std::vector<std::pair<int,int>> longestline(pattern.size());
		for (int i = 0; i < pattern.size() - 1; i++) {
			lineLength = 1;
			for (int j = 0; j < pattern[i].size() - 1; j++) {

				if (fruits[pattern[i][j].first][pattern[i][j].second] == fruits[pattern[i][j + 1].first][pattern[i][j + 1].second]) {
					lineLength++;
					fruitType = fruits[pattern[i][j].first][pattern[i][j].second];
					fruitline[i] = std::make_pair(fruitType, lineLength-1);
				}

				else break;
			}
		}
		return fruitline;
		}

	void PrintScore() {
		std::vector<std::pair<int, int>> fruitline = Evaluate();
		int totalscore = 0;


		for (int i = 0; i < fruitline.size(); i++) {
			/*std::cout << fruitline[i].first;
			std::cout << fruitline[i].second << std::endl;*/

			int currentPayline = score[fruitline[i].first][fruitline[i].second];

			if (currentPayline != 0) {
				totalscore += currentPayline;
				std::cout << "winning payline: " << i + 1 << std::endl;
				std::cout << "figure: " << fruitnames[fruitline[i].first] << std::endl;
				std::cout << "Winning points: " << currentPayline << std::endl;
				std::cout << "Consecutive Figures: " << fruitline[i].second + 1 << std::endl;

			}
		}

		if (totalscore == 0) {
			std::cout << "Better luck next time!" << std::endl;
		}
		else std::cout << "Total score: " << totalscore << std::endl;
	}


};


int main() {

	bool closewindow = false;
	

	std::cout << std::endl << "----------------------------" << std::endl;
	std::cout << std::endl << "     Slot Machine   " << std::endl;
	std::cout << std::endl << "		type START to begin " << std::endl;
	std::cout << std::endl << "----------------------------" << std::endl;
	std::string input;
	std::cin >> input;

	if (input == "START") {

		srand(time(0));
		SlotMachine* slotmachine = new SlotMachine;

		while (!closewindow) {
			std::cout << std::endl << "		NEXT - to pull the lever and play  " << std::endl;
			std::cout << std::endl << "		EXIT - exit game  " << std::endl;

			int option = 0;

			std::cin >> input;
			std::cout << "\n" << std::endl;
			if (input == "NEXT") option = 1 ;
			else if (input == "EXIT") option = 2;
			else if (input == "START") std::cout << "Game aleready started!" << std::endl;
			else std::cout << "Invalid Input!" << std::endl;

			switch (option)
			{
			case 1:
				system("cls");
				slotmachine->Generate();
				slotmachine->PrintMatrix();
				slotmachine->PrintScore();
				break;
			case 2:
				closewindow = true;
				system("cls");
				break;

			default:
				system("cls");
				break;
			}
		};
		delete slotmachine;
	}
	else {
		std::cout << "Invalid Input... Stopping." << std::endl;
		system("pause");
	}



	return 0;
}