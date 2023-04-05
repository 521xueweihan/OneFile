#include<iostream>
#include<math.h>
#include<Windows.h>
#include<conio.h>
#include<ctime>
using namespace std;

enum DIR
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

time_t start = 0, finish = 0;

int _x = 6, _y = 1;//图形生成位置

int map[30][16] = { 0 };

int sharp[20][8] = {
	{0,0,0,0,0,0,0,0},
	//I形
	{0,0,0,1,0,2,0,3},
	{0,0,1,0,2,0,3,0},
	//■形
	{0,0,1,0,0,1,1,1},
	//L形
	{0,0,0,1,0,2,1,2},
	{0,0,0,1,1,0,2,0},
	{0,0,1,0,1,1,1,2},
	{0,1,1,1,2,0,2,1},
	//J形
	{0,2,1,0,1,1,1,2},
	{0,0,0,1,1,1,2,1},
	{0,0,0,1,0,2,1,0},
	{0,0,1,0,2,0,2,1},
	//Z形
	{0,0,1,0,1,1,2,1},
	{0,1,0,2,1,0,1,1},
	//S形
	{0,1,1,0,1,1,2,0},
	{0,0,0,1,1,1,1,2},
	//T形
	{0,1,1,0,1,1,2,1},
	{0,0,0,1,0,2,1,1},
	{0,0,1,0,1,1,2,0},
	{0,1,1,0,1,1,1,2}
};


class Game
{
public:
	int score;//游戏分数
	int _id;//图形编号
	int top;//最高点高度
	int speed;//下落速度

	Game();
	void showMenu();//显示菜单
	void showGround();//显示游戏界面
	void gameOver();//游戏结束界面
	void Run();//运行游戏
	void sharpDraw(int id, bool show = false);//绘制图形
	void keyControl();//键盘控制
	bool move(int dir, int id);//移动判断
	bool downSet(int id);//下落
	void Turn(int id);//旋转
	void clean();//消行
};

void SetPos(int i, int j)//控制光标位置， 列， 行
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	cursor.bVisible = 0;	//这四行用来设置光标不显示
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

	srand((unsigned)time(NULL));

	Game game;
	game.showMenu();
	return 0;
}

Game::Game()
{
	score = 0;
	_id = 0;
	top = 58;
	speed = 1000;
}

void Game::showMenu()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if ((i == 0 || i == 29) || (j == 0 || j == 25))
			{
				cout << "■";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}

	SetPos(17, 8);
	cout << "俄 罗 斯 方 块" << endl;
	SetPos(13, 12);
	cout << "↑旋转方块  ↓加速下滑" << endl;
	SetPos(12, 14);
	cout << "← →左右移动  空格  暂停" << endl;
	SetPos(15, 20);
	cout << "0 退出  Enter 开始" << endl;

	while (1)
	{
		int select = _getch();
		if (select == 13)
		{
			system("cls");
			this->Run();
		}
		else if (select = 48)
		{
			system("cls");
			exit(0);
		}
	}
}

void Game::showGround()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if ((i == 0 || i == 29) || (j == 0 || j == 25 || j == 15))
			{
				cout << "■";
			}
			else if (i == 15 && j > 15)
			{
				cout << "■";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}

	SetPos(31, 2);
	cout << "下 个图形" << endl;
	SetPos(31, 17);
	cout << "当 前得分" << endl;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if ((i == 0 || i == 29) || (j == 0 || j == 15))
			{
				map[i][j] = 1;
			}
			else
			{
				map[i][j] = 0;
			}
		}
	}
}

void Game::gameOver()
{
	for (int i = 5; i < 15; i++)
	{
		SetPos(1, i);
		cout << "                            " << endl;
	}

	SetPos(8, 7);
	cout << "G a m e   O v e r" << endl;

	SetPos(3, 10);
	cout << "0 退出   Enter 重新开始" << endl;

	while (1)
	{
		int select = _getch();
		if (select == 13)
		{
			system("cls");
			this->Run();
		}
		else if (select == 48)
		{
			system("cls");
			exit(0);
		}
	}

}

void Game::Run()
{
	score = 0;
	_id = 0;
	top = 58;
	_x = 6;
	_y = 1;
	showGround();
	start = clock();
	int new_id = rand() % 19 + 1;

	while (1)
	{
		sharpDraw(_id);
		keyControl();

		if (downSet(_id))
		{
			sharpDraw(-new_id, 1);
			_id = new_id;
			new_id = rand() % 19 + 1;
			sharpDraw(new_id, 1);
			clean();
		}

		SetPos(34, 20);
		cout << score << endl;
	}
}

void Game::sharpDraw(int id, bool show)
{
	int x, y;

	if (show == true)
	{
		if (id > 0)
		{
			for (int i = 0; i < 4; i++)
			{
				x = 19 + sharp[id][2 * i];
				y = 6 + sharp[id][2 * i + 1];
				SetPos(2 * x, y);
				cout << "■";
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				x = 19 + sharp[-id][2 * i];
				y = 6 + sharp[-id][2 * i + 1];
				SetPos(2 * x, y);
				cout << "  ";
			}
		}
		return;
	}


	if (id > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			SetPos(2 * x, y);
			cout << "■";
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[-id][2 * i];
			y = _y + sharp[-id][2 * i + 1];
			SetPos(2 * x, y);
			cout << "  ";
		}
	}
	return;

}

bool Game::downSet(int id)
{
	if (id == 0)
		return true;

	finish = clock();

	if (finish - start < speed)
	{
		return false;
	}

	start = clock();

	if (!move(DOWN, _id))
	{
		int x, y;
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			map[y][x] = 1;

			if (y < top)
			{
				top = y;
			}
			if (top <= 1)
			{
				gameOver();
			}
		}
		_x = 6;
		_y = 1;
		return true;
	}

	sharpDraw(-id);
	_y++;
	sharpDraw(id);
	return false;
}

bool Game::move(int dir, int id)
{
	int x, y;
	switch (dir)
	{
	case UP:
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			if (map[y][x] == 1)
			{
				return false;
			}
		}
		break;
	case DOWN:
	{
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			if (map[y + 1][x] == 1)
			{
				return false;
			}
		}
	}
	break;
	case RIGHT:
	{
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			if (map[y][x + 1] == 1)
			{
				return false;
			}
		}
	}
	break;
	case LEFT:
	{
		for (int i = 0; i < 4; i++)
		{
			x = _x + sharp[id][2 * i];
			y = _y + sharp[id][2 * i + 1];
			if (map[y][x - 1] == 1)
			{
				return false;
			}
		}
	}
	break;
	default:
		break;
	}
	return true;
}

void Game::Turn(int id)
{
	switch (id)
	{
	case 1:id++; break;
	case 2:id--; break;

	case 3: break;

	case 4:id++; break;
	case 5:id++; break;
	case 6:id++; break;
	case 7:id -= 3; break;

	case 8:id++; break;
	case 9:id++; break;
	case 10:id++; break;
	case 11:id -= 3; break;

	case 12:id++; break;
	case 13:id--; break;

	case 14:id++; break;
	case 15:id--; break;

	case 16:id++; break;
	case 17:id++; break;
	case 18:id++; break;
	case 19:id -= 3; break;

	default:
		break;
	}

	if (!move(UP, id))
	{
		return;
	}

	sharpDraw(-_id);
	_id = id;
}

void Game::keyControl()
{
	if (!_kbhit())
		return;

	int key = _getch();

	switch (key)
	{
	case 72:
		Turn(_id);
		break;
	case 80:
		if (move(DOWN, _id))
		{
			sharpDraw(-_id);
			_y++;
		}
		break;
	case 75:
		if (move(LEFT, _id))
		{
			sharpDraw(-_id);
			_x--;
		}
		break;
	case 77:
		if (move(RIGHT, _id))
		{
			sharpDraw(-_id);
			_x++;
		}
		break;
	case 32:
	{
		for (int i = 5; i < 15; i++)
		{
			SetPos(1, i);
			cout << "                            " << endl;
		}

		SetPos(10, 7);
		cout << "游 戏 暂 停" << endl;

		SetPos(3, 10);
		cout << "0 返回菜单  回车 继续游戏" << endl;

		while (1)
		{
			int select = _getch();

			if (select == 13)
			{
				for (int i = 5; i < 15; i++)
				{
					SetPos(1, i);
					cout << "                            " << endl;
				}
				break;
			}
			else if (select == 48)
			{
				system("cls");
				showMenu();
			}
		}

	}
	default:
		break;
	}
}

void Game::clean()
{
	int n = -1;
	int line = -1;
	while (1)
	{
		for (int i = 28; i > 0; i--)
		{
			for (int j = 1; j < 15; j++)
			{
				line = i;
				if (map[i][j] == 0)
				{
					line = -1;
					break;
				}
			}
			if (line != -1)
				break;
		}

		if (line == -1)
			break;

		for (int i = line; i > 0; i--)
		{
			for (int j = 1; j < 15; j++)
			{
				if (i == 1)
					map[i][j] = 0;
				else
				{
					map[i][j] = map[i - 1][j];
					SetPos(2 * j, i);
					if (map[i][j] == 1)
						cout << "■";
					else
						cout << "  ";
				}
			}
		}
		top++;
		n++;
	}

	if (n >= 0)
	{
		score += n * n * 100 + 100;
		if (speed > 100)
			speed = 1000 - score / 10;
	}
}
