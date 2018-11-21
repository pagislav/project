#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

using namespace std;

bool gameOver;
const int a = 30, b = 30; // a - visota, b - shirina
int ycor = a / 2, xcor = b / 2, k = 0, score = 0; // координаты головы по игреку и по иксу, к - это костыль,для появление фрукта, очки
vector<vector<char>>vec(a, vector<char>(b)); // карта
vector<int> tail_y; // координаты блоков хвоста по игреку
vector<int> tail_x; // координаты блоков хвоста по иксу
deque<int>tail_cor_x; // лог координат головы по иксу (нужен для того,чтобы хвост повторял движения головы)
deque<int>tail_cor_y; // лог координат головы по игреку
char nap;

void mapp() // создание "карты"
{
	for (int i = 0; i < b; ++i)
	{
		vec[0][i] = '#';
	}
	for (int i = 1; i < a - 1; ++i)
	{
		for (int j = 0; j < b; ++j)
		{
			if (j == 0 || j == b - 1)
			{
				vec[i][j] = '#';
			}
			else
			{
				vec[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i < b; ++i)
	{
		vec[a - 1][i] = '#';
	}
}

void random_fruit() // генерация еды для "змейки"
{
	srand(time(0));
	int first = 1 + rand() % (a - 2), second = 1 + rand() % (b - 2);
	while (true)
	{
		if (k == 0 && (vec[first][second] != 's' || vec[first][second] != 'O'))
		{
			vec[first][second] = 'F';
			k++;
			break;
		}
	}
	

}

void shake_move() // движение головы
{
	cin >> nap;
	tail_cor_x.push_back(xcor);
	tail_cor_y.push_back(ycor);
	if (nap == 'w' || nap == 'W')
	{
		if (vec[ycor - 1][xcor] == '#')
		{
			swap(vec[ycor][xcor], vec[a - 2][xcor]);
			ycor = a - 2;
		}
		else if (vec[ycor - 1][xcor] == 'F')
		{
			swap(vec[ycor][xcor], vec[ycor - 1][xcor]); 
			vec[ycor][xcor] = 's';
			tail_y.push_back(ycor);
			tail_x.push_back(xcor);
			--ycor;
			score++;
			k--;
		}
		else if (vec[ycor - 1][xcor] == 's')
		{
			gameOver = true;
		}
		else
		{
			swap(vec[ycor][xcor], vec[ycor - 1][xcor]);
			--ycor;
		}
	}
	else if (nap == 's' || nap == 'S')
	{
		if (vec[ycor + 1][xcor] == '#')
		{
			swap(vec[ycor][xcor], vec[1][xcor]);
			ycor = 1;
		}
		else if (vec[ycor + 1][xcor] == 's')
		{
			gameOver = true;
		}
		else if (vec[ycor + 1][xcor] == 'F')
		{
			vec[ycor + 1][xcor] = 'O'; 
			vec[ycor][xcor] = 's';
			tail_y.push_back(ycor);
			tail_x.push_back(xcor);
			++ycor;
			++score;
			k--;
		}
		else
		{
			swap(vec[ycor][xcor], vec[ycor + 1][xcor]);
			++ycor;
		}
	}
	else if (nap == 'a' || nap == 'A')
	{
		if (vec[ycor][xcor - 1] == '#')
		{
			swap(vec[ycor][xcor], vec[ycor][b - 2]);
			xcor = b - 2;
		}
		else if (vec[ycor][xcor - 1] == 's')
		{
			gameOver = true;
		}
		else if (vec[ycor][xcor - 1] == 'F')
		{
			vec[ycor][xcor - 1] = 'O'; 
			vec[ycor][xcor] = 's';
			tail_y.push_back(ycor);
			tail_x.push_back(xcor);
			--xcor;
			score++;
			k--;
		}
		else
		{
			swap(vec[ycor][xcor], vec[ycor][xcor - 1]);
			--xcor;
		}

	}
	else if (nap == 'd' || nap == 'D')
	{
		if (vec[ycor][xcor + 1] == '#')
		{
			swap(vec[ycor][xcor], vec[ycor][1]);
			xcor = 1;
		}
		else if (vec[ycor][xcor + 1] == 's')
		{
			gameOver = true;
		}
		else if (vec[ycor][xcor + 1] == 'F')
		{
			vec[ycor][xcor + 1] = 'O'; 
			vec[ycor][xcor] = 's';
			tail_y.push_back(ycor);
			tail_x.push_back(xcor);
			++xcor;
			score++;
			k--;
		}
		else
		{
			swap(vec[ycor][xcor], vec[ycor][xcor + 1]);
			++xcor;
		}
	}


}

void hvost_move() // движение хвоста
{
	int j = 0;
	if (tail_x.size() != 0)
	{
		for (int i = tail_x.size() - 1; i >= 0; --i)
		{
			int index = tail_cor_x.size() - 1 - j;
			swap(vec[tail_y[i]][tail_x[i]], vec[tail_cor_y[index]][tail_cor_x[index]]);
			tail_x[i] = tail_cor_x[index];
			tail_y[i] = tail_cor_y[index];
			j++;
		}
	}
}

void vivod() // вывод текущего состояния карты в консоль
{
	system("cls");
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < b; ++j)
		{
			cout << vec[i][j];
		}
		cout << endl;
	}
	cout << "SCORE:" << ' ' << score << endl;
}

int main() 
{
	gameOver = false;
	mapp();
	vec[a / 2][b / 2] = 'O';
	while (!gameOver)
	{
		random_fruit();
		vivod();
		shake_move();
		hvost_move();
		if (tail_cor_x.size() > 1000)
		{
			for (int i = 1; i <= 500; ++i)
			{
				tail_cor_x.pop_front();
				tail_cor_y.pop_front();
			}
		}
	}
	if (gameOver == true)
	{
		system("cls");
		cout << "GAME OVER!" << endl << "YOU SCORE: " << score;
	}
	return 0;
}
