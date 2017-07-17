#pragma once

void sleep(double milliseconds);
void hideCursor();
void clearScreen();
/*void setWindow(int Width, int Height, int WidthBuffer, int HeightBuffer);
void removeScrollbar();	*/

class snake {
private:
	bool change;
	const int WIDTH = 71;
	const int HEIGHT = 26;
	int x, y;
	int numberOfDifficulty;
	int fruitX, fruitY;
	int score, nTail;
	int *tailX = new int[WIDTH * HEIGHT];
	int *tailY = new int[WIDTH * HEIGHT];
	int difficulty;
	bool gameOver;
	enum eDirection {
		STOP, LEFT, RIGHT,
		UP, DOWN
	};
	eDirection direction;
	eDirection newDirection;
	void draw();
	void input();
	void logic();
	void gameLoop();
public:
	void startGame();
	snake();
	~snake();
};
