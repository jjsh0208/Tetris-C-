#include "tetris.h"

void block_move(int inputX, int inputY, int input_lotation) {	//블록을 이동 및 회전시킵니다.
	
	int temp_rotation = block_rotation + input_lotation;	//임시 회전값을 선언해서 현재 회전 값을 넣어준다.
															// 현재 회전값 + 추가회전값
	if (temp_rotation > 3){	//회전값이 3이상으로 넘어가면 0으로 초기화
		temp_rotation = 0;	//배열에서 회전모양은 각 4개씩 배열에서 0 ~ 3 까지 이기때문이다.
	}
	
	for (int y = 0; y < 4; y++) { //원래 값 지우기
		for (int x = 0; x < 4; x++) {
			if (block[block_type][block_rotation][y][x] == 1) {	//블록의 현재 위치에 있는 값을 비워준다.

				board[block_Y + y][block_X + x] = EMPTY;	//대입한 값은 공백

			}
		}
	}

	for (int y = 0; y < 4; y++) { //다시 값 넣기        // 하나 밑의 칸으로 넣어준다
		for (int x = 0; x < 4; x++) {
			if (block[block_type][temp_rotation][y][x] == 1) {	// 블록의 값이 있으면 (바뀐 회전 모양)

				board[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;	//이동된 칸에 블록을 그린다.
				//원래 회전값 + 추가 회전값 
			}
		}
	}
	//원래 회전값을 회전값 + 추가 회전값으로 바꿔준다.
	block_X = block_X + inputX; //입력받은 x 값 만큼 이동
	block_Y = block_Y + inputY;	//입력받은 y 값 만큼 이동
	block_rotation = temp_rotation;	//현재의 로테이션 값에 넣어준다

}

void Blockprize(void) {	//블록을 픽스 시킵니다 (고정)
	for (int y = 0; y < board_SIZE_Y; y++) {	//보드의 y축 만큼		(24)
		for (int x = 0; x < board_SIZE_X; x++) {	//보드의 x축 만큼 (12)
			if (board[y][x] == MBLOCK) {	//블록이 MBLOCK이면 (움직이는 블록)
				board[y][x] = FBLOCK;		//고정된 블록으로 바꿔준다.
			}
		}
	}

	flag_neednewblock = 1;	//(중요) 새로운 블록이 필요하기 때문에 1로 바꿔준다.
	
	return;
}

void AutoDrop(void) {	//블록 자동 하강 (블록이 바닥에 닿자마자 픽스되지않게 틈을 만듬)

	if (CrushCheak(0,1,0) == TRUE && flag_crush == 0){	//이번에 충돌이 없고 , 이전 사이클에서 충돌이 없으면 
		block_move(0, 1, 0);	//블록 한칸 하강 (평상시 상태)
	}
	else if (CrushCheak(0,1,0) == TRUE && flag_crush == 1){	//이번에 충돌이 없고 , 이전 사이클에서는 충돌이 있으면
		flag_crush = 0;	//충돌 플래그를 꺼줍니다 (아래쪽에 충돌시켰다가 좌우로 이동이 가능하게함)
	}
	else if (CrushCheak(0, 1, 0) == FALSE && flag_crush == 0) {	//이번에 충돌이 있고 , 이전 사이클에서는 충돌이 없으면
		flag_crush = 1;	//충돌 플래그를 켜줍니다.
	}
	else if (CrushCheak(0,1,0) == FALSE && flag_crush == 1){	//이번에 충돌이 있고 , 전 사이클에서도 충돌이 있으면
		Blockprize();	//블록을 고정시킵니다.
		LineCheak();	//라인을 체크하고 파괴합니다.
		flag_crush = 0;	//충돌 플래그 초기화
	}
}

void keyboard_controller(void) {
	//_kbhit() => 키보드가 입력되었는지 체크하는 함수
	//_getch() => 키보드로 입력은받고 출력은 하지않는다.
	int key;
	if (_kbhit()){	//키보드로 입력을 받았다면	//_kbhit 키보드로 입력받는 함수
		key = _getch();
		if (key == 224){  //받은키가 방향키라면  //방향키는 확장키라서 2개의 값을 가지고있다 224 다음 고유의 숫자 
			key = _getch();	//한번 더 받는다.
			switch (key) {
			case LEFT:	//왼쪽 방향키
				if (CrushCheak(-1, 0, 0) == TRUE) {	//x방향으로 -1 만큼 이동했을 때 충돌하지않을 시
					block_move(-1, 0, 0);			//왼쪽으로 한칸 // X축을 -1 만큼 이동
					break;
				}

			case RIGHT:	//오른쪽 방향키
				if (CrushCheak(1, 0, 0) == TRUE) {	//x방향으로 1 만큼 이동했을 때 충돌하지않을 시
					block_move(1, 0, 0);		//오른쪽으로 한칸	// X축을 1 만큼 이동
					break;
				}

			case DOWN:	//아랫쪽 방향키
				if (CrushCheak(0, 1, 0) == TRUE) {	//y방향으로 1 만큼 이동했을 때 충돌하지않을 시
					block_move(0, 1, 0);		//오른쪽으로 한칸	// Y축을 1만큼 이동
					break;
				}

			case UP:	//벽에 붙어서도 회전이 가능
				for (int rotatemove_y = 0; ; rotatemove_y--) {//해당 y좌표에서 충돌 시 위로 올려준다
					for (int rotatemove_x = 0; rotatemove_x < 3; rotatemove_x++) {
						//벽에 붙어 회전 시 가장 많이 충돌 할 수 있는 가로 칸이 최대 2개 (막대블록)
						for (int n = 0; n < 2; n++) {
							//x쪽 보정으로만 하게되면 왼쪽은 보정이 되지않음 -1을 곱해서 부호를 계속 바꿀 수 있게 해준다
							rotatemove_x *= -1;
							if (CrushCheak(rotatemove_x, rotatemove_y, 1) == TRUE) {
								block_move(rotatemove_x, rotatemove_y, 1);
								return;
							}
						}
					}
				}
			}
		}
		else{	//받은 키가 방향키가 아니라면
			switch (key){
				case SPACE:
					flag_harddrop = 1; //스페이스 입력시 하드드롭을 켜준다.
					while (flag_crush != 1){//충돌이 일어날 때까지
						AutoDrop();// 블록 자동하강
					}
					break;
				
				case 'z':	//z,Z 홀드기능 사용
				case 'Z':
					if (hold_type == 0){ //홀드된 블록이 없고 홀드를 사용 가능한 경우
						block_type_hlod = block_type;	//현재 블록의 타입을 홀드한다
									
						MBlockDeleter();				//현재 블록을 지워준다.
						NextBlockPush();				//다음블록으로 푸쉬해준다.
						PrintNextBlock();				//다음에 나올 푸쉬된 블록을 보여준다.
						PrintHoldBlock();				//홀드된 블록을 보여준다

						
						flag_hlod = 1;					//홀드 플래그를 켜준다
						hold_type = 1;					//홀드 타입을 1로 교체
					}
					else if (hold_type == 1) {	//홀드된 블록이 있고 교체해야하는 경우
						int temp;
						//현재블록과 홀드된 블록을 교체
						temp = block_type_hlod;						
						block_type_hlod = block_type;
						block_type = temp;
						MBlockDeleter();				//현재 블록을 지워준다.
						PrintNextBlock();				//다음에 나올 블록을 보여준다.
						PrintHoldBlock();				//홀드된 블록을 보여준다.
				
						flag_hlod = 1;					//홀드 플래그를 켜준다
						hold_type = 2;					//홀드 타입을 2로 교체
					}
					else if (hold_type == 2) {	//홀드된 블록이 있고 교체해야하는 경우
						
						int temp;
						//현재블록과 홀드된 블록을 교체
						temp = block_type_hlod;
						block_type_hlod = block_type;
						block_type = temp;
						
						MBlockDeleter();				//현재 블록을 지워준다.
						PrintNextBlock();				//다음에 나올 블록을 보여준다.
						PrintHoldBlock();				//홀드된 블록을 보여준다.
						
						flag_hlod = 1;					//홀드 플래그를 켜준다.
						hold_type = 1;					//홀드 타입을 다시 1로 교체
					}
					//홀드 타입을 1,2로 계속 교체해가면서 홀드 된 블록을 교체해 사용할 수 있다
					else{
						break;
					}
					break;	
			}
		}
	}
	return;	//키보드로 입력받지 않았다면 나감
}