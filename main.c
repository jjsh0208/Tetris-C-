#include "tetris.h"

int main(void) {
	int menu = 0;
	
	setConsole();	//�ܼ�â ����
	srand((unsigned)time(NULL));	//���� �ð��� �õ�� �޽��ϴ�.
	
	while (1){
		menu = UI_intro();	//������ ��Ʈ�� �Լ� �޴� ���� �޾ƿͼ� 1.���ӽ���, 2.ȸ������, 3.��ŷ, 4.�������� �� ����

		if (menu == 1 && user_ID != NULL) {	//1. ���ӽ��� (�α����� �Ǿ��� ���� ���ӽ��� ����)
			game();
		}	   
		else if (menu == 2){	//2. �α���
			system("cls");
			Login();			//�α��� �Լ�
		}
		else if (menu == 3 && user_ID != NULL) { //3. �α׾ƿ�
			system("cls");
			user_ID = NULL;		//����� user_ID�� ���� ����
		}
		else if (menu == 4) {	//3. ȸ������
			system("cls");
			Sing_up();			//ȸ������ �Լ�
		}
		else if (menu == 5) {	//4. ��ŷ
			system("cls");
			Ranking();			//��ŷ�� �����ִ� �Լ�
		}
		else if (menu == 6) {	//5. ��������
			exit(0);
		}
		else{	
			system("cls");
			continue;
		}
	}
	return 0;
}