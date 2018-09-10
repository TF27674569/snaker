/*
 * game.cpp
 *
 *  Created on: 2018年9月7日
 *  Author: TIAN FENG
 */

#include "game.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// 宽高
#define WIDTH  25 // 每个字符占一个高度两个宽度
#define HEIGHT WIDTH

/**
 * 定义设的身体
 * 使用链表的结构
 */
typedef struct SNAKER {
	int x;
	int y;
	SNAKER* next;
} Snaker;

/**
 * 食物
 * 随机出现 不能在墙上
 * 不能在蛇身上
 */
typedef struct FOOD {
	int x;
	int y;
} Food;

/**
 * 定义蛇的头和尾
 */
Snaker* snaker;

// 食物
static Food food;

// 分数
int score, speed;

/**
 * 开始游戏
 */
void startGame() {
	// 画墙壁
	printWall();
	// 初始化蛇
	initSnaker();
	creatFood();
	// 键盘控制
	clickControl();
}

/**
 * 初始化蛇变量
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
 * 创建食物
 */
void creatFood() {
	srand((int) time(NULL));
	lable:
	// 用rand()随机生成在[x,y]内的整数int k=x+rand()%(y-x+1)
	food.y = rand() % (HEIGHT - 2) + 1; // [1,HEIGHT-1]
	food.x = rand() % ((WIDTH - 1) << 1 - 2 + 1) + 2; // [2,(WIDTH-1)<<1]
	if (food.x % 2 != 0) {
		food.x = food.x + 1;
	}

	Snaker *judge = snaker;
	//遍历排除蛇身重复
	while (judge->next) {
		if (food.x == judge->x && food.y == judge->y) {
			// 遇到重复的数字就直接重来
			goto lable;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("●");
}

/**
 * 打印围墙
 */
void printWall() {
	for (int i = 0; i < WIDTH; i++) {
		// 占两位每次的值必须乘以2
		printFull(i << 1, 0);
		printFull(i << 1, HEIGHT - 1);
	}

	// 第一个和最后一个就已经在横向上面打了
	for (int i = 1; i < HEIGHT - 1; i++) {
		// 占两位每次的值必须乘以2
		printFull(0, i);
		printFull((WIDTH - 1) << 1, i);
	}
}

/**
 * 打印实体
 */
void printFull(int x, int y) {
	gotoxy(x, y);
	printf("■");
}

/**
 * 打印空白
 */
void printEmpty(int x, int y) {
	gotoxy(x, y);
	printf(" ");
}

/**
 * 将光标移动到某个位置
 */
void gotoxy(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 标准输入输出句柄
	COORD coord = { x, y };// 光标位置
	CONSOLE_CURSOR_INFO cursor = {1, FALSE}; /*光标信息，用于隐藏光标*/
	SetConsoleCursorPosition(hOut, coord);
	SetConsoleCursorInfo(hOut, &cursor);
	SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);//设置颜色
}

/**
 * 判断游戏是否正在运行
 */
int gameRuning() {
	// 1. 蛇头撞墙没
	if (snaker->x == 0 || snaker->x == (WIDTH - 1) << 1 || snaker->y == 0
			|| snaker->y == WIDTH - 1) {
		gameOver();
		return 0;
	}

	// 2. 蛇头撞蛇身没
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
// 控制蛇的走位
int clickControl() {
	// 控制方向
	char control;

	// 如果运行就可以直接操作
	while (gameRuning()) {

		// 非阻塞读取键盘相应
		if (kbhit()) {
			// 读取键盘的响应
			control = getch();
		}

		// 移动蛇
		move(control);
	}
	return 0;
}

/**
 * 吃到食物
 */
int eatFoot(int x, int y) {
	if (x == food.x && y == food.y) {
		Snaker *_new = (Snaker*) malloc(sizeof(Snaker));
		_new->x = food.x;
		_new->y = food.y;
		_new->next = snaker;
		snaker = _new;
		score += 10;
		// 打印分数
		gotoxy(60, 11);
		printf("分数 ： %d", score);
		//吃完食物再创建
		creatFood();
		return 1;
	}
	return 0;

}

/**
 * 移动
 */
void move(char action) {
	int count = 0;
	// 1. 先清空蛇
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

	// 2. 重新打印蛇
	p = snaker;
	while (p != NULL) {
		printFull(p->x, p->y);
		p = p->next;
	}

	// 控制一下速度
	gotoxy(60, 9);// 等级打印位置
	if (count <= 10){
		speed = 300;
		// 打印分数
		printf("等级 ： 入门");
	}
	else if (count > 10 && count <= 20){
		printf("等级 ： 初级");
		speed = 200;
	}
	else if (count > 20 && count <= 40){
		printf("等级 ： 中级");
		speed = 100;
	}
	else{
		printf("等级 ： 高级");
		speed = 30;
	}
	Sleep(speed);

	// 光标位置
//	gotoxy(0, HEIGHT);
}

/**
 * 改变蛇的状态
 */
void change(int x, int y) {

	/**
	 * 先判断需不需要吃掉食物
	 */
	if(eatFoot(x,y)){
		// 被吃掉我在头上加了一个
		// 可以直接打印不用去掉尾部
		return;
	}

	Snaker* p = snaker;


	// 移除尾部
	while (p != NULL) {
		if (p->next->next == NULL) {
			break;
		}
		p = p->next;
	}

	Snaker* temp = p->next->next;
	p->next = NULL;
	// 释放最后一个
	free(temp);
	// 滞空最后一个

	// 新建一个 x y 放头部
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
		printf("GAME   OVER      o(*￣▽￣*)o");
		gotoxy(20, 16);
		printf("你的分數: %d", score);
		gotoxy(18, 18);
		printf("还不错哦，     继续努力O(∩_∩)O");
		gotoxy(0, 27);
}

