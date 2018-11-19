#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
// vec[ycor][xcor] - голова, vec[tail_y[i]][tail_x[i]] - итая цепочка хвоста,чем меньше и,тем меньше расстояние от головы

bool gameOver; 
const int a = 30, b = 30; // a - visota, b - shirina
int ycor = a / 2, xcor = b / 2, k = 0,score = 0;
vector<vector<char>>vec(a,vector<char>(b));
vector<int> tail_y; // TODO: научить хвост поворачивать и проходить сквозь стены
vector<int> tail_x;
vector<char> command_log;
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

void random_fruit() // работает вообще идеально, допилить появление не на 's' & 'O'
{
	if (k == 0)
	{
		srand(time(0));
		vec[1 + rand() % (a - 2)][1 + rand() % (b - 2)] = 'F';
		k++;
	}
	
}

void shake_move() // голова движется нормально,а хвост нет,но главное что он есть
{
	cin >> nap;
	command_log.push_back(nap);
	int size = command_log.size(), j = 0;
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
	
	if (tail_y.size() != 0)
	{
		for (int i = tail_y.size() - 1; i >= 0; --i)
		{
			if (command_log[size - j - 1] == 'w' || command_log[size - j - 1] == 'W')
			{
				if (vec[tail_y[i] - 1][tail_x[i]] == '#')
				{
					swap(vec[tail_y[i]][tail_x[i]], vec[a - 2][tail_x[i]]);
					tail_y[i] = a - 2;
				}
				else if (vec[tail_y[i] - 1][tail_x[i]] != 's')
				{
					if (vec[tail_y[i] - 1][tail_x[i] -1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] - 1]);
						tail_x[i]--;
					}
					else if (vec[tail_y[i] - 1][tail_x[i] + 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] + 1]);
						tail_x[i]++;
					}
					else if (vec[tail_y[i] - 1][tail_x[i]] != 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] - 1][tail_x[i]]);
						tail_y[i]--;
					}
				}
			}
			else if (command_log[size - j - 1] == 's' || command_log[size - j - 1] == 'S')
			{
				if (vec[tail_y[i] + 1][tail_x[i]] == '#')
				{
					swap(vec[tail_y[i]][tail_x[i]], vec[1][tail_x[i]]);
					tail_y[i] = 1;
				}
				else if (vec[tail_y[i] + 1][tail_x[i]] != 'O')
				{
					if (vec[tail_y[i] + 1][tail_x[i] - 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] - 1]);
						tail_x[i]--;
					}
					else if (vec[tail_y[i] + 1][tail_x[i] + 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] + 1]);
						tail_x[i]++;
					}
					else if (vec[tail_y[i] + 1][tail_x[i]] != 's')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] + 1][tail_x[i]]);
						tail_y[i]++;
					}
				}
			}
			else if (command_log[size - j - 1] == 'a' || command_log[size - j - 1] == 'A')
			{
				if (vec[tail_y[i]][tail_x[i] - 1] == '#')
				{
					swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][b - 2]);
					tail_x[i] = b - 2;
				}
				else if ( vec[tail_y[i]][tail_x[i] - 1] != 's')
				{
					if (vec[tail_y[i] - 1][tail_x[i] - 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] - 1][tail_x[i]]);
						tail_y[i]--;
					}
					else if (vec[tail_y[i] + 1][tail_x[i] - 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] + 1][tail_x[i]]);
						tail_y[i]++;
					}
					else if (vec[tail_y[i]][tail_x[i] - 1] != 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] - 1]);
						tail_x[i]--;
					}
				}
			}
			else if ((command_log[size - j - 1] == 'd' || command_log[size - j - 1] == 'D'))
			{
				if (vec[tail_y[i]][tail_x[i] + 1] == '#')
				{
					swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][1]);
					tail_x[i] = 1;
				}
				else if (vec[tail_y[i]][tail_x[i] + 1] != 'O')
				{
					if (vec[tail_y[i] - 1][tail_x[i] + 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] - 1][tail_x[i]]);
						tail_y[i]--;
					}
					else if (vec[tail_y[i] + 1][tail_x[i] + 1] == 'O')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i] + 1][tail_x[i]]);
						tail_y[i]++;
					}
					else if (vec[tail_y[i]][tail_x[i] + 1] != 's')
					{
						swap(vec[tail_y[i]][tail_x[i]], vec[tail_y[i]][tail_x[i] + 1]);
						tail_x[i]++;
					}
				}
			}
		}
		j++;
	}
	
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
	while (!gameOver)
	{
		random_fruit();
		vivod();
		shake_move();
	}
	if (gameOver == true)
	{
		system("cls");
		cout << "GAME OVER!" << endl << "YOU SCORE: " << score;
	}
	return 0;
}
