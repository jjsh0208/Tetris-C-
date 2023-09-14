#include "tetris.h"

int CrushCheak(int x_obj, int y_obj,int r_obj) {	//�ӽ÷� ����� �̵��� ��ġ�� �̵��غ��� �浹�� �ִ��� üũ

	int temp_rotation = block_rotation + r_obj;	//�ӽ� ȸ������ �����ؼ� ���� ȸ�� ���� �־��ش�.
	// ���� ȸ���� + �߰�ȸ����
	if (temp_rotation > 3) {	//ȸ������ 3�̻����� �Ѿ�� 0���� �ʱ�ȭ
		temp_rotation = 0;	//�迭���� ȸ������� �� 4���� �迭���� 0 ~ 3 ���� �̱⶧���̴�.
	}

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			if (block[block_type][temp_rotation][y][x] == 1 &&
				board[block_Y + y_obj + y][block_X + x_obj + x] > 3) {
				return FALSE; //��ġ�� �κ��� ������ FALSE ����
			}
		}
	}
	return TRUE;	//��ġ�� �κ��� ������ TRUE ����

//if���� �ٽ��Դϴ�
//enum MyEnum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5 };	
//0 = ����� , 1 = ���� �����̰� �ִ� �� , 2 = ���� ���� ����, 3 = �׸��� ���, 4 = ��, 5 = ������ ���
//���� 1. �迭�ȿ� �ִ� ���� 1(����� ����) �̸鼭
//���� 2. ���Ӻ��� �� �Է¹��� ����ŭ �����̰�, ���� �����ϴ� ��ġ�� ��(4) �̳� ������ ���(5)�� ��� FALSE(��ħ)����
// ��ɵǴ� ĭ�� �ϳ��� ������ (TRUE) ��ȯ
}

void LineCheak(void) {	//������ üũ�ϰ� ���� ����

	int k;	//������ �ı��� y��ġ�� �����ϴ� ��
	int block_linecheak;	//10���� ���� ä�������� üũ�ϴ� �뵵�� ����

	for (int y = board_SIZE_Y - 2; y > 2;) {	//(Ž��) y�̵� ��
	
		block_linecheak = 0;	//���� y�ٷ� �Ѿ�� �� ���� 0���� �ʱ�ȭ

		for (int x = 1; x < board_SIZE_X - 1; x++){	// (Ž��) X �̵�
			if (board[y][x] == FBLOCK) {	//�ش� ��ġ�� fix�� ��� ��������
				block_linecheak++;	//�� ����
			}
		}
		if (block_linecheak == board_SIZE_X - 2){	//�ش� ���� �ı��ؾ��ϴ� �����̸�
			deleteline_total++;	//�����ı� ��Ż + 1
			deleteline_combo++;	//�����ı� ���� + 1
			for (k = y; k > 1; k--) {	//K�� ���� Y���� �Ѱ��ְ�, K�� 1�̵Ǹ� ����
				for (int i = 1; i < board_SIZE_X - 1 ; i++){
					if (board[k - 1][i] != OVERLINE) {	//��ĭ�� ��� ������
						board[k][i] = board[k - 1][i];	//����� ��� ��ĭ �� �����ش�.
					}

					if (board[k - 1][i] == OVERLINE){	//��ĭ ���� �ִ� ����� ���������̸� EMPTY�� �־��ش�.
						board[k][i] = EMPTY;
					}
				}
			}
		}
		else{
			y--;	//������
		}
	}
	score_maneger(); // ���ھ� ����
	deleteline_combo = 0;	//�޺� �ʱ�ȭ
}