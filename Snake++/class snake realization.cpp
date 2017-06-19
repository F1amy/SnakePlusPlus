#include "stdafx.h"
#include "class snake definition.h"

using namespace std;

snake::snake(int diff) {
	change = true;
	difficulty = diff;
	gameOver = false;
	newDirection = STOP;
	direction = STOP;
	x = width / 2;
	y = height / 2;
	srand((unsigned int)time(NULL));
	fruitX = rand() % (width - 2) + 1;
	fruitY = rand() % height;
	score = 0, nTail = 3;
	tailX[0] = x - 1;
	tailY[0] = y;
	tailX[1] = x - 2;
	tailY[1] = y;
	tailX[2] = x - 3;
	tailY[2] = y;
}

snake::~snake() {
	delete[] tailX;
	delete[] tailY;
}

void snake::draw() {
	if (change) {
		system("mode con cols=77 lines=32");
		system("cls");
		cout << endl;
		for (int i = 0; i < width; i++) {
			if (i == 0)
				cout << "   ";
			if (i == 0 || i == width - 1)
				cout << "+";
			else
				cout << "-";
		}
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j == 0)
					cout << "   ";
				if (j == 0 || j == width - 1) {
					cout << "|";
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
		for (int i = 0; i < width; i++) {
			if (i == 0)
				cout << "   ";
			if (i == 0 || i == width - 1)
				cout << "+";
			else
				cout << "-";
		}
		cout << "\n\n";
		cout << "       Score: ";
		cout.fill(' ');
		cout.width(10);
		cout << left << score;
		cout << "        ";
		cout.fill(' ');
		cout.width(12);
		if (!gameOver) {
			cout << left << "   Snake++";
		}
		else
			cout << left << "  Game over!";
		cout << "                    ";
		cout.fill(' ');
		cout.width(6);
		switch (difficulty) {
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
	if (_kbhit()) {
		switch (toupper(_getch())) {
		case 87: //W
			newDirection = UP;
			break;
		case 65: //A
			newDirection = LEFT;
			break;
		case 83: //S
			newDirection = DOWN;
			break;
		case 68: //D
			newDirection = RIGHT;
			break;
		case 88: //X
			gameOver = true;
			change = true;
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
				if (!((tailX[0] == x) && (tailY[0] == (height - 1)))) {
					direction = newDirection;
				}
			}
		}
		break;
	case LEFT:
		if (!((tailX[0] == (width - 2)) && (tailY[0] == y))) {
			if (x > 0) {
				if (!((tailX[0] == (x - 1)) && (tailY[0] == y))) {
					direction = newDirection;
				}
			}
		}
		break;
	case DOWN:
		if (!((tailX[0] == x) && (tailY[0] == (y + 1)))) {
			if (y < height) {
				if (!((tailX[0] == x) && (tailY[0] == (0)))) {
					direction = newDirection;
				}
			}
		}
		break;
	case RIGHT:
		if (!((tailX[0] == (x + 1)) && (tailY[0] == y))) {
			if (x <= width - 2) {
				if (!((tailX[0] == (1)) && (tailY[0] == y))) {
					direction = newDirection;
				}
			}
		}
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
	default:
		break;
	}

	/*	if (x >= width - 1 || x <= 0 || y >= height || y < 0)
			gameOver = true;	*/

	if (y < 0)
		y = height - 1;
	else if (x <= 0)
		x = width - 2;
	else if (y >= height)
		y = 0;
	else if (x > width - 2)
		x = 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
			change = true;
		}
	}
	srand((unsigned int)time(NULL));
	if (x == fruitX && y == fruitY) {
		fruitX = rand() % (width - 2) + 1;
		fruitY = rand() % height;
		score += 10;
		nTail++;
	}
}