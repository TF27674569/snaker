/*
 * app.cpp
 *
 *  Created on: 2018��9��7��
 *  Author: TIAN FENG
 */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include<windows.h>

int main() {

//	HANDLE hOut, hIn; /*��׼���������*/
//	COORD size = {1080, 1080}; /*���ڴ�С*/
//	SMALL_RECT rc = {0, 0, 1080-1, 1080-1};
//	CONSOLE_CURSOR_INFO cursor = {1, FALSE}; /*�����Ϣ���������ع��*/
//
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	SetConsoleWindowInfo(hOut, TRUE, &rc);
//	SetConsoleScreenBufferSize(hOut, size);
//	SetConsoleCursorInfo(hOut, &cursor);

	startGame();
	system("pause");
	return 0;
}

