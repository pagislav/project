#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool gameOver; 
const int a = 30, b = 30; // a - visota, b - shirina
int ycor = a / 2, xcor = b / 2, k = 0,score = 0;
vector<vector<char>>vec(a,vector<char>(b));
vector<int> meta_y; // TODO: допилить хвост
vector<int> meta_x;
vector<char> hnap;
char nap;

void mapp() // работает без нареканий
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

void random_fruit() // работает вообще идеально
{
	if (k == 0)
	{
		srand(time(0));
		vec[1 + rand() % (a - 2)][1 + rand() % (b - 2)] = 'F';
		k++;
	}
	
}

void head_move() // голова движется нормально
{
	cin >> nap;
	if (nap == 'w' || nap == 'W' )
	{
		if (vec[ycor - 1][xcor] == '#')
		{
			swap(vec[ycor][xcor], vec[a - 2][xcor]);
			ycor = a - 2;
		}
		else if (vec[ycor - 1][xcor] == 'F')
		{
			swap(vec[ycor][xcor], vec[ycor - 1][xcor]); // хвост отпадает
			vec[ycor][xcor] = 's';
			hnap.push_back(nap);
			meta_y.push_back(ycor);
			meta_x.push_back(xcor);
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
	else if (nap == 's' || nap == 'S' )
	{
		if (vec[ycor +1][xcor] == '#')
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
			vec[ycor + 1][xcor] = 'O'; // хвост отпадает
			vec[ycor][xcor] = 's';
			hnap.push_back(nap);
			meta_y.push_back(ycor);
			meta_x.push_back(xcor);
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
	else if (nap == 'a' || nap == 'A' )
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
			vec[ycor][xcor - 1] = 'O'; // хвост отпадает
			vec[ycor][xcor] = 's';
			hnap.push_back(nap);
			meta_y.push_back(ycor);
			meta_x.push_back(xcor);
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
	else if (nap == 'd' || nap == 'D' )
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
			vec[ycor][xcor + 1] = 'O'; // хвост отпадает
			vec[ycor][xcor] = 's';
			hnap.push_back(nap);
			meta_y.push_back(ycor);
			meta_x.push_back(xcor);
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

void hvost_move() // строки длиннее,чем растояние между землёй и марсом
{
	
}

void vivod() // Работает без нареканий
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

int main() // complete
{
	gameOver = false;
	mapp();
	vec[a / 2][b / 2] = 'O';
	vec[a / 2 - 1][b / 2] = 'F';
	vec[a / 2 - 2][b / 2] = 'F';
	while (!gameOver)
	{
		random_fruit();
		vivod();
		head_move();
		hvost_move();
	}
	if (gameOver == true)
	{
		system("cls");
		cout << "GAME OVER!" << endl << "YOU SCORE: " << score;
	}
	return 0;
}
