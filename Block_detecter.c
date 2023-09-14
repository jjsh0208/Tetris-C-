#include "tetris.h"

int CrushCheak(int x_obj, int y_obj,int r_obj) {	//임시로 블록이 이동할 위치에 이동해보고 충돌이 있는지 체크

	int temp_rotation = block_rotation + r_obj;	//임시 회전값을 선언해서 현재 회전 값을 넣어준다.
	// 현재 회전값 + 추가회전값
	if (temp_rotation > 3) {	//회전값이 3이상으로 넘어가면 0으로 초기화
		temp_rotation = 0;	//배열에서 회전모양은 각 4개씩 배열에서 0 ~ 3 까지 이기때문이다.
	}

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			if (block[block_type][temp_rotation][y][x] == 1 &&
				board[block_Y + y_obj + y][block_X + x_obj + x] > 3) {
				return FALSE; //겹치는 부분이 있으면 FALSE 리턴
			}
		}
	}
	return TRUE;	//겹치는 부분이 없으면 TRUE 리턴

//if문이 핵심입니다
//enum MyEnum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };	
//0 = 빈공간 , 1 = 현재 움직이고 있는 블럭 , 2 = 게임 오버 라인, 3 = 그림자 블록, 4 = 벽, 5 = 고정된 블록
//조건 1. 배열안에 있는 값이 1(블록이 있음) 이면서
//조건 2. 게임보드 내 입력받은 값만큼 움직이고, 블럭이 들어가야하는 위치에 벽(4) 이나 고정된 블록(5)일 경우 FALSE(겹침)리턴
// 충될되는 칸이 하나도 없으면 (TRUE) 반환
}

void LineCheak(void) {	//라인을 체크하고 줄을 삭제

	int k;	//라인이 파괴된 y위치를 저장하는 값
	int block_linecheak;	//10개가 전부 채워졌는지 체크하는 용도의 변수

	for (int y = board_SIZE_Y - 2; y > 2;) {	//(탐색) y이동 ▲
	
		block_linecheak = 0;	//다음 y줄로 넘어올 때 마다 0으로 초기화

		for (int x = 1; x < board_SIZE_X - 1; x++){	// (탐색) X 이동
			if (board[y][x] == FBLOCK) {	//해당 위치에 fix된 블록 이있으면
				block_linecheak++;	//값 증가
			}
		}
		if (block_linecheak == board_SIZE_X - 2){	//해당 줄이 파괴해야하는 라인이면
			deleteline_total++;	//라인파괴 토탈 + 1
			deleteline_combo++;	//라인파괴 점수 + 1
			for (k = y; k > 1; k--) {	//K에 현재 Y값을 넘겨주고, K가 1이되면 종료
				for (int i = 1; i < board_SIZE_X - 1 ; i++){
					if (board[k - 1][i] != OVERLINE) {	//한칸씩 모두 내려줌
						board[k][i] = board[k - 1][i];	//블록을 모두 한칸 씩 내려준다.
					}

					if (board[k - 1][i] == OVERLINE){	//한칸 위에 있는 블록이 오버라인이면 EMPTY를 넣어준다.
						board[k][i] = EMPTY;
					}
				}
			}
		}
		else{
			y--;	//다음줄
		}
	}
	score_maneger(); // 스코어 지급
	deleteline_combo = 0;	//콤보 초기화
}