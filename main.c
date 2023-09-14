#include "tetris.h"

int main(void) {
	int menu = 0;
	
	setConsole();	//콘솔창 세팅
	srand((unsigned)time(NULL));	//현재 시간을 시드로 받습니다.
	
	while (1){
		menu = UI_intro();	//게임의 인트로 함수 메뉴 값을 받아와서 1.게임시작, 2.회원가입, 3.랭킹, 4.게임종료 를 실행

		if (menu == 1 && user_ID != NULL) {	//1. 게임시작 (로그인이 되었을 때만 게임시작 가능)
			game();
		}	   
		else if (menu == 2){	//2. 로그인
			system("cls");
			Login();			//로그인 함수
		}
		else if (menu == 3 && user_ID != NULL) { //3. 로그아웃
			system("cls");
			user_ID = NULL;		//저장된 user_ID의 값을 지움
		}
		else if (menu == 4) {	//3. 회원가입
			system("cls");
			Sing_up();			//회원가입 함수
		}
		else if (menu == 5) {	//4. 랭킹
			system("cls");
			Ranking();			//랭킹을 보여주는 함수
		}
		else if (menu == 6) {	//5. 게임종료
			exit(0);
		}
		else{	
			system("cls");
			continue;
		}
	}
	return 0;
}