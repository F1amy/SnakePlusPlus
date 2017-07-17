#include "stdafx.h"
#include "header.h"

using namespace std;

/*
void setWindow(int Width, int Height, int WidthBuffer, int HeightBuffer) {
	_COORD coord;
	coord.X = WidthBuffer;
	coord.Y = HeightBuffer;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

void removeScrollbar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}	*/

void sleep(double milliseconds) {
	double endwait = clock() + milliseconds * (CLOCKS_PER_SEC / 1000);
	while (clock() < endwait); // {}
}

void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void clearScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

snake::snake() {
	change = true;
	difficulty = 100;
	gameOver = false;
	newDirection = STOP;
	direction = STOP;
	x = WIDTH / 2;
	y = HEIGHT / 2;
	numberOfDifficulty = 0;
	score = 0, nTail = 3;
	tailX[0] = x - 1;
	tailY[0] = y;
	tailX[1] = x - 2;
	tailY[1] = y;
	tailX[2] = x - 3;
	tailY[2] = y;
	srand((unsigned int)time(NULL));
	bool inTail = false;
	do {
		inTail = false;
		fruitX = rand() % (WIDTH - 2) + 1;
		fruitY = rand() % HEIGHT;
		for (int i = 0; i < nTail; i++) {
			if (fruitX == tailX[i] && fruitY == tailY[i]) {
				inTail = true;
			}
		}
	} while ((fruitX == x && fruitY == y || inTail == true) || gameOver == true);
}

snake::~snake() {
	delete[] tailX;
	delete[] tailY;
}

void snake::startGame() {
	setlocale(LC_ALL, "Russian");
	string input = "NONE";
	const string theme = "0123456789ABCDEF";
	int count = 0;
	/*	SetConsoleCP(1251);
		SetConsoleOutputCP(1251);	*/
	system("color 0A");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

/*	setWindow(77, 32, 77, 32);
	removeScrollbar();	*/
	system("mode con: cols=77 lines=32");

	SetConsoleTitle(L"Snake++");
	do {
		system("cls");
		cout << "\n"
			<< "          SPECIAL THANKS TO NVitanovic, THE AUTHOR OF THE TUTORIAL" << endl
			<< "\n"
			<< "               $$$$$  $   $     $   $  $ $$$$$     +       +" << endl
			<< "               $      $$  $    $ $  $ $  $        +       +" << endl
			<< "               $$$$$  $ $ $   $  $  $$   $$$$$ +++++++ +++++++" << endl
			<< "                   $  $  $$  $$$$$$ $ $  $        +       +" << endl
			<< "               $$$$$  $   $ $     $ $  $ $$$$$   +       + " << endl
			<< "\n"
			<< "                +------------Welcome-to-Snake++!------------+" << endl
			<< "                |                                           |" << endl
			<< "                |  Hello! To start, choose the difficulty.  |" << endl
			<< "                |     Please write one of the following     |" << endl
			<< "                |        numbers from the left bar.         |" << endl
			<< "                |                                           |" << endl
			<< "                | F1amy           18.06.2017           v1.0 |" << endl
			<< "                +-------------------------------------------+\n" << endl
			<< "           " << "+-Difficulty-+" << "   +------------How-to-play-------------+" << endl
			<< "           " << "| 1 | Slug   |" << "   | Move around using WASD (only eng.) |" << endl //or arrow keys
			<< "           " << "|------------|" << "   | key) or arrow keys. Try to eat all |" << endl
			<< "           " << "| 2 | Worm   |" << "   | the fruits around you. You can go  |" << endl
			<< "           " << "|------------|" << "   | through walls, appearing on the    |" << endl
			<< "           " << "| 3 | Snake  |" << "   | other side. If you try to eat      |" << endl
			<< "           " << "|------------|" << "   | yourself, you'll die. You can end  |" << endl
			<< "           " << "| 4 | Python |" << "   | the game on \"X\", pause on \"P\".     |" << endl
			<< "           " << "+------------+" << "   +------------------------------------+" << endl
			<< "\n               >> ";

		while (_kbhit()) _getch();
		getline(cin, input);

		input.erase(remove(input.begin(), input.end(), ' '), input.end());

		if (input == "1") {
			numberOfDifficulty = 1;
			difficulty = 500;
		}
		else if (input == "2") {
			numberOfDifficulty = 2;
			difficulty = 350;
		}
		else if (input == "3") {
			numberOfDifficulty = 3;
			difficulty = 100;
		}
		else if (input == "4") {
			numberOfDifficulty = 4;
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
					sleep(2500);
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				}
				else {
					cout << "\n                 " << "Error. Please write the number from 1 to 4.";
					sleep(2500);
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
				}
			}
			else {
				cout << "\n                 " << "Error. Please write the number from 1 to 4.";
				sleep(2500);
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
			}
		}
	} while (numberOfDifficulty < 1 || numberOfDifficulty > 4);
	hideCursor();
	gameLoop();
}
void snake::gameLoop() {
	while (!gameOver) {
		input();
		logic();
		draw();
		sleep(difficulty);
	}
	//sleep(2500);
	string msgScore = "\tCongratulations! You have finished the game.\nStats: Your score is " + to_string(score) + ", the size of your tail is "
		+ to_string(nTail) + ", you ate " + to_string(nTail - 3) + " fruits.";
	wstring stemp = wstring(msgScore.begin(), msgScore.end());
	LPCWSTR message = stemp.c_str();
	MessageBox(NULL, message, L"Game over!", MB_OK);
	/*	while (_kbhit()) _getch();
		_getch();	*/
}

void snake::draw() {
	if (change) {
		/*	system("mode con cols=77 lines=32");	*/
		/*	system("cls");	*/
		clearScreen();
		cout << endl;
		for (int i = 0; i < WIDTH; i++) {
			if (i == 0)
				cout << "   ";
			if (i == 0 || i == WIDTH - 1)
				cout << "+";
			else
				cout << "-";
		}
		cout << endl;
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0)
					cout << "   ";
				if (j == 0 || j == WIDTH - 1) {
					cout << "|";
					//static_cast <char> (symbol_dec_code)
				}
				else if (i == y && j == x) {
					if (gameOver)
						cout << "X";
					else
						cout << "O";
				}
				else if (i == fruitY && j == fruitX) {
					cout << "F";
				}
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							if (gameOver)
								cout << "x";
							else
								cout << "o";
							print = true;
						}
					}
					if (!print) {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
		for (int i = 0; i < WIDTH; i++) {
			if (i == 0)
				cout << "   ";
			if (i == 0 || i == WIDTH - 1)
				cout << "+";
			else
				cout << "-";
		}
		cout << "\n\n";
		cout << "       Score: ";
		cout.fill(' ');
		cout.width(10);
		cout << left << score;
		cout << "   ";
		cout.fill(' ');
		cout.width(22);
		if (!gameOver) {
			if (direction == STOP) {
				cout << left << "Press WASD to continue";
			}
			else
				cout << left << "        Snake++";
		}
		else
			cout << left << "       Game over!";
		cout << "               ";
		cout.fill(' ');
		cout.width(6);
		switch (numberOfDifficulty) {
		case 1:
			cout << right << "Slug";
			break;
		case 2:
			cout << right << "Worm";
			break;
		case 3:
			cout << right << "Snake";
			break;
		case 4:
			cout << right << "Python";
			break;
		default:
			break;
		}
		change = false;
	}
}

void snake::input() {
	setlocale(LC_ALL, "Russian");
	int symbCode = 0;
	if (_kbhit()) {
		symbCode = _getch();
		//cout << symbCode << endl << toupper(symbCode);
		switch (toupper(symbCode)) {
		case 'W':
			newDirection = UP;
			break;
		case 'A':
			newDirection = LEFT;
			break;
		case 'S':
			newDirection = DOWN;
			break;
		case 'D':
			newDirection = RIGHT;
			break;
		case 'P':
			newDirection = STOP;
			break;
		case 'X':
			gameOver = true;
			change = true;
			break;
		case 192:
			symbCode = _getch();
			switch (symbCode) {
			case 72:
				newDirection = UP;
				break;
			case 75:
				newDirection = LEFT;
				break;
			case 80:
				newDirection = DOWN;
				break;
			case 77:
				newDirection = RIGHT;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	while (_kbhit()) _getch();
}

void snake::logic() {
	switch (newDirection) {
	case UP:
		if (!((tailX[0] == x) && (tailY[0] == (y - 1)))) {
			if (y >= 0) {
				if (!((tailX[0] == x) && (tailY[0] == (HEIGHT - 1)))) {
					direction = newDirection;
				}
			}
		}
		break;
	case LEFT:
		if (!((tailX[0] == (WIDTH - 2)) && (tailY[0] == y))) {
			if (x > 0) {
				if (!((tailX[0] == (x - 1)) && (tailY[0] == y))) {
					direction = newDirection;
				}
			}
		}
		break;
	case DOWN:
		if (!((tailX[0] == x) && (tailY[0] == (y + 1)))) {
			if (y < HEIGHT) {
				if (!((tailX[0] == x) && (tailY[0] == (0)))) {
					direction = newDirection;
				}
			}
		}
		break;
	case RIGHT:
		if (!((tailX[0] == (x + 1)) && (tailY[0] == y))) {
			if (x <= WIDTH - 2) {
				if (!((tailX[0] == (1)) && (tailY[0] == y))) {
					direction = newDirection;
				}
			}
		}
		break;
	case STOP:
		direction = newDirection;
		break;
	default:
		break;
	}
	if (direction != STOP) {
		int prevX = x;
		int prevY = y;
		for (int i = 0; i < nTail; i++) {
			swap(tailX[i], prevX);
			swap(tailY[i], prevY);
		}
	}
	switch (direction) {
	case UP:
		y--;
		change = true;
		break;

	case LEFT:
		x--;
		change = true;
		break;

	case DOWN:
		y++;
		change = true;
		break;

	case RIGHT:
		x++;
		change = true;
		break;

	case STOP:
		change = true;
		break;

	default:
		break;
	}

	/*	if (x >= WIDTH - 1 || x <= 0 || y >= HEIGHT || y < 0)
			gameOver = true;	*/

	if (y < 0)
		y = HEIGHT - 1;
	else if (x <= 0)
		x = WIDTH - 2;
	else if (y >= HEIGHT)
		y = 0;
	else if (x > WIDTH - 2)
		x = 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
			change = true;
		}
	}
	bool inTail = false;
	srand((unsigned int)time(NULL));
	if (x == fruitX && y == fruitY) {
		do {
			inTail = false;
			fruitX = rand() % (WIDTH - 2) + 1;
			fruitY = rand() % HEIGHT;
			for (int i = 0; i < nTail; i++) {
				if (fruitX == tailX[i] && fruitY == tailY[i]) {
					inTail = true;
				}
			}
		} while ((fruitX == x && fruitY == y || inTail == true) || gameOver == true);
		score += 10;
		nTail++;
	}
}