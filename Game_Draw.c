#include "tetris.h"

void Reset_game_board(void) {
	//tetris.h 
	//#define board_SIZE_X 12	
	//#define board_SIZE_Y 24	
	//int board[board_SIZE_Y][board_SIZE_X];
	//���Ӻ���� ���� 24 ���� 12 �������� 2���� �迭�� ������ش�

	for (int y = 0; y < board_SIZE_Y; y++) {
		for (int x = 0; x < board_SIZE_X; x++) {
			board[y][x] = EMPTY;		//���������� ���� EMPTY = 0 (�����)�� ���忡 ���δ� �־��ش�.
		}
	}
	for (int y = 0; y < board_SIZE_Y; y++) {			
		for (int x = 0; x < board_SIZE_X; x++) {		//���� ���������� ����
			if (x == 0 || x == board_SIZE_X - 1) {	    // ���� ���ʰ� ���� �ʿ� WALL�� �־��ش� WALL�� ���� 4 
				board[y][x] = WALL;
			}
			if (y == board_SIZE_Y - 1) {	// �ٴ��� ����� ���� Y�� board_SIZE_Y - 1(14 - 1) �� ���� ������ WALL�� �־��ش�
				board[y][x] = WALL;
			}
			if (y == 2 && x != 0 && x != board_SIZE_X - 1) {
				board[y][x] = OVERLINE;						//OVERLINE�� ���� 2
				// //�迭�� 3�� ° ���κ��� ù��° ĭ�� ������ ĭ�� ������ �� �ٿ� OVERLINE�� �־��ش�
			}
		}
	}
}


void Print_board(void) {
	for (int y = 0; y < board_SIZE_Y; y++) {	//������ y�� ��ŭ //24 ��ŭ
		for (int x = 0; x < board_SIZE_X; x++) {//������ x�� ��ŭ //12 ��ŭ
			
			switch (board[y][x]) {
			case EMPTY:		//�ش� ĭ�� ������̸�   
				gotoxy(x + 13, y +2);
				printf("  ");	//������ �����̽��� 2������ 2ĭ�� ����ش�
				break;			//��(���)�� �ݰ��� �ƴ� ���۹��� �̱⿡ 2ĭ�� ����ش�

			case MBLOCK:	//�����̰� �ִ� ���
				gotoxy(x + 13, y + 2);
				printf("��");	
				break;
			
			case SBLOCK:	//�׸��ں��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(x + 13, y + 2);
				printf("��");
				
				break;

			case OVERLINE:	//�ش� ĭ�� ��������
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				gotoxy(x + 13, y + 2);
				printf(".");
				break;

			case WALL:		//�ش�ĭ�� ���̶�� (�ٴ�����)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(x + 13, y + 2);
				printf("��");
				break;

			case FBLOCK:	//�ش�ĭ�� ������ ����̸�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				gotoxy(x + 13, y + 2);
				printf("��");
				break;
			}
			if (y == 2 && x != 0 && x != board_SIZE_X - 1 && board[y][x] == EMPTY) {
				//y�� 2�� ���ο� ������� ���ʺ��� �����ʱ��� ������ ����� ���������� �ٽ� �׸���
				board[y][x] = OVERLINE;  //���������� �������� �ٽ� �׷��ֱ� 
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}

void PrintHoldBlock(void) {		//Ȧ��� ����� ǥ���ϴ� �Լ�
	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			if (block[block_type_hlod][0][y][x] == 1){	//���� Ȧ��� Ÿ���� ��� ����� ǥ��
				gotoxy(4 + x, 4 + y);
				printf("��");
			}
			else{
				gotoxy(4 + x, 4 + y);					//���� �� ���� ǥ��
				printf("  ");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
}

void PrintNextBlock(void) {	//������ ���� ����� ȭ�鿡 ǥ��

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++) {
			if (block[block_typeN1][0][y][x] == 1){	//1�� ° ��������� Ÿ���� ȭ�鿡 ǥ��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				gotoxy(30 + x, 4 + y);
				printf("��");
			}
			else{
				gotoxy(30 + x, 4 + y);				//����� ����� �ƴ� ������ ���� ǥ��
				printf("  ");
				
			}
			if (block[block_typeN2][0][y][x] == 1) {//2�� ° ��������� Ÿ���� ȭ�鿡 ǥ��
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				gotoxy(30 + x, 9 + y);
				printf("��");
			}
			else {
				gotoxy(30 + x, 9 + y);				//����� ����� �ƴ� ������ ���� ǥ��
				printf("  ");
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}

void printGameOver(void) {
	int count = 0;
	//���ӿ��� ������ �����Ǿ��� �� printGameOver �Լ� �ߵ�

	for (int y = 0; y < board_SIZE_Y - 1; y++) {
		for (int x = 1; x < board_SIZE_X - 1; x++) {
			board[y][x] = EMPTY;		//���������� ���� EMPTY = 0 (�����)�� ���δ� �־��ش�.
		}
	}

	Print_board(); // �ٽ� ����� ���� ȭ�� ���

	gotoxy(16, 10);
	printf("%s �� \n", user_ID);				//�α����� ������ ID
	gotoxy(15, 12);
	printf("���� ���� : %d\n", score);			//�̹� ������ ���� 
	gotoxy(15, 14);
	printf("�ְ� ���� : %s\n", user_best_score);//������ ��ϵ� �ְ� ����

	//Game Over !! ������ �����Ÿ��� �ϱ����� �ݺ����ȿ��� �����̸� �ְ�
	//count�� Ȧ�� �� ��쿡�� ������ �߰� ¦���� ��쿡�� ������ �����
	//Ű���忡�� �Է��� ���� �� �ݺ������� ���
	while (1) {
		count++;
		if (_kbhit()) {	
			break;
		}
		if (count % 2 == 0) {
			gotoxy(16, 5);
			printf("                ");	//���ӿ���
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(15, 7);
			printf("                 ");

		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(16, 5);
			printf(" Game Over!!");	//���ӿ���
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			gotoxy(15, 7);
			printf("Press Any Butoon");
		}
			Sleep(600);	// ���� ǥ�ø� ���� ������//�� �� �� ����
	}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		flag_game_end = 1;
}


void UI_Login(void) {	//�α��� ȭ�� UI
	int x1 = 15;
	int y1 = 7;

	gotoxy(x1, y1++);
	printf("      ����  Login ����\n");
	gotoxy(x1, y1++);
	printf("��������������������������������������������������");
	gotoxy(x1, y1++);
	printf("                        ��");
	gotoxy(x1, y1++);
	printf("��������������������������������������������������");
	gotoxy(x1, y1++);
	printf("                        ��");
	gotoxy(x1, y1++);
	printf("��������������������������������������������������");
}

void UI_SingUp(void) {	//ȸ������ȭ�� UI
	int x1 = 15;
	int y1 = 7;

	gotoxy(x1, y1++);
	printf("      ����  SingUP ����\n");
	gotoxy(x1, y1++);
	printf("��������������������������������������������������");
	gotoxy(x1, y1++ );
	printf("                        ��");
	gotoxy(x1, y1++ );
	printf("��������������������������������������������������");
	gotoxy(x1, y1++);
	printf("                        ��");
	gotoxy(x1, y1++ );
	printf("��������������������������������������������������");
}

void UI_Draw(void) {	//����ȭ�� UI
	int x1 = 29;
	int y1 = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	gotoxy(x1, y1++);
	printf("   N E X T  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(x1, y1++);
	printf("������������������������");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("������������������������");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("��          ��");
	gotoxy(x1, y1++);
	printf("������������������������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	int x2 = 3;
	int y2 = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(x2, y2++);
	printf("   H O L D  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(x2, y2++);
	printf("������������������������");
	gotoxy(x2, y2++);
	printf("��          ��");
	gotoxy(x2, y2++);
	printf("��          ��");
	gotoxy(x2, y2++);
	printf("��          ��");
	gotoxy(x2, y2++);
	printf("��          ��");
	gotoxy(x2, y2++);
	printf("������������������������");

	int x3 = 1;
	int y3 = 10;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	gotoxy(x3, y3++);
	printf("   - How To PLAY -   ");
	y3++;

	gotoxy(x3, y3++);
	printf("   [����]  : MOVE  ");
	y3++;
	gotoxy(x3, y3++);
	printf("   [��]    : RATATE");
	y3++;
	gotoxy(x3, y3++);
	printf("   [��]    : SOFT DROP");
	y3++;
	gotoxy(x3, y3++);
	printf("   [SPC]   : HARD DROP");
	y3++;
	gotoxy(x3, y3++);
	printf("   [Z]     :      HOLD");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

}



int UI_intro(void) {	//������ ��Ʈ�θ� �����ְ� �޴��� �����ϴ� �Լ�
	int num = 0;
	printf("                                                                                \n");
	printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�\n");
	printf("                                                                                \n");
	printf("             �ââ�   �ââ�   �ââ�   �ââ�    �ââ�   �ââ�               \n");
	printf("               ��     ��         ��     ��   ��     ��     ��         	  \n");
	printf("               ��     �ââ�     ��     �ââ�      ��     �ââ�               \n");
	printf("               ��     ��         ��     ��   ��     ��         ��          \n");
	printf("               ��     �ââ�     ��     ��   ��   �ââ�   �ââ�                \n");
	printf("                                                                                \n");
	printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�\n");
	printf("                                                                                \n");
	printf("                                                               By.������        \n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n"); 
	if (user_ID != NULL){
		gotoxy(17, 15);
		printf("1. ���ӽ���\n");
	}
	else {
		gotoxy(15, 15);
		printf("-- �α��� ���ּ��� --\n");
	}
	gotoxy(17, 17);
	printf("2. �α���  \n");
	gotoxy(17, 19);
	printf("3. �α׾ƿ�  \n");
	gotoxy(17, 21);
	printf("4. ȸ������\n");
	gotoxy(17, 23);
	printf("5. ��    ŷ\n");
	gotoxy(17, 25);
	printf("6. ��������\n");
	gotoxy(17, 27);
	printf("�Է� : ");
	scanf("%d", &num);

	return num;
}