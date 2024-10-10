#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;
void Shift_Right(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--)
		arr[i + 1] = arr[i];
}
enum Direction { Top = 1, Down, Right, Left};
struct Map { int widht, height, fruitX, fruitY; };
struct Snake { int headX, headY, tail_N; tail_X[50], tail_Y[50], char Dir; };
struct player { int score; bool lose; };
Map Map1; Snake snake1; player player1;
void Generate_fruit() {
	srand(time(NULL));
	Map1.fruitX = rand() % (Map1.widht - 2) + 1;// 1 to 38
	Map1.fruitY = rand() % (Map1.height - 2) + 1;// 1 to 18

}
void setup() {
	Map1.widht = 40;
	Map1.height = 20;
	Generate_fruit();
	//--------------
	snake1.headX = Map1.widht / 2;
	snake1.headY = Map1.height / 2;
	snake1.tail_N = 0;
	//--------------
	player1.score = 0;
	player1.lose = false;

}
void Draw() {
	system("cls");
	for (int i = 0; i < Map1.height; i++) {
		for (int j = 0; j < Map1.widht; j++) {
			if (i == 0 || i = Map1.height - 1) cout << "*";
			else if (j == 0 || j == Map1.widht - 1) cout << "*";
			else if (i == snake1.headY && j == snake1.headX) cout << "O";
			else if (i == Map1.fruitY && j == Map1.fruitX) cout << "$";
			else {
				bool printed = false;
				for (int z = 0; z < snake1.tail_N; z++) {
					if (snake1.tail_X[z] == j && snake1.tail_Y[z] == i) {
						cout << "o";
						printed = true;
						break;
					}
				}
				if (!printed) cout << " ";
			}
		}
		cout << endl;
	}
	cout << "Player Score : " << player1.score << endl;
}
void Input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case 'w': snake1.Dir = Top; break;
		case 's': snake1.Dir = Down; break;
		case 'd': snake1.Dir = Right; break;
		case 'a': snake1.Dir = Left; break;
		case 'x': exit(0);
		default:
			break;
		}
	}
}
void Move() {
	Shift_Right(snake1.tail_X, 50);
	Shift_Right(snake1.tail_Y, 50);
	snake1.tail_X[0] = snake1.headX;
	snake1.tail_Y[0] = snake1.headY;
	switch (snake1.Dir)
	{
	case Top: snake1.headY--; break;
	case Down: snake1.headY++; break;
	case Right:snake1.headX++; break;
	case Left: snake1.headX--; break;

	}
	if (snake1.headY >= Map1.height || snake1.headY <= 0 || snake1.headX >= Map1.widht || snake1.headX <= 0)
		player1.lose = true;
	if (snake1.headX == Map1.fruitX && snake1.headY == Map1.fruitY) {
		Generate_fruit();
		player1.score += 1;
		snake1.tail_N++;
	}
}
int main() {
	setup();
	while (!player1.lose)
	{
		Draw();
		Input();
		Move();
		Sleep(50);
	}
	system("pause");
	return 0;
}