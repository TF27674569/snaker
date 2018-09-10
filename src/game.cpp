/*
 * game.cpp
 *
 *  Created on: 2018��9��7��
 *  Author: TIAN FENG
 */

#include "game.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// ���
#define WIDTH  25 // ÿ���ַ�ռһ���߶��������
#define HEIGHT WIDTH

/**
 * �����������
 * ʹ������Ľṹ
 */
typedef struct SNAKER {
	int x;
	int y;
	SNAKER* next;
} Snaker;

/**
 * ʳ��
 * ������� ������ǽ��
 * ������������
 */
typedef struct FOOD {
	int x;
	int y;
} Food;

/**
 * �����ߵ�ͷ��β
 */
Snaker* snaker;

// ʳ��
static Food food;

// ����
int score, speed;

/**
 * ��ʼ��Ϸ
 */
void startGame() {
	// ��ǽ��
	printWall();
	// ��ʼ����
	initSnaker();
	creatFood();
	// ���̿���
	clickControl();
}

/**
 * ��ʼ���߱���
 */
void initSnaker() {
	snaker = (Snaker*) malloc(sizeof(Snaker));
	snaker->x = 10;
	snaker->y = 15;
	Snaker* p1 = (Snaker*) malloc(sizeof(Snaker));
	p1->x = 10;
	p1->y = 16;
	Snaker* p2 = (Snaker*) malloc(sizeof(Snaker));
	p2->x = 10;
	p2->y = 17;

	snaker->next = p1;
	p1->next = p2;
	p2->next = NULL;
}

/**
 * ����ʳ��
 */
void creatFood() {
	srand((int) time(NULL));
	lable:
	// ��rand()���������[x,y]�ڵ�����int k=x+rand()%(y-x+1)
	food.y = rand() % (HEIGHT - 2) + 1; // [1,HEIGHT-1]
	food.x = rand() % ((WIDTH - 1) << 1 - 2 + 1) + 2; // [2,(WIDTH-1)<<1]
	if (food.x % 2 != 0) {
		food.x = food.x + 1;
	}

	Snaker *judge = snaker;
	//�����ų������ظ�
	while (judge->next) {
		if (food.x == judge->x && food.y == judge->y) {
			// �����ظ������־�ֱ������
			goto lable;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("��");
}

/**
 * ��ӡΧǽ
 */
void printWall() {
	for (int i = 0; i < WIDTH; i++) {
		// ռ��λÿ�ε�ֵ�������2
		printFull(i << 1, 0);
		printFull(i << 1, HEIGHT - 1);
	}

	// ��һ�������һ�����Ѿ��ں����������
	for (int i = 1; i < HEIGHT - 1; i++) {
		// ռ��λÿ�ε�ֵ�������2
		printFull(0, i);
		printFull((WIDTH - 1) << 1, i);
	}
}

/**
 * ��ӡʵ��
 */
void printFull(int x, int y) {
	gotoxy(x, y);
	printf("��");
}

/**
 * ��ӡ�հ�
 */
void printEmpty(int x, int y) {
	gotoxy(x, y);
	printf(" ");
}

/**
 * ������ƶ���ĳ��λ��
 */
void gotoxy(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��׼����������
	COORD coord = { x, y };// ���λ��
	CONSOLE_CURSOR_INFO cursor = {1, FALSE}; /*�����Ϣ���������ع��*/
	SetConsoleCursorPosition(hOut, coord);
	SetConsoleCursorInfo(hOut, &cursor);
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);//������ɫ
}

/**
 * �ж���Ϸ�Ƿ���������
 */
int gameRuning() {
	// 1. ��ͷײǽû
	if (snaker->x == 0 || snaker->x == (WIDTH - 1) << 1 || snaker->y == 0
			|| snaker->y == WIDTH - 1) {
		gameOver();
		return 0;
	}

	// 2. ��ͷײ����û
	Snaker *p = snaker->next;
	while (p->next) {
		if (snaker->x == p->x && snaker->y == p->y) {
			gameOver();
			return 0;
		}
		p = p->next;
	}
	return 1;

}

int temp;
// �����ߵ���λ
int clickControl() {
	// ���Ʒ���
	char control;

	// ������оͿ���ֱ�Ӳ���
	while (gameRuning()) {

		// ��������ȡ������Ӧ
		if (kbhit()) {
			// ��ȡ���̵���Ӧ
			control = getch();
		}

		// �ƶ���
		move(control);
	}
	return 0;
}

/**
 * �Ե�ʳ��
 */
int eatFoot(int x, int y) {
	if (x == food.x && y == food.y) {
		Snaker *_new = (Snaker*) malloc(sizeof(Snaker));
		_new->x = food.x;
		_new->y = food.y;
		_new->next = snaker;
		snaker = _new;
		score += 10;
		// ��ӡ����
		gotoxy(60, 11);
		printf("���� �� %d", score);
		//����ʳ���ٴ���
		creatFood();
		return 1;
	}
	return 0;

}

/**
 * �ƶ�
 */
void move(char action) {
	int count = 0;
	// 1. �������
	Snaker* p = snaker;
	while (p != NULL) {
		printEmpty(p->x, p->y);
		p = p->next;
		count++;
	}

	switch (action) {
	case 'w':
	case 'W':
	case 72:
		change(snaker->x, snaker->y - 1);
		break;
	case 's':
	case 'S':
	case 80:
		change(snaker->x, snaker->y + 1);
		break;
	case 'A':
	case 'a':
	case 75:
		change(snaker->x - 2, snaker->y);
		break;
	case 'D':
	case 'd':
	case 77:
		change(snaker->x + 2, snaker->y);
		break;
	case 'Q':
	case 'q':
	case 0x1b:
		getchar();
		break;
	}

	// 2. ���´�ӡ��
	p = snaker;
	while (p != NULL) {
		printFull(p->x, p->y);
		p = p->next;
	}

	// ����һ���ٶ�
	gotoxy(60, 9);// �ȼ���ӡλ��
	if (count <= 10){
		speed = 300;
		// ��ӡ����
		printf("�ȼ� �� ����");
	}
	else if (count > 10 && count <= 20){
		printf("�ȼ� �� ����");
		speed = 200;
	}
	else if (count > 20 && count <= 40){
		printf("�ȼ� �� �м�");
		speed = 100;
	}
	else{
		printf("�ȼ� �� �߼�");
		speed = 30;
	}
	Sleep(speed);

	// ���λ��
//	gotoxy(0, HEIGHT);
}

/**
 * �ı��ߵ�״̬
 */
void change(int x, int y) {

	/**
	 * ���ж��費��Ҫ�Ե�ʳ��
	 */
	if(eatFoot(x,y)){
		// ���Ե�����ͷ�ϼ���һ��
		// ����ֱ�Ӵ�ӡ����ȥ��β��
		return;
	}

	Snaker* p = snaker;


	// �Ƴ�β��
	while (p != NULL) {
		if (p->next->next == NULL) {
			break;
		}
		p = p->next;
	}

	Snaker* temp = p->next->next;
	p->next = NULL;
	// �ͷ����һ��
	free(temp);
	// �Ϳ����һ��

	// �½�һ�� x y ��ͷ��
	temp = (Snaker*) malloc(sizeof(Snaker));
	temp->x = x;
	temp->y = y;
	temp->next = snaker;
	snaker = temp;

}

void gameOver(){
		system("cls");
		gotoxy(15, 10);
		printf("**********************************************");
		gotoxy(15, 20);
		printf("**********************************************");
		gotoxy(18, 14);
		printf("GAME   OVER      o(*������*)o");
		gotoxy(20, 16);
		printf("��ķ֔�: %d", score);
		gotoxy(18, 18);
		printf("������Ŷ��     ����Ŭ��O(��_��)O");
		gotoxy(0, 27);
}

