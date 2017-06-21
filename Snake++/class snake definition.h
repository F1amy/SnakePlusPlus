#pragma once

class snake {
private:
	bool change;
	const int width = 71;
	const int height = 26;
	int x, y;
	int fruitX, fruitY;
	int score, nTail;
	int *tailX = new int[width * height];
	int *tailY = new int[width * height];
	int difficulty;
	enum eDirection {
		STOP,
		LEFT, RIGHT,
		UP, DOWN
	};
	eDirection direction;
	eDirection newDirection;
public:
	void hideCursor();
	void clearScreen();
	bool gameOver;
	snake(int diff = 0);
	~snake();
	void draw();
	void input();
	void logic();
};
