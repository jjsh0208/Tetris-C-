#include "tetris.h"

void block_move(int inputX, int inputY, int input_lotation) {	//����� �̵� �� ȸ����ŵ�ϴ�.
	
	int temp_rotation = block_rotation + input_lotation;	//�ӽ� ȸ������ �����ؼ� ���� ȸ�� ���� �־��ش�.
															// ���� ȸ���� + �߰�ȸ����
	if (temp_rotation > 3){	//ȸ������ 3�̻����� �Ѿ�� 0���� �ʱ�ȭ
		temp_rotation = 0;	//�迭���� ȸ������� �� 4���� �迭���� 0 ~ 3 ���� �̱⶧���̴�.
	}
	
	for (int y = 0; y < 4; y++) { //���� �� �����
		for (int x = 0; x < 4; x++) {
			if (block[block_type][block_rotation][y][x] == 1) {	//����� ���� ��ġ�� �ִ� ���� ����ش�.

				board[block_Y + y][block_X + x] = EMPTY;	//������ ���� ����

			}
		}
	}

	for (int y = 0; y < 4; y++) { //�ٽ� �� �ֱ�        // �ϳ� ���� ĭ���� �־��ش�
		for (int x = 0; x < 4; x++) {
			if (block[block_type][temp_rotation][y][x] == 1) {	// ����� ���� ������ (�ٲ� ȸ�� ���)

				board[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;	//�̵��� ĭ�� ����� �׸���.
				//���� ȸ���� + �߰� ȸ���� 
			}
		}
	}
	//���� ȸ������ ȸ���� + �߰� ȸ�������� �ٲ��ش�.
	block_X = block_X + inputX; //�Է¹��� x �� ��ŭ �̵�
	block_Y = block_Y + inputY;	//�Է¹��� y �� ��ŭ �̵�
	block_rotation = temp_rotation;	//������ �����̼� ���� �־��ش�

}

void Blockprize(void) {	//����� �Ƚ� ��ŵ�ϴ� (����)
	for (int y = 0; y < board_SIZE_Y; y++) {	//������ y�� ��ŭ		(24)
		for (int x = 0; x < board_SIZE_X; x++) {	//������ x�� ��ŭ (12)
			if (board[y][x] == MBLOCK) {	//����� MBLOCK�̸� (�����̴� ���)
				board[y][x] = FBLOCK;		//������ ������� �ٲ��ش�.
			}
		}
	}

	flag_neednewblock = 1;	//(�߿�) ���ο� ����� �ʿ��ϱ� ������ 1�� �ٲ��ش�.
	
	return;
}

void AutoDrop(void) {	//��� �ڵ� �ϰ� (����� �ٴڿ� ���ڸ��� �Ƚ������ʰ� ƴ�� ����)

	if (CrushCheak(0,1,0) == TRUE && flag_crush == 0){	//�̹��� �浹�� ���� , ���� ����Ŭ���� �浹�� ������ 
		block_move(0, 1, 0);	//��� ��ĭ �ϰ� (���� ����)
	}
	else if (CrushCheak(0,1,0) == TRUE && flag_crush == 1){	//�̹��� �浹�� ���� , ���� ����Ŭ������ �浹�� ������
		flag_crush = 0;	//�浹 �÷��׸� ���ݴϴ� (�Ʒ��ʿ� �浹���״ٰ� �¿�� �̵��� �����ϰ���)
	}
	else if (CrushCheak(0, 1, 0) == FALSE && flag_crush == 0) {	//�̹��� �浹�� �ְ� , ���� ����Ŭ������ �浹�� ������
		flag_crush = 1;	//�浹 �÷��׸� ���ݴϴ�.
	}
	else if (CrushCheak(0,1,0) == FALSE && flag_crush == 1){	//�̹��� �浹�� �ְ� , �� ����Ŭ������ �浹�� ������
		Blockprize();	//����� ������ŵ�ϴ�.
		LineCheak();	//������ üũ�ϰ� �ı��մϴ�.
		flag_crush = 0;	//�浹 �÷��� �ʱ�ȭ
	}
}

void keyboard_controller(void) {
	//_kbhit() => Ű���尡 �ԷµǾ����� üũ�ϴ� �Լ�
	//_getch() => Ű����� �Է����ް� ����� �����ʴ´�.
	int key;
	if (_kbhit()){	//Ű����� �Է��� �޾Ҵٸ�	//_kbhit Ű����� �Է¹޴� �Լ�
		key = _getch();
		if (key == 224){  //����Ű�� ����Ű���  //����Ű�� Ȯ��Ű�� 2���� ���� �������ִ� 224 ���� ������ ���� 
			key = _getch();	//�ѹ� �� �޴´�.
			switch (key) {
			case LEFT:	//���� ����Ű
				if (CrushCheak(-1, 0, 0) == TRUE) {	//x�������� -1 ��ŭ �̵����� �� �浹�������� ��
					block_move(-1, 0, 0);			//�������� ��ĭ // X���� -1 ��ŭ �̵�
					break;
				}

			case RIGHT:	//������ ����Ű
				if (CrushCheak(1, 0, 0) == TRUE) {	//x�������� 1 ��ŭ �̵����� �� �浹�������� ��
					block_move(1, 0, 0);		//���������� ��ĭ	// X���� 1 ��ŭ �̵�
					break;
				}

			case DOWN:	//�Ʒ��� ����Ű
				if (CrushCheak(0, 1, 0) == TRUE) {	//y�������� 1 ��ŭ �̵����� �� �浹�������� ��
					block_move(0, 1, 0);		//���������� ��ĭ	// Y���� 1��ŭ �̵�
					break;
				}

			case UP:	//���� �پ�� ȸ���� ����
				for (int rotatemove_y = 0; ; rotatemove_y--) {//�ش� y��ǥ���� �浹 �� ���� �÷��ش�
					for (int rotatemove_x = 0; rotatemove_x < 3; rotatemove_x++) {
						//���� �پ� ȸ�� �� ���� ���� �浹 �� �� �ִ� ���� ĭ�� �ִ� 2�� (������)
						for (int n = 0; n < 2; n++) {
							//x�� �������θ� �ϰԵǸ� ������ ������ �������� -1�� ���ؼ� ��ȣ�� ��� �ٲ� �� �ְ� ���ش�
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
		else{	//���� Ű�� ����Ű�� �ƴ϶��
			switch (key){
				case SPACE:
					flag_harddrop = 1; //�����̽� �Է½� �ϵ����� ���ش�.
					while (flag_crush != 1){//�浹�� �Ͼ ������
						AutoDrop();// ��� �ڵ��ϰ�
					}
					break;
				
				case 'z':	//z,Z Ȧ���� ���
				case 'Z':
					if (hold_type == 0){ //Ȧ��� ����� ���� Ȧ�带 ��� ������ ���
						block_type_hlod = block_type;	//���� ����� Ÿ���� Ȧ���Ѵ�
									
						MBlockDeleter();				//���� ����� �����ش�.
						NextBlockPush();				//����������� Ǫ�����ش�.
						PrintNextBlock();				//������ ���� Ǫ���� ����� �����ش�.
						PrintHoldBlock();				//Ȧ��� ����� �����ش�

						
						flag_hlod = 1;					//Ȧ�� �÷��׸� ���ش�
						hold_type = 1;					//Ȧ�� Ÿ���� 1�� ��ü
					}
					else if (hold_type == 1) {	//Ȧ��� ����� �ְ� ��ü�ؾ��ϴ� ���
						int temp;
						//�����ϰ� Ȧ��� ����� ��ü
						temp = block_type_hlod;						
						block_type_hlod = block_type;
						block_type = temp;
						MBlockDeleter();				//���� ����� �����ش�.
						PrintNextBlock();				//������ ���� ����� �����ش�.
						PrintHoldBlock();				//Ȧ��� ����� �����ش�.
				
						flag_hlod = 1;					//Ȧ�� �÷��׸� ���ش�
						hold_type = 2;					//Ȧ�� Ÿ���� 2�� ��ü
					}
					else if (hold_type == 2) {	//Ȧ��� ����� �ְ� ��ü�ؾ��ϴ� ���
						
						int temp;
						//�����ϰ� Ȧ��� ����� ��ü
						temp = block_type_hlod;
						block_type_hlod = block_type;
						block_type = temp;
						
						MBlockDeleter();				//���� ����� �����ش�.
						PrintNextBlock();				//������ ���� ����� �����ش�.
						PrintHoldBlock();				//Ȧ��� ����� �����ش�.
						
						flag_hlod = 1;					//Ȧ�� �÷��׸� ���ش�.
						hold_type = 1;					//Ȧ�� Ÿ���� �ٽ� 1�� ��ü
					}
					//Ȧ�� Ÿ���� 1,2�� ��� ��ü�ذ��鼭 Ȧ�� �� ����� ��ü�� ����� �� �ִ�
					else{
						break;
					}
					break;	
			}
		}
	}
	return;	//Ű����� �Է¹��� �ʾҴٸ� ����
}