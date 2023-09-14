#include "tetris.h"

void game(void) {
	system("cls");
	flag_game_end = 0;
	UI_Draw();
	Reset_game_board();	//게임판 초기화합니다.
	Reset_information();//게임 정보를 초기화합니다.
	new_block_maker();	//블록을 하나 생성합니다.
	Print_board();		//게임 화면을 출력합니다.
	print_information();	//점수판 출력

	while (1) {
		if (flag_game_end == 1) {	//게임종료 플래그가 켜져있으면 게임 종료
			system("cls");
			break;
		}

		if (flag_hlod == 1) {	//홀드 플래그가 켜져있으면 꺼준다
			flag_hlod = 0;
		}

		speed_maneger();
		for (int i = 0; i < 5; i++) {		//한칸이 아래로 떨어지는 동안 5번 입력받을 수 있다.
			keyboard_controller();	//키보드로 키값을 받습니다.
			MakeShadowBlock();

			Print_board();	//게임 화면을출력합니다.	
			Sleep(game_speed);	//게임 속도	//딜레이
			DeletShadowBlock();	//그림자 블록 지워주기 

			if (flag_hlod == 1) {	//홀드 플래그 켜져있으면 해당 블록을 멈춘다
				break;
			}

			if (flag_harddrop == 1) {	//하드드롭 플래그가 켜져있으면 항상 꺼준다.
				flag_harddrop = 0;
				break;
			}
		}
		if (flag_hlod == 0) {	//홀드 플래그가 꺼져있을 때만 아래의 함수들을 실행
			AutoDrop(); //블록자동하강
			print_information();	//점수판 출력
			GameOverCheak();	//게임오버 체크

		}


		if (flag_neednewblock == 1) {	//새로운 블록 플래그가 켜져있으면 (새로운 블록이 필요하면) 
			new_block_maker();	//새로운 블록 생성
		}
	}
	return;
}


void score_maneger(void) {
	
	score += 5;	//기본점수 블록이 바닥에 닿을 시 5점 획득
	switch (deleteline_combo){
	
	case 1:	//콤보가 1일 때
		score += 50;	//50점 획득
		return;
	case 2:	//콤보가 2일 때
		score += 150;	//150점 획득
		return;
	case 3:	//콤보가 3일 때
		score += 300;	//300점 획득
		return;
	case 4:	//콤보가 4일 때
		score += 400;	//400점 회득
		return;
	default:
		return;
	}

}

void speed_maneger(void) {
	//게임의 난이도를 조절하는 함수 총 부서진 블록의 수를 확인해
	//레벨을 올리고 블록이 내려오는 속도를 빠르게한다.
	if (deleteline_total < 10) {
		level = 1;
		game_speed = 75;
		return;
	}
	else if (deleteline_total < 20){
		level = 2;
		game_speed = 45;
		return;
	}
	else if (deleteline_total < 30) {
		level = 3;
		game_speed = 35;
		return;
	}
	else if (deleteline_total < 40) {
		level = 4;
		game_speed = 30;
		return;
	}
	else if (deleteline_total < 50) {
		level = 5;
		game_speed = 25;
		return;
	}
	else if (deleteline_total < 60) {
		level = 6;
		game_speed = 20;
		return;
	}
	else if (deleteline_total < 70) {
		level = 7;
		game_speed = 15;
		return;
	}
	else if (deleteline_total < 80) {
		level = 8;
		game_speed = 10;
		return;
	}
}

void Reset_information() {	//게임 시작 시 게임 정보 초기화
	score = 0;
	deleteline_total = 0;
	level = 1;
	game_speed = 50;
	hold_type = 0;


	block_typeN1 = rand() % 7;
	block_typeN2 = rand() % 7;

}

void print_information() {	//게임의 진행 사항에 대해 화면에 표시
	
	gotoxy(28, 15);
	printf("[ USRE: %s ]", user_ID);

	gotoxy(28, 17);
	printf("[ LEVEL : %d ]", level);

	gotoxy(28, 19);
	printf("[ SCORE : %d ]", score);
	
	gotoxy(28, 21);
	printf("[ BEST SCORE : %s ]", user_best_score);
	
	gotoxy(28, 23);
	printf("[ DELETE LINE : %d ]", deleteline_total);

}

void NextBlockPush(void) {	//다음에 나올 블록들을 미리 생성해 다음 칸으로 밀어준다
	block_type = block_typeN1;
	block_typeN1 = block_typeN2;
	block_typeN2 = rand() % 7;	
}

void GameOverCheak(void) {
	
	for (int x = 1;  x < board_SIZE_X - 2;  x++){

		if (board[2][x] == FBLOCK) { // 오버라인에 고정된 블록이 있으면
			Best_score();		//종료조건 만족이 로그인한 유저의 현재점수와 최고점수를 비교해 갱신
			printGameOver();	//화면에 게임종료

			system("cls");		

			
			Reset_game_board(); // 게임보드 초기화
			Reset_information();	//게임정보 초기화

			Print_board();	//게임보드 출력
			print_information();	//게임정보 출력
		}
	}
}