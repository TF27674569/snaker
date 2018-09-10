/*
 * game.h
 *
 *  Created on: 2018��9��7��
 *  Author: TIAN FENG
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_


/**
 * ��ʼ��Ϸ
 */
void startGame();


/**
 * ��ʼ���߱���
 */
void initSnaker();

/**
 * ����ʳ��
 */
void creatFood();

/**
 * ��ӡΧǽ
 */
void printWall();

/**
 * ��ӡʵ��
 */
void printFull(int x , int y);

/**
 * ��ӡ�հ�
 */
void printEmpty(int x , int y);

/**
 * ������ƶ���ĳ��λ��
 */
void gotoxy(int x , int y);


// �����ߵ���λ
int clickControl();

/**
 * �Ե�ʳ��
 */
int eatFoot(int x, int y);


/**
 * �ƶ�
 */
void move(char control);

/**
 * �ı��ߵ�״̬
 */
void change(int x,int y);

/**
 * ��Ϸ����
 */
void gameOver();

#endif /* SRC_GAME_H_ */
