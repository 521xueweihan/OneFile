#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>


// 定义标记上下左右的明示常量 
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ESC 5 
#define FOOD 10
// 定义表示位置的结构体类型
typedef struct snake
{
	int x;
	int y;
	struct snake *next;
}snake;
// 定义全局变量 
int score = 0; // 当前得分
int speed = 200; // 存储当前速度
int status;
snake *tail, *head; // 存储蛇头蛇尾 
snake *food, *q;// q用于遍历链表 

HANDLE hOUT;
void gotoxy(int x, int y); // 设置光标位置 
int choice(void); // 载入游戏界面
int color(int c); // 设置字体颜色 
void printGame(void); // 打印游戏界面 
void printSnake(void); // 打印蛇身
void printFood(void); // 打印食物
void printTips(void); // 打印提示
void snakeMove(void); // 主操作函数 
int biteSelf(void); // 判断是否咬到了自己
int encounterWall(void); // 判断是否撞墙 
void keyboardControl(void); // 获取击键 
void speedUp(void); // 加速
void speedDown(void); // 减速
int endGame(void); // 结束函数; 
char *s_gets(char *st, int n); // 读取字符
void frees(snake *); // 释放内存 

int main(int argc, char *argv[])
{
	while (1)
	{
		if (choice() == 1)
			keyboardControl();
		else
		{
			gotoxy(5, 15);
			printf("按任意键返回");
			getchar(); // 去除前一个前导换行 
			while (1)
			{
				if (getchar())
				{
					system("cls");
					break;
				}
			}
		}
	}
	frees(head);

	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int choice(void)
{
	int yourchoice;
	// 画出界面 
	gotoxy(35, 5);
	color(11);
	printf("\t贪吃蛇大作战\n");
	printf("\n\n");
	color(13);
	printf("\t\t★★★★★★★★");
	printf("\t\t★★★★★★★★");
	gotoxy(25, 15);
	color(12);
	printf("1.进入游戏\t2.查看说明\t3.退出游戏\n");
	color(11);
	printf("请选择:");
	scanf("%d", &yourchoice);
	switch (yourchoice)
	{
	case 1:
		system("cls");
		// 初始化 
		printGame();
		printSnake();
		printFood();
		break;
	case 2:
		system("cls");
		printTips();
		break;
	case 3:
		system("cls");
		gotoxy(30, 10);
		color(11);
		printf("Bye!");
		exit(0);
	default:
		system("cls");
		printf("没有此序号,请输入1,2或3\n");
		Sleep(2000);
		system("cls");
	}
	return yourchoice;
}
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}
void printGame()
{
	int i, j;
	gotoxy(5, 5);
	printf("游戏载入中..请稍后");
	Sleep(2000);
	system("cls");

	// 打印上下界面
	for (i = 0; i <= 50; i += 2)
	{
		gotoxy(i, 0);
		printf("□");
		gotoxy(i, 25);
		printf("□");
	}
	// 打印左右界面
	for (i = 0; i <= 25; i += 1)
	{
		gotoxy(0, i);
		printf("□");
		gotoxy(50, i);
		printf("□");
	}
	// 打印中间网格
	for (i = 1; i <= 24; i += 1)
	{
		for (j = 2; j <= 48; j += 2)
		{
			gotoxy(j, i);
			color(11);
			printf("■");
		}
	}
	// 打印右侧的规则和计分栏
	gotoxy(60, 13);
	printf("当前分数:%d分,当前速度%d", score, speed);
	gotoxy(60, 15);
	printf("用↑ ↓ ← →分别控制蛇的移动\n");
	gotoxy(60, 18);
	printf("每次获取食物加10分  按下F1加速,F2减速,空格暂停\n");
	gotoxy(60, 20);
	printf("不能撞墙和咬到自己");
	gotoxy(60, 22);
	printf("速度不低于100,不高于300");
}
void printSnake(void)
{
	int i;
	// 设定蛇尾(16,13),头插入,初始向右 
	tail = (snake*)malloc(sizeof(snake));
	tail->x = 16;
	tail->y = 13;
	tail->next = NULL;
	// 设定初始蛇长是4
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 16 + 2 * i;
		head->y = 13;
		tail = head; // 头成为尾
	}
	// 输出蛇身
	while (tail->next)
	{
		gotoxy(tail->x, tail->y);
		color(14);
		printf("★");
		tail = tail->next;
	}
}
void printFood(void)
{
	srand((unsigned)time(NULL)); // 利用时钟修改种子 
	food = (snake*)malloc(sizeof(snake));
	food->x = 1; // 初始化x坐标 
	while (food->x % 2 && food->x)
	{
		food->x = rand() % 46 + 2;// 2-48 
	}
	food->y = rand() % 23 + 1; // 1-24 
	q = head; // 不改变头遍历链表 
	while (q->next)
	{
		if (q->x == food->x && q->y == food->y)
		{
			free(food);
			printFood();
		}
		else
		{
			gotoxy(food->x, food->y);
			color(12);
			printf("●");
			break;
		}
	}
}
void printTips(void)
{
	color(11);
	printf("***********Tips************\n");
	printf("1.采用合理的速度可以获得更高的分数\n");
	printf("2.一定不要撞到自己或者两边的墙\n");
	printf("3.游戏过程中按ESC退出游戏\n");
}
void snakeMove(void)
{
	snake *snakenext;
	snakenext = (snake*)malloc(sizeof(snake));
	if (biteSelf())
	{
		gotoxy(60, 11);
		printf("咬到自己了");
		free(snakenext);
		Sleep(1500);
		system("cls");
		exit(0);
	}
	else if (encounterWall())
	{
		gotoxy(60, 11);
		printf("撞到墙了");
		free(snakenext);
		Sleep(1500);
		system("cls");
		exit(0);
	}
	else
	{
		// 前两个条件判断完成才开始移动 
		Sleep(350 - speed);
		if (status == UP)
		{
			snakenext->x = head->x;
			snakenext->y = head->y - 1;
			snakenext->next = head;
			head = snakenext;
			q = head;
			if (snakenext->x == food->x && snakenext->y == food->y)
			{
				while (q)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("当前分数:%d分,当前速度%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("■");
				free(q->next);
				q->next = NULL;
			}
		}
		else if (status == DOWN)
		{
			snakenext->x = head->x;
			snakenext->y = head->y + 1;
			snakenext->next = head;
			head = snakenext;
			q = head;
			if (snakenext->x == food->x && snakenext->y == food->y)
			{
				while (q)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("当前分数:%d分,当前速度%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("■");
				free(q->next);
				q->next = NULL;
			}
		}
		else if (status == LEFT)
		{
			snakenext->x = head->x - 2;
			snakenext->y = head->y;
			snakenext->next = head;
			head = snakenext;
			q = head;
			if (snakenext->x == food->x && snakenext->y == food->y)
			{
				while (q)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("当前分数:%d分,当前速度%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("■");
				free(q->next);
				q->next = NULL;
			}
		}
		else if (status == RIGHT)
		{
			snakenext->x = head->x + 2;
			snakenext->y = head->y;
			snakenext->next = head;
			head = snakenext;
			q = head;
			if (snakenext->x == food->x && snakenext->y == food->y)
			{
				while (q)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("当前分数:%d分,当前速度%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("★");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("■");
				free(q->next);
				q->next = NULL;
			}
		}
	}
}
int biteSelf(void)
{
	int x = 0; // 默认未咬到自己
	q = head->next;
	// 遍历蛇身 
	while (q->next)
	{
		if (q->x == head->x && q->y == head->y)
		{
			x = 1;
		}
		q = q->next;
	}

	return x;
}
int encounterWall(void)
{
	int x = 0; // 默认未撞到墙

	if (head->x == 0 || head->x == 50 || head->y == 0 || head->y == 25)
		x = 1;

	return x;
}
void keyboardControl(void)
{
	status = RIGHT; // 初始蛇向右移动
	while (1)
	{
		if (GetAsyncKeyState(VK_UP) && status != DOWN) // GetAsyncKeyState函数用来判断函数调用时指定虚拟键的状态
		{
			status = UP;           //如果蛇不是向下前进的时候，按上键，执行向上前进操作
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != UP) // 如果蛇不是向上前进的时候，按下键，执行向下前进操作
		{
			status = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != RIGHT) // 如果蛇不是向右前进的时候，按左键，执行向左前进
		{
			status = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != LEFT) // 如果蛇不是向左前进的时候，按右键，执行向右前进
		{
			status = RIGHT;
		}
		if (GetAsyncKeyState(VK_SPACE))// 空格暂停 
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE)) // 再次按空格改变状态 
				{
					break;
				}

			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			status = ESC; // 按esc键,直接到结束界面
			if (endGame())
			{
				Sleep(500);
				system("cls");
				break;
			}
		}
		else if (GetAsyncKeyState(VK_F1)) // 按F1键，加速
		{
			speedUp();
			gotoxy(60, 13);
			printf("当前分数:%d分,当前速度%d", score, speed);
		}
		else if (GetAsyncKeyState(VK_F2)) // 按F2键，减速
		{
			speedDown();
			gotoxy(60, 13);
			printf("当前分数:%d分,当前速度%d", score, speed);
		}
		snakeMove();
	}
}
void speedUp(void)
{
	if (speed <= 280)
		speed += 20;
}
void speedDown(void)
{
	if (speed >= 120)
		speed -= 20;
}
int endGame(void)
{
	char x = 0;
	char judge[5];

	getchar();
	gotoxy(60, 9);
	printf("确定退出吗?(Yes/No)");
	gotoxy(60, 11);
	s_gets(judge, 5);

	if (strcmp(judge, "Yes") == 0)
	{
		Sleep(250);
		system("cls");
		gotoxy(40, 11);
		printf("\tBye!");
		x = 1;
	}
	else
		x = 0;

	return x;
}
char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;

	gotoxy(60, 11);
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
		while (getchar() != '\n')
			continue;
	}

	return ret_val;
}
void frees(snake *s)
{
	snake *current = s;

	while (current)
	{
		current = s;
		s = current->next;
		free(current);
	}
}
