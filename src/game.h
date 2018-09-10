/*
 * game.h
 *
 *  Created on: 2018年9月7日
 *  Author: TIAN FENG
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_


/**
 * 开始游戏
 */
void startGame();


/**
 * 初始化蛇变量
 */
void initSnaker();

/**
 * 创建食物
 */
void creatFood();

/**
 * 打印围墙
 */
void printWall();

/**
 * 打印实体
 */
void printFull(int x , int y);

/**
 * 打印空白
 */
void printEmpty(int x , int y);

/**
 * 将光标移动到某个位置
 */
void gotoxy(int x , int y);


// 控制蛇的走位
int clickControl();

/**
 * 吃到食物
 */
int eatFoot(int x, int y);


/**
 * 移动
 */
void move(char control);

/**
 * 改变蛇的状态
 */
void change(int x,int y);

/**
 * 游戏结束
 */
void gameOver();

#endif /* SRC_GAME_H_ */
