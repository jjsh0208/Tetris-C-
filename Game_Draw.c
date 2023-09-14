#include "tetris.h"

void Reset_game_board(void) {
	//tetris.h 
	//#define board_SIZE_X 12	
	//#define board_SIZE_Y 24	
	//int board[board_SIZE_Y][board_SIZE_X];
	//게임보드는 세로 24 가로 12 사이즈의 2차원 배열로 만들어준다

	for (int y = 0; y < board_SIZE_Y; y++) {
		for (int x = 0; x < board_SIZE_X; x++) {
			board[y][x] = EMPTY;		//열거형으로 지정 EMPTY = 0 (빈공간)을 보드에 전부다 넣어준다.
		}
	}
	for (int y = 0; y < board_SIZE_Y; y++) {			
		for (int x = 0; x < board_SIZE_X; x++) {		//벽과 오버라인을 생성
			if (x == 0 || x == board_SIZE_X - 1) {	    // 가장 왼쪽과 오른 쪽에 WALL에 넣어준다 WALL의 값은 4 
				board[y][x] = WALL;
			}
			if (y == board_SIZE_Y - 1) {	// 바닥을 만들기 위해 Y에 board_SIZE_Y - 1(14 - 1) 과 같은 라인의 WALL을 넣어준다
				board[y][x] = WALL;
			}
			if (y == 2 && x != 0 && x != board_SIZE_X - 1) {
				board[y][x] = OVERLINE;						//OVERLINE의 값은 2
				// //배열상 3번 째 라인부터 첫번째 칸과 마지막 칸을 제외한 한 줄에 OVERLINE을 넣어준다
			}
		}
	}
}


void Print_board(void) {
	for (int y = 0; y < board_SIZE_Y; y++) {	//보드의 y축 만큼 //24 만큼
		for (int x = 0; x < board_SIZE_X; x++) {//보드의 x축 만큼 //12 만큼
			
			switch (board[y][x]) {
			case EMPTY:		//해당 칸이 빈공간이면   
				gotoxy(x + 13, y +2);
				printf("  ");	//공백은 스페이스바 2번으로 2칸을 띄어준다
				break;			//■(블록)은 반각이 아닌 전작문자 이기에 2칸을 띄어준다

			case MBLOCK:	//움직이고 있는 블록
				gotoxy(x + 13, y + 2);
				printf("■");	
				break;
			
			case SBLOCK:	//그림자블록
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(x + 13, y + 2);
				printf("⊙");
				
				break;

			case OVERLINE:	//해당 칸이 오버라인
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				gotoxy(x + 13, y + 2);
				printf(".");
				break;

			case WALL:		//해당칸이 벽이라면 (바닥포함)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(x + 13, y + 2);
				printf("▩");
				break;

			case FBLOCK:	//해당칸이 고정된 블록이면
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(x + 13, y + 2);
				printf("□");
				break;
			}
			if (y == 2 && x != 0 && x != board_SIZE_X - 1 && board[y][x] == EMPTY) {
				//y가 2인 라인에 보드안의 왼쪽부터 오른쪽까지 공백이 생기면 오버라인을 다시 그린다
				board[y][x] = OVERLINE;  //오버라인이 지워지면 다시 그려주기 
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}

void PrintHoldBlock(void) {		//홀드된 블록을 표시하는 함수
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			if (block[block_type_hlod][0][y][x] == 1){	//현재 홀드된 타입의 블록 모양을 표시
				gotoxy(4 + x, 4 + y);
				printf("■");
			}
			else{
				gotoxy(4 + x, 4 + y);					//없을 시 공백 표시
				printf("  ");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}

void PrintNextBlock(void) {	//다음에 나올 블록을 화면에 표시

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			if (block[block_typeN1][0][y][x] == 1){	//1번 째 다음블록의 타입을 화면에 표시
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoxy(30 + x, 4 + y);
				printf("■");
			}
			else{
				gotoxy(30 + x, 4 + y);				//블록의 모양이 아닌 곳에는 공백 표시
				printf("  ");
				
			}
			if (block[block_typeN2][0][y][x] == 1) {//2번 째 다음블록의 타입을 화면에 표시
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoxy(30 + x, 9 + y);
				printf("■");
			}
			else {
				gotoxy(30 + x, 9 + y);				//블록의 모양이 아닌 곳에는 공백 표시
				printf("  ");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}

void printGameOver(void) {
	int count = 0;
	//게임오버 조건이 만족되었을 시 printGameOver 함수 발동

	for (int y = 0; y < board_SIZE_Y - 1; y++) {
		for (int x = 1; x < board_SIZE_X - 1; x++) {
			board[y][x] = EMPTY;		//열거형으로 지정 EMPTY = 0 (빈공간)을 전부다 넣어준다.
		}
	}

	Print_board(); // 다시 비워진 보드 화면 출력

	gotoxy(16, 10);
	printf("%s 님 \n", user_ID);				//로그인한 유저의 ID
	gotoxy(15, 12);
	printf("현재 점수 : %d\n", score);			//이번 게임의 점수 
	gotoxy(15, 14);
	printf("최고 점수 : %s\n", user_best_score);//계정에 등록된 최고 점수

	//Game Over !! 문구를 깜빡거리게 하기위해 반복문안에서 딜레이를 주고
	//count가 홀수 인 경우에만 문구가 뜨고 짝수인 경우에는 문구가 사라짐
	//키보드에서 입력이 들어올 시 반복문에서 벗어남
	while (1) {
		count++;
		if (_kbhit()) {	
			break;
		}
		if (count % 2 == 0) {
			gotoxy(16, 5);
			printf("                ");	//게임오버
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(15, 7);
			printf("                 ");

		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(16, 5);
			printf(" Game Over!!");	//게임오버
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(15, 7);
			printf("Press Any Butoon");
		}
			Sleep(600);	// 문구 표시를 위해 딜레이//몇 초 간 정지
	}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		flag_game_end = 1;
}


void UI_Login(void) {	//로그인 화면 UI
	int x1 = 15;
	int y1 = 7;

	gotoxy(x1, y1++);
	printf("      ━━  Login ━━\n");
	gotoxy(x1, y1++);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(x1, y1++);
	printf("                        ┃");
	gotoxy(x1, y1++);
	printf("┣━━━━━━━━━━━━━━━━━━━━━━━┫");
	gotoxy(x1, y1++);
	printf("                        ┃");
	gotoxy(x1, y1++);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void UI_SingUp(void) {	//회원가입화면 UI
	int x1 = 15;
	int y1 = 7;

	gotoxy(x1, y1++);
	printf("      ━━  SingUP ━━\n");
	gotoxy(x1, y1++);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(x1, y1++ );
	printf("                        ┃");
	gotoxy(x1, y1++ );
	printf("┣━━━━━━━━━━━━━━━━━━━━━━━┫");
	gotoxy(x1, y1++);
	printf("                        ┃");
	gotoxy(x1, y1++ );
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void UI_Draw(void) {	//게임화면 UI
	int x1 = 29;
	int y1 = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	gotoxy(x1, y1++);
	printf("   N E X T  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(x1, y1++);
	printf("┏━━━━━━━━━━┓");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┣━━━━━━━━━━┫");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┃          ┃");
	gotoxy(x1, y1++);
	printf("┗━━━━━━━━━━┛");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	int x2 = 3;
	int y2 = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(x2, y2++);
	printf("   H O L D  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(x2, y2++);
	printf("┏━━━━━━━━━━┓");
	gotoxy(x2, y2++);
	printf("┃          ┃");
	gotoxy(x2, y2++);
	printf("┃          ┃");
	gotoxy(x2, y2++);
	printf("┃          ┃");
	gotoxy(x2, y2++);
	printf("┃          ┃");
	gotoxy(x2, y2++);
	printf("┗━━━━━━━━━━┛");

	int x3 = 1;
	int y3 = 10;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	gotoxy(x3, y3++);
	printf("   - How To PLAY -   ");
	y3++;

	gotoxy(x3, y3++);
	printf("   [◀▶]  : MOVE  ");
	y3++;
	gotoxy(x3, y3++);
	printf("   [▲]    : RATATE");
	y3++;
	gotoxy(x3, y3++);
	printf("   [▼]    : SOFT DROP");
	y3++;
	gotoxy(x3, y3++);
	printf("   [SPC]   : HARD DROP");
	y3++;
	gotoxy(x3, y3++);
	printf("   [Z]     :      HOLD");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}



int UI_intro(void) {	//게임의 인트로를 보여주고 메뉴를 선택하는 함수
	int num = 0;
	printf("                                                                                \n");
	printf("☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf("                                                                                \n");
	printf("             ▣▣▣   ▣▣▣   ▣▣▣   ▣▣▣    ▣▣▣   ▣▣▣               \n");
	printf("               ▣     ▣         ▣     ▣   ▣     ▣     ▣         	  \n");
	printf("               ▣     ▣▣▣     ▣     ▣▣▣      ▣     ▣▣▣               \n");
	printf("               ▣     ▣         ▣     ▣   ▣     ▣         ▣          \n");
	printf("               ▣     ▣▣▣     ▣     ▣   ▣   ▣▣▣   ▣▣▣                \n");
	printf("                                                                                \n");
	printf("☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf("                                                                                \n");
	printf("                                                               By.전승현        \n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n"); 
	if (user_ID != NULL){
		gotoxy(17, 15);
		printf("1. 게임시작\n");
	}
	else {
		gotoxy(15, 15);
		printf("-- 로그인 해주세요 --\n");
	}
	gotoxy(17, 17);
	printf("2. 로그인  \n");
	gotoxy(17, 19);
	printf("3. 로그아웃  \n");
	gotoxy(17, 21);
	printf("4. 회원가입\n");
	gotoxy(17, 23);
	printf("5. 랭    킹\n");
	gotoxy(17, 25);
	printf("6. 게임종료\n");
	gotoxy(17, 27);
	printf("입력 : ");
	scanf("%d", &num);

	return num;
}