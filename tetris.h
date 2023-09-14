#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <mysql.h>

#define UP 72		//키보드 방향키 입력 ↑ 값
#define DOWN 80		//키보드 방향키 입력 ↓ 값
#define LEFT 75		//키보드 방향키 입력 ← 값
#define RIGHT 77	//키보드 방향키 입력 → 값
#define SPACE 32	//키보드 방향키 입력 스페이스바 값
#define SHIFT 16	//키보드 SHIFT키 입력 값 
#define board_SIZE_X 12		//보드의 가로 사이즈
#define board_SIZE_Y 24		//보드의 세로 사이즈
#define TRUE 1		//충돌 안했을 때 1
#define FALSE 0		//충돌 했을때 0

#define HOST "127.0.0.1"	//호스트번호
#define USER "root"			//유저명
#define PASSWD "gusdk5540"	//패스워드
#define NAME "members"		//테이블명
#define PORT 3307			//포트번호

enum MyEnum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };	//열거형으로 블럭의 타입을 지정
//0 = 빈공간 , 1 = 현재 움직이고 있는 블럭 , 2 = 게임 오버 라인, 3 = 그림자 블록, 4 = 벽, 5 = 고정된 블록

int board[board_SIZE_Y][board_SIZE_X]; //보드를 전역변수로 생성, 가로 12 세로 24로 생성해준다.
extern int block[7][4][4][4];	//extern은 외부 변수를 참조할 수 있게 해준다 ★
								//block의 위치는 3.block_maker.c

int block_X;			//현재 블록의 x 위치 값 가로
int block_Y;			//현재 블록의 y 위치 값 세로
int block_rotation;		//현재 블록의 회전 값
int block_type;			//현재 블록의 타입 값 (총 7개)
int block_typeN1;		//다음에 나올 블록 타입 1
int block_typeN2;		//다음에 나올 블록 타입 2

int block_type_hlod;	//홀드된 블록의 타입
int hold_type;			//홀드의 상태 
int flag_hlod;			//플래스 : 홀드를 사용했는지 체크

int flag_neednewblock;	//플래그 : 새로운 블록이 필요한지 체크합니다.
int flag_crush;			//플래그 : 블록 충돌이 일어남
int flag_harddrop;		//플래그 : 하드드롭이 켜짐
int flag_game_end;		//플래그 : 게임 종료

int deleteline_total;	//파괴한 라인 총합 
int deleteline_combo;	//동시 파괴 수 체크
int score;				//현재 점수
int best_score;			//유저 최고 점수;
int level;				//게임의 난이도 레벨
int game_speed;			//블록이 내려오는 속도

char* user_ID ;			//로그인한 유저의 아이디를 저장
char* user_best_score;

//console.c 
void console_size(void);				//콘솔창의 크기를 조절
void CursorView(void);					//커서를 표시않지 않습니다.
void remove_scrollbar();				//콘솔창의 스크롤바 삭제
void setConsole(void);					//콘솔 세팅 함수 모음
void gotoxy(int x, int y);				//x, y 좌표로 이동시키는 함수

//Game_Draw.c
void Reset_game_board(void);			//보드의 값을 빈공간으로 만들고 벽과 오버라인 의 값을 넣어주는 함수
void Print_board(void);					//보드안의 값으로 블록을 화면에 출력해주는 함수
void PrintHoldBlock(void);				//홀드된 블록을 표시
void PrintNextBlock(void);				//다음에 나올 블록 표시
void GameOverCheak(void);				//게임 종료 조건을 체크하는 파트
void printGameOver(void);				//게임 종료 문구 출력
void UI_Login(void);					//로그인 화면 UI 
void UI_SingUp(void);					//회원가입 화면 UI
void UI_Draw(void);						//게임 화면 UI
int UI_intro(void);						//게임의 인트로를 보여주고 메뉴를 선택하는 함수 

//Block_maker.c
void new_block_maker(void);				//블록 생성 파트
void DeletShadowBlock(void);			//그림자 블록 제거 
void MakeShadowBlock(void);				//그림자 블록 생성 (미리 내려갈 위치 보는 그림자 블록)
void MBlockDeleter(void);				//현재 블록을 지워주는 함수

//Block_detecter.c
int CrushCheak(int x, int y, int z);	//블록의 충돌을 체크	//X 이동값 , Y이동값 , 회전 값
void LineCheak(void);					//라인을 체크하고 파괴하는 파트

//Block_controller.c
void block_move(int x, int y, int z);	//블록을 이동하는 파트	//X 이동값 , Y이동값 , 회전 값
void Blockprize();						//블록을 고정 시켜준다
void AutoDrop(void);					//블록을 자동으로 하강시켜주는 파트
void keyboard_controller(void);			//키보드로 입력받는 함수

//Game_maneger.c
void score_maneger(void);				//파괴된 블록 수로 스코어 올림
void speed_maneger(void);				//파괴된 블록 수로 게임 레벨 처리
void Reset_information();				//정보 초기화
void print_information();				//텍스트 관련 출력
void NextBlockPush(void);				//  블록 푸시
void GameOverCheak(void);				//게임 종료 조건을 체크하는 파트
void game(void);						//실제 게임이 실행되는 함수

//Data_base.c
void Best_score(void);					//유저의 최고점수 갱신시 데이터베이스 업데이트
void Sing_up(void);						//회원가입 함수
void Login(void);						//로그인 함수
void Ranking(void);						//랭킹을 보여주는 함수