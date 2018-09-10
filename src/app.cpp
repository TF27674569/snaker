/*
 * app.cpp
 *
 *  Created on: 2018年9月7日
 *  Author: TIAN FENG
 */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include<windows.h>

int main() {

//	HANDLE hOut, hIn; /*标准输出输入句柄*/
//	COORD size = {1080, 1080}; /*窗口大小*/
//	SMALL_RECT rc = {0, 0, 1080-1, 1080-1};
//	CONSOLE_CURSOR_INFO cursor = {1, FALSE}; /*光标信息，用于隐藏光标*/
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

