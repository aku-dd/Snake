#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include<Windows.h>



using namespace std;

class Snake 
{
public:
	int snakex, snakey, foodx, foody, food = 0;
	
	enum Surf
	{
		stop = 0, Left, Right, up, down
	};
	Surf dir;

	int tail = 0;
	int tailx[200] = { 0 };
	int taily[200] = { 0 };
	const int width = 20;
	const int height = 20;
	bool gameover;
	void Start();
	void set_input();
	void Grid();
	void build();
};

void Snake::Start() // начало игры
{
	gameover = false;
	dir = stop;
	tailx[0] = 0;
	taily[0] = 0;
	snakex = width / 3;
	snakey = height / 2;
	foodx = rand() % width;
	foody = rand() % height;
}

void Snake::set_input() // управление змейкой
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'q':
			gameover = true;
			break;
		}
	}
}

void Snake::Grid() // игровое поле
{
	system("cls");
	for (int i = 0; i < width + 1; i++)
	{
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "|";
			}
			if (i == snakex && j == snakey) // голова змейки
				cout << "@";
			else if (i == foodx && j == foody)
				cout << "*";
			else
			{
				bool add_tail = false;
				for (int h = 0; h < tail; h++)
				{
					if (tailx[h] == i && taily[h] == j)
					{
						cout << "#";
						add_tail = true;
					}
				}
				if (!add_tail)
				{
					cout << " ";
				}
			}
			if (j == width - 1)
				cout << "|";
		}
		cout << endl;
	}
	for (int i = 0; i < width / 2 + 1; i++)
	{
		cout << "_";
	}
	cout << endl;
	cout << "Кол-во очков: " << food;
}

void Snake::build() // процесс увеличения змейки
{
	int prevx = tailx[0];
	int prevy = taily[0];
	tailx[0] = snakex;
	taily[0] = snakey;
	int prevNx, prevNy;
	for (int i = 1; i < tail; i++)
	{
		prevNx = tailx[i];
		prevNy = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prevNx;
		prevy = prevNy;
	}
	switch (dir)
	{
	case Left:
		snakey--;
		break;
	case Right:
		snakey++;
		break;
	case up:
		snakex--;
		break;
	case down:
		snakex++;
		break;
	default:
		break;
	}

	if (snakex >= width) snakex = 0;
	else if (snakex < 0) snakex = width - 1;
	// дописать значения для snakey
	if (snakey >= height) snakey = 0;
	else if (snakey < 0) snakey = height - 1;
	// дописать условие, если голова входит в хвост!
	for (int i = 0; i < tail; i++)
	{
		if (tailx[i] == snakex && taily[i] == snakey)
		{
			gameover = true;
		}

	}
	if (snakex == foodx && snakey == foody)
	{
		food += 1;
		foodx = rand() % width;
		foody = rand() % height;
		tail++;
	}
}

int main() // основная функция игры
{
	setlocale(LC_ALL, "rus");
	
	Snake s;
	s.Start();
	while (!s.gameover)
	{
		//Start;
		s.Grid();
		s.set_input();
		s.build();
		Sleep(200); // скорость змейики, чем больше тем медленнее она двигается
	}
	return 0;
}

