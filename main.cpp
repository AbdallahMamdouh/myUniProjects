#include <iostream>
#include <random>
using namespace std;
enum board_map { e = 0, o = 1, x = 2 };
int plays = 0, r, c, difficulty = 0,player;
bool choice,turn;
class tictactoe
{
public:
	board_map X[3][3] = { {e,e,e},{e,e,e},{e,e,e} };
	void play()//this function lets the player choose the mode and difficulty also it let him choose if he want to restart the game
	{
		cout << "for 1-player enter 0\nfor 2-players enter 1\n";
		cin >> player;
		if (player)
		{
			display();
			while (!end())

			{
				if (plays % 2 == 0)
				{
					r = 9999; c = 9999;
					while (!check(r, c))
					{
						cout << "player 1 please enter a valid value for r and c\n";
						cin >> r >> c;
					}
					playX(r, c);
				}
				else
				{
					r = 99999; c = 99999;
					while (!check(r, c))
					{
						cout << "player 2 please enter a valid value for r and c\n";
						cin >> r >> c;
					}
					playO(r, c);
				}
			}
		}
		else
		{
			cout << "for easy enter 0\nfor medium enter 1\nfor hard enter 2\n";
			cin >> difficulty;
			cout << "for X enter 1 and for O enter 0\n";
			cin >> choice;
			if (choice)
			{
				display();
				while (!end())
				{
					if (plays % 2 == 0)
					{
						r = 99999; c = 99999;
						while (!check(r, c))
						{
							cout << "player 1 please enter a valid value for r and c\n";
							cin >> r >> c;
						}
						playX(r, c);
					}
					else
						autoplay();
				}
			}
			else
			{
				display();
				while (!end())
				{
					if (plays % 2 == 0)
						autoplay();
					else
					{
						r = 99999; c = 99999;
						while (!check(r, c))
						{
							cout << "player 2 please enter a valid value for r and c\n";
							cin >> r >> c;
						}
						playO(r, c);
					}
				}
			}
		}
	}
	bool end()//this function end the game if someone made a winning move or number of empty positions  = 0
	{
		return (cross0() == 1 || cross1() == 1 || column0() == 1 || column1() == 1 || column2() == 1 || row0() == 1 || row1() == 1 || row2() == 1 || cross0() == 2 || cross1() == 2 || column0() == 2 || column1() == 2 || column2() == 2 || row0() == 2 || row1() == 2 || row2() == 2 || plays == 9);
	}
	void winner()//this function determine who won the game when the game ends
	{

		if (cross0() == 1 || cross1() == 1 || column0() == 1 || column1() == 1 || column2() == 1 || row0() == 1 || row1() == 1 || row2() == 1)
		{
			if (player || !choice)
				cout << "player 2 wins!\n";
			else if (!player&&choice)
				cout << "computer wins!!\n";
			return;
		}
		else if (cross0() == 2 || cross1() == 2 || column0() == 2 || column1() == 2 || column2() == 2 || row0() == 2 || row1() == 2 || row2() == 2)
		{
			if (player || choice)
				cout << "player 1 wins!\n";
			else if (!player && !choice)
				cout << "computer wins!!\n";
			return;
		}
		else if (plays == 9)
		{
			cout << "it's a draw!\n";
			return;
		}
		else
			return;
	}
	void playX(int row, int column)//plays x in a given position
	{
		X[row][column] = x;
		plays++;
		display();
	}
	void playO(int row, int column)//plays o in a given position
	{
		X[row][column] = o;
		plays++;
		display();
	}
	void playZ(board_map z, int row, int column)//plays either x or o in a given position
	{
		if (z == x)
			playX(row, column);
		else if (z == o)
			playO(row, column);
		turn = 0;
		return;
	}
	void autoplay()//AI for computer player
	{
		board_map s = (choice) ? o : x;
		board_map z = (choice) ? x : o;
		turn = 1;
		//this is hard mode no one can beat the computer you can either lose or have a draw
		if (difficulty == 2)
		{
			//*this block of code make the computer play in the square that will make it win
			if (X[0][0] == s && X[1][1] == s && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[0][0] == s && X[2][2] == s && X[1][1] == e)
				playZ(s, 1, 1);
			else if (X[1][1] == s && X[2][2] == s && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[0][2] == s && X[1][1] == s && X[2][0] == e)
				playZ(s, 2, 0);
			else if (X[0][2] == s && X[2][0] == s && X[1][1] == e)
				playZ(s, 1, 1);
			else if (X[1][1] == s && X[2][0] == s && X[0][2] == e)
				playZ(s, 0, 2);
			int i = 0;
			while (i < 3 && turn)
			{
				if (X[0][i] == s && X[1][i] == s && X[2][i] == e)
					playZ(s, 2, i);
				else if (X[0][i] == s && X[2][i] == s && X[1][i] == e)
					playZ(s, 1, i);
				else if (X[1][i] == s && X[2][i] == s && X[0][i] == e)
					playZ(s, 0, i);
				else if (X[i][0] == s && X[i][1] == s && X[i][2] == e)
					playZ(s, i, 2);
				else if (X[i][0] == s && X[i][2] == s && X[i][1] == e)
					playZ(s, i, 1);
				else if (X[i][1] == s && X[i][2] == s && X[i][0] == e)
					playZ(s, i, 0);
				i++;
			}
			//__________________________________________________________
			//this block of code make the computer play in the corners if the player plays in the middle to block some strategies
			if ((plays == 1 || plays == 2) && turn)
			{
				if (X[1][1] == z)
				{
					int a = rand() % 4;
					while (turn)
					{
						if (a == 0 && X[0][0] == e)
							playZ(s, 0, 0);
						else if (a == 1 && X[0][2] == e)
							playZ(s, 0, 2);
						else if (a == 2 && X[2][0] == e)
							playZ(s, 2, 0);
						else if (a == 3 && X[2][2] == e)
							playZ(s, 2, 2);
					}
				}
				//_____________________________________________________
				//and this one makes the computer play in the middle if its empty
				else if (X[1][1] == e)
					playZ(s, 1, 1);
				//_____________________________________________________
			}
			//this block of code blocks the player from winning by playing in the position where the player wins if he played in
			if (turn)
			{
				if (X[0][0] == z && X[1][1] == z && X[2][2] == e)
					playZ(s, 2, 2);
				else if (X[0][0] == z && X[2][2] == z && X[1][1] == e)
					playZ(s, 1, 1);
				else if (X[1][1] == z && X[2][2] == z && X[0][0] == e)
					playZ(s, 0, 0);
				else if (X[0][2] == z && X[1][1] == z && X[2][0] == e)
					playZ(s, 2, 0);
				else if (X[0][2] == z && X[2][0] == z && X[1][1] == e)
					playZ(s, 1, 1);
				else if (X[1][1] == z && X[2][0] == z && X[0][2] == e)
					playZ(s, 0, 2);
				int i = 0;
				while (i < 3 && turn)
				{

					if (X[0][i] == z && X[1][i] == z && X[2][i] == e)
						playZ(s, 2, i);
					else if (X[0][i] == z && X[2][i] == z && X[1][i] == e)
						playZ(s, 1, i);
					else if (X[1][i] == z && X[2][i] == z && X[0][i] == e)
						playZ(s, 0, i);
					else if (X[i][0] == z && X[i][1] == z && X[i][2] == e)
						playZ(s, i, 2);
					else if (X[i][0] == z && X[i][2] == z && X[i][1] == e)
						playZ(s, i, 1);
					else if (X[i][1] == z && X[i][2] == z && X[i][0] == e)
						playZ(s, i, 0);
					i++;
				}
			}
			//__________________________________________________________________________
			//this block of code blocks all the known strategies to win the game
			if (turn)
			{
			if (X[1][0] == z && X[0][1] == z && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[0][1] == z && X[1][2] == z && X[0][2] == e)
				playZ(s, 0, 2);
			else if (X[1][0] == z && X[2][1] == z && X[2][0] == e)
				playZ(s, 2, 0);
			else if (X[1][2] == z && X[2][1] == z && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[0][0] == z && X[1][2] == z && X[0][2] == e)
				playZ(s, 0, 2);
			else if (X[0][2] == z && X[1][0] == z && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[2][0] == z && X[1][2] == z && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[2][2] == z && X[1][0] == z && X[2][0] == e)
				playZ(s, 2, 2);
			else if (X[0][0] == z && X[1][1] == z && X[2][0] == e)
				playZ(s, 2, 0);
			else if (X[0][0] == z && X[1][1] == z && X[0][2] == e)
				playZ(s, 0, 2);
			else if (X[0][2] == z && X[1][1] == z && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[0][2] == z && X[1][1] == z && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[2][0] == z && X[1][1] == z && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[2][0] == z && X[1][1] == z && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[2][2] == z && X[1][1] == z && X[2][0] == e)
				playZ(s, 2, 0);
			else if (X[2][2] == z && X[1][1] == z && X[0][2] == e)
				playZ(s, 0, 2);
			}
			//______________________________________________________________
		}
		//this is normal mode the computer blocks some winning moves or else it plays random
		if (difficulty == 1 && turn)
		{
			if (X[0][0] == z && X[1][1] == z && X[2][2] == e)
				playZ(s, 2, 2);
			else if (X[0][0] == z && X[2][2] == z && X[1][1] == e)
				playZ(s, 1, 1);
			else if (X[1][1] == z && X[2][2] == z && X[0][0] == e)
				playZ(s, 0, 0);
			else if (X[0][2] == z && X[1][1] == z && X[2][0] == e)
				playZ(s, 2, 0);
			else if (X[0][2] == z && X[2][0] == z && X[1][1] == e)
				playZ(s, 1, 1);
			else if (X[1][1] == z && X[2][0] == z && X[0][2] == e)
				playZ(s, 0, 2);
			int i = 0;
			while (i < 3 && turn)
			{

				if (X[0][i] == z && X[1][i] == z && X[2][i] == e)
					playZ(s, 2, i);
				else if (X[0][i] == z && X[2][i] == z && X[1][i] == e)
					playZ(s, 1, i);
				else if (X[1][i] == z && X[2][i] == z && X[0][i] == e)
					playZ(s, 0, i);
				else if (X[i][0] == z && X[i][1] == z && X[i][2] == e)
					playZ(s, i, 2);
				else if (X[i][0] == z && X[i][2] == z && X[i][1] == e)
					playZ(s, i, 1);
				else if (X[i][1] == z && X[i][2] == z && X[i][0] == e)
					playZ(s, i, 0);
				i++;
			}
		}
		//this block of code is for any mode and it makes the computer play random moves
		if ((difficulty>=0&&difficulty<=2)&& turn)
		{
			r = rand() % 3;
			c = rand() % 3;
			while (!check(r, c))
			{
				r = rand() % 3;
				c = rand() % 3;
			}
			playZ(s, r, c);
		}
	}
	void clear()//clears the game board for a new game
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				X[i][j] = e;
		plays = 0;
	}
	bool check(int row, int column)//checks if the given position is empty or not
	{
		return (row >= 0 && row <= 2 && column >= 0 && column <= 2 && X[row][column] == e);
	}
	void display()//this function displays the game board
	{
		system("cls");
		cout << "\n__________________\n";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << "|";
				if (X[i][j] == x)
					cout << "  X  ";
				else if (X[i][j] == o)
					cout << "  O  ";
				else
					cout << "     ";
			}
			cout << "|";
			cout << "\n__________________\n";
		}
	}
	//this block of functions checks if we have a complete row or column or cross
	int cross0()
	{
		if (X[0][0] == o && X[1][1] == o && X[2][2] == o)
			return 1;
		else if (X[0][0] == x && X[1][1] == x && X[2][2] == x)
			return 2;
		else return 0;
	}
	int cross1()
	{
		if (X[0][2] == o && X[1][1] == o && X[2][0] == o)
			return 1;
		else if (X[0][2] == x && X[1][1] == x && X[2][0] == x)
			return 2;
		else return 0;
	}
	int column0()
	{
		if (X[0][0] == o && X[1][0] == o && X[2][0] == o)
			return 1;
		else if (X[0][0] == x && X[1][0] == x && X[2][0] == x)
			return 2;
		else return 0;
	}
	int column1()
	{
		if (X[0][1] == o && X[1][1] == o && X[2][1] == o)
			return 1;
		else if (X[0][1] == x && X[1][1] == x && X[2][1] == x)
			return 2;
		else return 0;
	}
	int column2()
	{
		if (X[0][2] == o && X[1][2] == o && X[2][2] == o)
			return 1;
		else if (X[0][2] == x && X[1][2] == x && X[2][2] == x)
			return 2;
		else return 0;
	}
	int row0()
	{
		if (X[0][0] == o && X[0][1] == o && X[0][2] == o)
			return 1;
		else if (X[0][0] == x && X[0][1] == x && X[0][2] == x)
			return 2;
		else return 0;
	}
	int row1()
	{
		if (X[1][0] == o && X[1][1] == o && X[1][2] == o)
			return 1;
		else if (X[1][0] == x && X[1][1] == x && X[1][2] == x)
			return 2;
		else return 0;
	}
	int row2()
	{
		if (X[2][0] == o && X[2][1] == o && X[2][2] == o)
			return 1;
		else if (X[2][0] == x && X[2][1] == x && X[2][2] == x)
			return 2;
		else return 0;
	}
};
//main function of the game
int main()
{
	tictactoe game;
	bool restart = 1;
	while (restart)
	{
		game.play();
		game.winner();
		cout << "restart?\nenter 1 for yes and 0 for no\n";
		cin >> restart;
		game.clear();
	}
	system("pause");
	return 0;
}