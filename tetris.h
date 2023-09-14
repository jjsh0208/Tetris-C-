#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <mysql.h>

#define UP 72		//Ű���� ����Ű �Է� �� ��
#define DOWN 80		//Ű���� ����Ű �Է� �� ��
#define LEFT 75		//Ű���� ����Ű �Է� �� ��
#define RIGHT 77	//Ű���� ����Ű �Է� �� ��
#define SPACE 32	//Ű���� ����Ű �Է� �����̽��� ��
#define SHIFT 16	//Ű���� SHIFTŰ �Է� �� 
#define board_SIZE_X 12		//������ ���� ������
#define board_SIZE_Y 24		//������ ���� ������
#define TRUE 1		//�浹 ������ �� 1
#define FALSE 0		//�浹 ������ 0

#define HOST "127.0.0.1"	//ȣ��Ʈ��ȣ
#define USER "root"			//������
#define PASSWD "gusdk5540"	//�н�����
#define NAME "members"		//���̺��
#define PORT 3307			//��Ʈ��ȣ

enum MyEnum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };	//���������� ���� Ÿ���� ����
//0 = ����� , 1 = ���� �����̰� �ִ� �� , 2 = ���� ���� ����, 3 = �׸��� ���, 4 = ��, 5 = ������ ���

int board[board_SIZE_Y][board_SIZE_X]; //���带 ���������� ����, ���� 12 ���� 24�� �������ش�.
extern int block[7][4][4][4];	//extern�� �ܺ� ������ ������ �� �ְ� ���ش� ��
								//block�� ��ġ�� 3.block_maker.c

int block_X;			//���� ����� x ��ġ �� ����
int block_Y;			//���� ����� y ��ġ �� ����
int block_rotation;		//���� ����� ȸ�� ��
int block_type;			//���� ����� Ÿ�� �� (�� 7��)
int block_typeN1;		//������ ���� ��� Ÿ�� 1
int block_typeN2;		//������ ���� ��� Ÿ�� 2

int block_type_hlod;	//Ȧ��� ����� Ÿ��
int hold_type;			//Ȧ���� ���� 
int flag_hlod;			//�÷��� : Ȧ�带 ����ߴ��� üũ

int flag_neednewblock;	//�÷��� : ���ο� ����� �ʿ����� üũ�մϴ�.
int flag_crush;			//�÷��� : ��� �浹�� �Ͼ
int flag_harddrop;		//�÷��� : �ϵ����� ����
int flag_game_end;		//�÷��� : ���� ����

int deleteline_total;	//�ı��� ���� ���� 
int deleteline_combo;	//���� �ı� �� üũ
int score;				//���� ����
int best_score;			//���� �ְ� ����;
int level;				//������ ���̵� ����
int game_speed;			//����� �������� �ӵ�

char* user_ID ;			//�α����� ������ ���̵� ����
char* user_best_score;

//console.c 
void console_size(void);				//�ܼ�â�� ũ�⸦ ����
void CursorView(void);					//Ŀ���� ǥ�þ��� �ʽ��ϴ�.
void remove_scrollbar();				//�ܼ�â�� ��ũ�ѹ� ����
void setConsole(void);					//�ܼ� ���� �Լ� ����
void gotoxy(int x, int y);				//x, y ��ǥ�� �̵���Ű�� �Լ�

//Game_Draw.c
void Reset_game_board(void);			//������ ���� ��������� ����� ���� �������� �� ���� �־��ִ� �Լ�
void Print_board(void);					//������� ������ ����� ȭ�鿡 ������ִ� �Լ�
void PrintHoldBlock(void);				//Ȧ��� ����� ǥ��
void PrintNextBlock(void);				//������ ���� ��� ǥ��
void GameOverCheak(void);				//���� ���� ������ üũ�ϴ� ��Ʈ
void printGameOver(void);				//���� ���� ���� ���
void UI_Login(void);					//�α��� ȭ�� UI 
void UI_SingUp(void);					//ȸ������ ȭ�� UI
void UI_Draw(void);						//���� ȭ�� UI
int UI_intro(void);						//������ ��Ʈ�θ� �����ְ� �޴��� �����ϴ� �Լ� 

//Block_maker.c
void new_block_maker(void);				//��� ���� ��Ʈ
void DeletShadowBlock(void);			//�׸��� ��� ���� 
void MakeShadowBlock(void);				//�׸��� ��� ���� (�̸� ������ ��ġ ���� �׸��� ���)
void MBlockDeleter(void);				//���� ����� �����ִ� �Լ�

//Block_detecter.c
int CrushCheak(int x, int y, int z);	//����� �浹�� üũ	//X �̵��� , Y�̵��� , ȸ�� ��
void LineCheak(void);					//������ üũ�ϰ� �ı��ϴ� ��Ʈ

//Block_controller.c
void block_move(int x, int y, int z);	//����� �̵��ϴ� ��Ʈ	//X �̵��� , Y�̵��� , ȸ�� ��
void Blockprize();						//����� ���� �����ش�
void AutoDrop(void);					//����� �ڵ����� �ϰ������ִ� ��Ʈ
void keyboard_controller(void);			//Ű����� �Է¹޴� �Լ�

//Game_maneger.c
void score_maneger(void);				//�ı��� ��� ���� ���ھ� �ø�
void speed_maneger(void);				//�ı��� ��� ���� ���� ���� ó��
void Reset_information();				//���� �ʱ�ȭ
void print_information();				//�ؽ�Ʈ ���� ���
void NextBlockPush(void);				//  ��� Ǫ��
void GameOverCheak(void);				//���� ���� ������ üũ�ϴ� ��Ʈ
void game(void);						//���� ������ ����Ǵ� �Լ�

//Data_base.c
void Best_score(void);					//������ �ְ����� ���Ž� �����ͺ��̽� ������Ʈ
void Sing_up(void);						//ȸ������ �Լ�
void Login(void);						//�α��� �Լ�
void Ranking(void);						//��ŷ�� �����ִ� �Լ�