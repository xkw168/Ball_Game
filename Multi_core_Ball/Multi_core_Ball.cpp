// Multi_core_Ball.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void playGame();
void initGame();
void reDraw();
int getDirection();
DWORD WINAPI Thread_player1(LPVOID lpParameter);
DWORD WINAPI Thread_player2(LPVOID lpParameter);

HANDLE handle1, handle2;
HANDLE hEvent[2];

Ball *player1, *player2;
Dot *dot;
TCHAR s[10];//the score
TCHAR s1[20] = _T("Player1:");//the score
TCHAR s2[20] = _T("Player2:");//the score
bool dir1, dir2;
bool isFinish;//����ͬ�������̵߳�ȫ�ֱ���
int direction;

void main()
{
	initGame();
	playGame();
	CloseHandle(handle1);
	CloseHandle(handle2);
	closegraph();
	printf("��Ϸ����!!!\n");
	printf("���1�÷֣�%d\n", player1->getScore());
	printf("���2�÷֣�%d\n", player2->getScore());
	if (player1->getScore() > player2->getScore())
	{
		printf("���1��ʤ������\n");
	}
	else
	{
		printf("���2��ʤ������\n");
	}
}

void initGame()
{
	initgraph(GRAPH_WIDE, GRAPH_HIGH);//������Ϸ����
	setbkcolor(LIGHTGRAY);//���ñ���ɫ
	setfillcolor(CYAN);//�������ɫ
	setlinecolor(CYAN);//��������ɫ

	dot = new Dot();
	//�½����
	player1 = new Ball(PLAYER_STARTX, PLAYER1_STARTY);
	player2 = new Ball(PLAYER_STARTX, PLAYER2_STARTY);

	//���ں����߳�ͬ�����¼�
	hEvent[0] = CreateEvent(NULL, FALSE, FALSE, _T("Player1"));
	hEvent[1] = CreateEvent(NULL, FALSE, FALSE, _T("Player2"));
	//����������ҵ��߳�
	handle1 = CreateThread(NULL, 0, Thread_player1, NULL, 0, NULL);
	handle2 = CreateThread(NULL, 0, Thread_player2, NULL, 0, NULL);
	Sleep(50);//�ӳ�һ��ʱ�䣬��֤������Ҷ��������

	dir1 = false;
	dir2 = false;
	isFinish = false;
	direction = LEFT;
}

void playGame()
{
	char key;
	while (!isFinish)
	{
		WaitForMultipleObjects(2, hEvent, TRUE, INFINITE);//�����¼����ź�ʱ�ͷ���ֵ
		reDraw();
		if (_kbhit())//���������Ļ����ı䷽��.û�оͷ��򲻱�
		{
			key = _getch();
			if (key == -32)
			{
				key = _getch();
				if (key == 72)//��
				{
					direction = UP;
					dir2 = true;
				}
				else if (key == 80)//��
				{
					direction = DOWN;
					dir2 = true;
				}
				else if (key == 75)//��
				{
					direction = LEFT;
					dir2 = true;
				}
				else if (key == 77)//��
				{
					direction = RIGHT;
					dir2 = true;
				}
			}
			else if (key == 'w')
			{
				direction = UP;
				dir1 = true;
			}
			else if (key == 'a')
			{
				direction = LEFT;
				dir1 = true;
			}
			else if (key == 's')
			{
				direction = DOWN;
				dir1 = true;
			}
			else if (key == 'd')
			{
				direction = RIGHT;
				dir1 = true;
			}
		}
	}
}

void reDraw()
{
	Sleep(SLEEP_TIME);
	//����
	cleardevice();
	//�ػ�ͼ��
	player1->draw();
	player2->draw();
	dot->draw();
	//��ʾ�ɼ�
	outtextxy(GRAPH_WIDE - 100, 50, s1);
	_stprintf(s, _T("%d"), player1->getScore());//���ַ���ת��Ϊ����
	outtextxy(GRAPH_WIDE - 30, 50, s);
	outtextxy(GRAPH_WIDE - 100, 70, s2);
	_stprintf(s, _T("%d"), player2->getScore());//���ַ���ת��Ϊ����
	outtextxy(GRAPH_WIDE - 30, 70, s);
}

DWORD WINAPI Thread_player1(LPVOID lpParameter)
{
	int state1;
	while (true)
	{
		//�ж��Ƿ��а�����Ҫ�ı䷽��
		if (dir1)
		{
			player1->changeDirection(direction);
			dir1 = false;
		}
		state1 = player1->checkState(player2, dot);
		if (state1 == HIT_WALL)
		{
			player1->init(PLAYER_STARTX, PLAYER1_STARTY);//ײǽ���������¿�ʼ
		}
		else if(state1 == HIT_BALL)
		{
			if (player1->getR() <= player2->getR())//�ȱ���С
			{
				player1->init(PLAYER_STARTX, PLAYER1_STARTY);//�����˳Ե�
				player2->eat(3);//���2��������
			}
			else
			{
				player2->init(PLAYER_STARTX, PLAYER2_STARTY);//�Ե�����
				player1->eat(3);//���1��������
			}
		}
		else if (state1 == EAT)
		{
			player1->eat(dot->getR() - 5);//�Ե����ӣ���������
			dot->change();//�ػ����
		}
		else if(state1 == KEEP)
		{
			player1->move();
		}
		if (player1->getScore() == GAME_OVER)
		{
			break;
		}
		Sleep(SLEEP_TIME);
		SetEvent(hEvent[0]);
	}
	isFinish = true;
	return 0;
}

DWORD WINAPI Thread_player2(LPVOID lpParameter)
{
	int state2;
	while (true)
	{
		//�ж��Ƿ��а�����Ҫ�ı䷽��
		if (dir2)
		{
			player2->changeDirection(direction);
			dir2 = false;
		}
		state2 = player2->checkState(player1, dot);
		if (state2 == HIT_WALL)
		{
			player2->init(PLAYER_STARTX, PLAYER2_STARTY);//ײǽ���������¿�ʼ
		}
		else if (state2 == HIT_BALL)
		{
			if (player2->getR() <= player1->getR())//�ȱ���С
			{
				player2->init(PLAYER_STARTX, PLAYER1_STARTY);//�����˳Ե�
				player1->eat(3);//���2��������
			}
			else
			{
				player1->init(PLAYER_STARTX, PLAYER2_STARTY);//�Ե�����
				player2->eat(3);//���1��������
			}
		}
		else if (state2 == EAT)
		{
			player2->eat(dot->getR() - 5);//�Ե����ӣ���������
			dot->change();//�ػ����
		}
		else if (state2 == KEEP)
		{
			player2->move();
		}
		if (player2->getScore() == GAME_OVER)
		{
			break;
		}
		Sleep(SLEEP_TIME);
		SetEvent(hEvent[1]);
	}
	isFinish = true;
	return 0;
}