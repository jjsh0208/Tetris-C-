#include "tetris.h"

void game(void) {
	system("cls");
	flag_game_end = 0;
	UI_Draw();
	Reset_game_board();	//������ �ʱ�ȭ�մϴ�.
	Reset_information();//���� ������ �ʱ�ȭ�մϴ�.
	new_block_maker();	//����� �ϳ� �����մϴ�.
	Print_board();		//���� ȭ���� ����մϴ�.
	print_information();	//������ ���

	while (1) {
		if (flag_game_end == 1) {	//�������� �÷��װ� ���������� ���� ����
			system("cls");
			break;
		}

		if (flag_hlod == 1) {	//Ȧ�� �÷��װ� ���������� ���ش�
			flag_hlod = 0;
		}

		speed_maneger();
		for (int i = 0; i < 5; i++) {		//��ĭ�� �Ʒ��� �������� ���� 5�� �Է¹��� �� �ִ�.
			keyboard_controller();	//Ű����� Ű���� �޽��ϴ�.
			MakeShadowBlock();

			Print_board();	//���� ȭ��������մϴ�.	
			Sleep(game_speed);	//���� �ӵ�	//������
			DeletShadowBlock();	//�׸��� ��� �����ֱ� 

			if (flag_hlod == 1) {	//Ȧ�� �÷��� ���������� �ش� ����� �����
				break;
			}

			if (flag_harddrop == 1) {	//�ϵ��� �÷��װ� ���������� �׻� ���ش�.
				flag_harddrop = 0;
				break;
			}
		}
		if (flag_hlod == 0) {	//Ȧ�� �÷��װ� �������� ���� �Ʒ��� �Լ����� ����
			AutoDrop(); //����ڵ��ϰ�
			print_information();	//������ ���
			GameOverCheak();	//���ӿ��� üũ

		}


		if (flag_neednewblock == 1) {	//���ο� ��� �÷��װ� ���������� (���ο� ����� �ʿ��ϸ�) 
			new_block_maker();	//���ο� ��� ����
		}
	}
	return;
}


void score_maneger(void) {
	
	score += 5;	//�⺻���� ����� �ٴڿ� ���� �� 5�� ȹ��
	switch (deleteline_combo){
	
	case 1:	//�޺��� 1�� ��
		score += 50;	//50�� ȹ��
		return;
	case 2:	//�޺��� 2�� ��
		score += 150;	//150�� ȹ��
		return;
	case 3:	//�޺��� 3�� ��
		score += 300;	//300�� ȹ��
		return;
	case 4:	//�޺��� 4�� ��
		score += 400;	//400�� ȸ��
		return;
	default:
		return;
	}

}

void speed_maneger(void) {
	//������ ���̵��� �����ϴ� �Լ� �� �μ��� ����� ���� Ȯ����
	//������ �ø��� ����� �������� �ӵ��� �������Ѵ�.
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

void Reset_information() {	//���� ���� �� ���� ���� �ʱ�ȭ
	score = 0;
	deleteline_total = 0;
	level = 1;
	game_speed = 50;
	hold_type = 0;


	block_typeN1 = rand() % 7;
	block_typeN2 = rand() % 7;

}

void print_information() {	//������ ���� ���׿� ���� ȭ�鿡 ǥ��
	
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

void NextBlockPush(void) {	//������ ���� ��ϵ��� �̸� ������ ���� ĭ���� �о��ش�
	block_type = block_typeN1;
	block_typeN1 = block_typeN2;
	block_typeN2 = rand() % 7;	
}

void GameOverCheak(void) {
	
	for (int x = 1;  x < board_SIZE_X - 2;  x++){

		if (board[2][x] == FBLOCK) { // �������ο� ������ ����� ������
			Best_score();		//�������� ������ �α����� ������ ���������� �ְ������� ���� ����
			printGameOver();	//ȭ�鿡 ��������

			system("cls");		

			
			Reset_game_board(); // ���Ӻ��� �ʱ�ȭ
			Reset_information();	//�������� �ʱ�ȭ

			Print_board();	//���Ӻ��� ���
			print_information();	//�������� ���
		}
	}
}