// Snake++.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "class snake definition.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string input = "NONE";
	const string theme = "0123456789ABCDEF";
	int choose = 0, difficulty = 0, count = 0;
	system("mode con cols=77 lines=32");
	system("title Snake++");
	do {
		system("cls");
		cout << "\n";
		cout << "          SPECIAL THANKS TO NVitanovic, THE AUTHOR OF THE TUTORIAL" << endl;
		cout << "\n";
		cout << "               $$$$$  $   $     $   $  $ $$$$$     +       +" << endl;
		cout << "               $      $$  $    $ $  $ $  $        +       +" << endl;
		cout << "               $$$$$  $ $ $   $  $  $$   $$$$$ +++++++ +++++++" << endl;
		cout << "                   $  $  $$  $$$$$$ $ $  $        +       +" << endl;
		cout << "               $$$$$  $   $ $     $ $  $ $$$$$   +       + " << endl;
		cout << "\n";
		cout << "                +------------Welcome-to-Snake++!------------+" << endl;
		cout << "                |                                           |" << endl;
		cout << "                |  Hello! To start, choose the difficulty.  |" << endl;
		cout << "                |     Please write one of the following     |" << endl;
		cout << "                |        numbers from the left bar.         |" << endl;
		cout << "                |                                           |" << endl;
		cout << "                | F1amy           18.06.2017           v1.0 |" << endl;
		cout << "                +-------------------------------------------+\n" << endl;
		cout << "           " << "+-Difficulty-+" << "   +------------How-to-play-------------+" << endl;
		cout << "           " << "| 1 | Slug   |" << "   | Move around using WASD (on the     |" << endl;
		cout << "           " << "|------------|" << "   | English keyboard!). Try to eat all |" << endl;
		cout << "           " << "| 2 | Worm   |" << "   | the fruits around you. You can go  |" << endl;
		cout << "           " << "|------------|" << "   | through walls, appearing on the    |" << endl;
		cout << "           " << "| 3 | Snake  |" << "   | other side. If you try to eat      |" << endl;
		cout << "           " << "|------------|" << "   | yourself, you'll die. You can end  |" << endl;
		cout << "           " << "| 4 | Python |" << "   | the game by pressing \"X\".          |" << endl;
		cout << "           " << "+------------+" << "   +------------------------------------+" << endl;
		cout << "\n               >> ";

		while (_kbhit()) _getch();
		getline(cin, input);

		input.erase(remove(input.begin(), input.end(), ' '), input.end());

		if (input == "1") {
			choose = 1;
			difficulty = 500;
		}
		else if (input == "2") {
			choose = 2;
			difficulty = 350;
		}
		else if (input == "3") {
			choose = 3;
			difficulty = 100;
		}
		else if (input == "4") {
			choose = 4;
			difficulty = 10;
		}
		else {
			if (input.length() == 2) {
				transform(input.begin(), input.end(), input.begin(), ::toupper);
				count = 0;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 16; j++) {
						if (input.at(i) == theme.at(j)) {
							count++;
						}
					}
				}
				if ((count == 2) && (input.at(0) != input.at(1))) {
					system(("color " + input).c_str());
					cout << "\n                 " << "        The color theme is changed!";
					Sleep(2500);
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				}
				else {
					cout << "\n                 " << "Error. Please write the number from 1 to 4.";
					Sleep(2500);
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				}
			}
			else {
				cout << "\n                 " << "Error. Please write the number from 1 to 4.";
				Sleep(2500);
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	} while (choose < 1 || choose > 4);
	snake game(choose);

	while (!game.gameOver) {
		game.input();
		game.logic();
		game.draw();
		Sleep(difficulty);
	}
	Sleep(2500);
	while (_kbhit()) _getch();
	_getch();
	system("cls");
	return 0;
}