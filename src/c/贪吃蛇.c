#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>


// �������������ҵ���ʾ���� 
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define ESC 5 
#define FOOD 10
// �����ʾλ�õĽṹ������
typedef struct snake
{
	int x;
	int y;
	struct snake *next;
}snake;
// ����ȫ�ֱ��� 
int score = 0; // ��ǰ�÷�
int speed = 200; // �洢��ǰ�ٶ�
int status;
snake *tail, *head; // �洢��ͷ��β 
snake *food, *q;// q���ڱ������� 

HANDLE hOUT;
void gotoxy(int x, int y); // ���ù��λ�� 
int choice(void); // ������Ϸ����
int color(int c); // ����������ɫ 
void printGame(void); // ��ӡ��Ϸ���� 
void printSnake(void); // ��ӡ����
void printFood(void); // ��ӡʳ��
void printTips(void); // ��ӡ��ʾ
void snakeMove(void); // ���������� 
int biteSelf(void); // �ж��Ƿ�ҧ�����Լ�
int encounterWall(void); // �ж��Ƿ�ײǽ 
void keyboardControl(void); // ��ȡ���� 
void speedUp(void); // ����
void speedDown(void); // ����
int endGame(void); // ��������; 
char *s_gets(char *st, int n); // ��ȡ�ַ�
void frees(snake *); // �ͷ��ڴ� 

int main(int argc, char *argv[])
{
	while (1)
	{
		if (choice() == 1)
			keyboardControl();
		else
		{
			gotoxy(5, 15);
			printf("�����������");
			getchar(); // ȥ��ǰһ��ǰ������ 
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
	// �������� 
	gotoxy(35, 5);
	color(11);
	printf("\t̰���ߴ���ս\n");
	printf("\n\n");
	color(13);
	printf("\t\t���������");
	printf("\t\t���������");
	gotoxy(25, 15);
	color(12);
	printf("1.������Ϸ\t2.�鿴˵��\t3.�˳���Ϸ\n");
	color(11);
	printf("��ѡ��:");
	scanf("%d", &yourchoice);
	switch (yourchoice)
	{
	case 1:
		system("cls");
		// ��ʼ�� 
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
		printf("û�д����,������1,2��3\n");
		Sleep(2000);
		system("cls");
	}
	return yourchoice;
}
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}
void printGame()
{
	int i, j;
	gotoxy(5, 5);
	printf("��Ϸ������..���Ժ�");
	Sleep(2000);
	system("cls");

	// ��ӡ���½���
	for (i = 0; i <= 50; i += 2)
	{
		gotoxy(i, 0);
		printf("��");
		gotoxy(i, 25);
		printf("��");
	}
	// ��ӡ���ҽ���
	for (i = 0; i <= 25; i += 1)
	{
		gotoxy(0, i);
		printf("��");
		gotoxy(50, i);
		printf("��");
	}
	// ��ӡ�м�����
	for (i = 1; i <= 24; i += 1)
	{
		for (j = 2; j <= 48; j += 2)
		{
			gotoxy(j, i);
			color(11);
			printf("��");
		}
	}
	// ��ӡ�Ҳ�Ĺ���ͼƷ���
	gotoxy(60, 13);
	printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
	gotoxy(60, 15);
	printf("�á� �� �� ���ֱ�����ߵ��ƶ�\n");
	gotoxy(60, 18);
	printf("ÿ�λ�ȡʳ���10��  ����F1����,F2����,�ո���ͣ\n");
	gotoxy(60, 20);
	printf("����ײǽ��ҧ���Լ�");
	gotoxy(60, 22);
	printf("�ٶȲ�����100,������300");
}
void printSnake(void)
{
	int i;
	// �趨��β(16,13),ͷ����,��ʼ���� 
	tail = (snake*)malloc(sizeof(snake));
	tail->x = 16;
	tail->y = 13;
	tail->next = NULL;
	// �趨��ʼ�߳���4
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 16 + 2 * i;
		head->y = 13;
		tail = head; // ͷ��Ϊβ
	}
	// �������
	while (tail->next)
	{
		gotoxy(tail->x, tail->y);
		color(14);
		printf("��");
		tail = tail->next;
	}
}
void printFood(void)
{
	srand((unsigned)time(NULL)); // ����ʱ���޸����� 
	food = (snake*)malloc(sizeof(snake));
	food->x = 1; // ��ʼ��x���� 
	while (food->x % 2 && food->x)
	{
		food->x = rand() % 46 + 2;// 2-48 
	}
	food->y = rand() % 23 + 1; // 1-24 
	q = head; // ���ı�ͷ�������� 
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
			printf("��");
			break;
		}
	}
}
void printTips(void)
{
	color(11);
	printf("***********Tips************\n");
	printf("1.���ú�����ٶȿ��Ի�ø��ߵķ���\n");
	printf("2.һ����Ҫײ���Լ��������ߵ�ǽ\n");
	printf("3.��Ϸ�����а�ESC�˳���Ϸ\n");
}
void snakeMove(void)
{
	snake *snakenext;
	snakenext = (snake*)malloc(sizeof(snake));
	if (biteSelf())
	{
		gotoxy(60, 11);
		printf("ҧ���Լ���");
		free(snakenext);
		Sleep(1500);
		system("cls");
		exit(0);
	}
	else if (encounterWall())
	{
		gotoxy(60, 11);
		printf("ײ��ǽ��");
		free(snakenext);
		Sleep(1500);
		system("cls");
		exit(0);
	}
	else
	{
		// ǰ���������ж���ɲſ�ʼ�ƶ� 
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
					printf("��");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("��");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("��");
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
					printf("��");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("��");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("��");
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
					printf("��");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("��");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("��");
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
					printf("��");
					q = q->next;
				}
				score += FOOD;
				gotoxy(60, 13);
				printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
				printFood();
			}
			else
			{
				while (q->next->next)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("��");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(11);
				printf("��");
				free(q->next);
				q->next = NULL;
			}
		}
	}
}
int biteSelf(void)
{
	int x = 0; // Ĭ��δҧ���Լ�
	q = head->next;
	// �������� 
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
	int x = 0; // Ĭ��δײ��ǽ

	if (head->x == 0 || head->x == 50 || head->y == 0 || head->y == 25)
		x = 1;

	return x;
}
void keyboardControl(void)
{
	status = RIGHT; // ��ʼ�������ƶ�
	while (1)
	{
		if (GetAsyncKeyState(VK_UP) && status != DOWN) // GetAsyncKeyState���������жϺ�������ʱָ���������״̬
		{
			status = UP;           //����߲�������ǰ����ʱ�򣬰��ϼ���ִ������ǰ������
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != UP) // ����߲�������ǰ����ʱ�򣬰��¼���ִ������ǰ������
		{
			status = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != RIGHT) // ����߲�������ǰ����ʱ�򣬰������ִ������ǰ��
		{
			status = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != LEFT) // ����߲�������ǰ����ʱ�򣬰��Ҽ���ִ������ǰ��
		{
			status = RIGHT;
		}
		if (GetAsyncKeyState(VK_SPACE))// �ո���ͣ 
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE)) // �ٴΰ��ո�ı�״̬ 
				{
					break;
				}

			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			status = ESC; // ��esc��,ֱ�ӵ���������
			if (endGame())
			{
				Sleep(500);
				system("cls");
				break;
			}
		}
		else if (GetAsyncKeyState(VK_F1)) // ��F1��������
		{
			speedUp();
			gotoxy(60, 13);
			printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
		}
		else if (GetAsyncKeyState(VK_F2)) // ��F2��������
		{
			speedDown();
			gotoxy(60, 13);
			printf("��ǰ����:%d��,��ǰ�ٶ�%d", score, speed);
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
	printf("ȷ���˳���?(Yes/No)");
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
