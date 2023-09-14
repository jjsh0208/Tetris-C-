#include "tetris.h"

void Login(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//������� ����
	MYSQL_RES* result = NULL;	//��ü ���̺� ���� ����
	MYSQL_ROW* row = { 0 };		//�� ���� ���� ����

	char ID[15] = { 0 };
	char PASS[15] = { 0 };
	char buffer[200] = { 0 };

	//���ἳ�� �ʱ�ȭ : mysql_intit(����ü �ּ�)
	mysql_init(&mysql);

	//���� : mysql_real_connect(����ü �ּ�, ȣ��Ʈ��, ������, �н����� , DB��, PORT��ȣ )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//����üũ
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//���� ����
		UI_Login();	
		getchar();
		gotoxy(11, 9);
		printf("���̵� :�� ");
		gets(ID);
		gotoxy(10, 11);
		printf("�н����� :�� ");
		gets(PASS);

		sprintf(buffer, "select ID , PASS ,BEST_SCORE from members where ID = '%s' AND PASS = '%s'", ID, PASS);
		//�Է��� ������ ��й�ȣ�� ������ ȸ���� �ִ��� ��ȸ�ϴ� SQL��
		mysql_query(connection, buffer);	//SQL�� ����

		result = mysql_store_result(connection);	//������ SQL���� ��ü ���̺��� �����´�

		if ((row = mysql_fetch_row(result)) != NULL) {	//�� ������ �о�ͼ� ���� �ְ�
			if (strcmp(ID, row[0]) == 0 && strcmp(PASS, row[1]) == 0) {	 //�о�� ������ ��й�ȣ�� �����ϸ� �α��� ����  
				user_ID = row[0];
				user_best_score = row[2];
				gotoxy(15, 15);
				printf("�������! %s ��", user_ID);
				gotoxy(15, 16);
				printf("�α��� ����");
			}
		}
		else {	//��ȸ���� ������ ������ ������ �α׾ƿ�
			gotoxy(15, 15);
			printf("�α��� ����");
		}

		mysql_close(connection);	//�����ͺ��̽� ����
		system("pause");
		system("cls");
	}
	return;
}

void Sing_up(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//������� ����
	MYSQL_RES* result = NULL;	//��ü ���̺� ���� ����
	MYSQL_ROW row = { 0 };		//�� ���� ���� ����

	char ID[15] = { 0 };
	char PASS[15] = { 0 };
	char buffer[200] = { 0 };

	//���ἳ�� �ʱ�ȭ : mysql_intit(����ü �ּ�)
	mysql_init(&mysql);

	//���� : mysql_real_connect(����ü �ּ�, ȣ��Ʈ��, ������, �н����� , DB��, PORT��ȣ )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//����üũ 
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//���� ����
		UI_SingUp();
		getchar();
		gotoxy(9, 9);
		printf("���̵� �Է� : ");
		gets(ID);
		gotoxy(8, 11);
		printf("�н����� �Է� : ");
		gets(PASS);
		sprintf(buffer, "select ID from members where ID = '%s'", ID); //members ���̺��� �Է��� ID�� ������ ID �� �˻�
		
		mysql_query(connection, buffer); // ������ ����
	
		//������ SQL���� ��ü ���̺��� �����´�
		result = mysql_store_result(connection);
		
			//����� �о����
		if ((row = mysql_fetch_row(result)) != NULL) {	//�������� �����Ͽ� �о�� ���� ������ (ID�ߺ�)

			gotoxy(15, 15);
			printf("�ߺ��� ID �Դϴ�.\n");
			gotoxy(15, 16);
			printf("�ٽ� �������ּ���\n");
		}
		else {	//�������� �����Ͽ� �о�� ���� ������ (ID�ߺ� X)

			//�Է��� ID�� PASSWD�� members ���̺� �߰�
			sprintf(buffer, "insert into members values (0,'%s','%s','0')", ID, PASS);
			
			mysql_query(connection, buffer);	//������ ����
			gotoxy(15, 15);
			printf("ȸ������ ����\n");
			gotoxy(15, 15);
			printf("ȯ���մϴ�! �α��� ���ּ���!\n");
		}

		mysql_close(connection);	//�����ͺ��̽� ����
		system("pause");
		system("cls");
		return;
	}
}

void Best_score(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//������� ����
	MYSQL_RES* result = NULL;	//��ü ���̺� ���� ����
	MYSQL_ROW row = { 0 };		//�� ���� ���� ����

	char buffer[200] = { 0 };

	//���ἳ�� �ʱ�ȭ : mysql_intit(����ü �ּ�)
	mysql_init(&mysql);

	//���� : mysql_real_connect(����ü �ּ�, ȣ��Ʈ��, ������, �н����� , DB��, PORT��ȣ )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//����üũ
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//���� ����
		//members ���̺��� �α����� ������ �ְ��������� ���������� ������ �����ͺ��̽��� �ְ� ���� ���� ����
		sprintf(buffer, "update members set BEST_SCORE = '%d' where	ID = '%s' AND '%d' > BEST_SCORE ",score,user_ID,score);
		
		//SQL�� ����
		mysql_query(connection, buffer);
		
	}
	mysql_close(connection);	//�����ͺ��̽� ����
	return;
}

void Ranking(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//������� ����
	MYSQL_RES* result = NULL;	//��ü ���̺� ���� ����
	MYSQL_ROW row = { 0 };		//�� ���� ���� ����

	char buffer[200] = { 0 };
	int rank = 1;
	int x = 10;
	int y = 3;

	//���ἳ�� �ʱ�ȭ : mysql_intit(����ü �ּ�)
	mysql_init(&mysql);

	//���� : mysql_real_connect(����ü �ּ�, ȣ��Ʈ��, ������, �н����� , DB��, PORT��ȣ )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//���� üũ
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	} 
	else {	//���� ����
		//members ���̺��� ������ �� ������ �ְ������� ������������ �ִ� 10������ �����´�.
		mysql_query(connection, "select  ID, BEST_SCORE from members order by BEST_SCORE DESC LIMIT 10");
		
		//������ SQL���� ��ü ���̺��� �����´�
		result = mysql_store_result(connection);	

		gotoxy(11, 1);
		printf("              ��  ŷ");
		gotoxy(11, y++);
		printf("����         �г���        �ְ� ����");
		gotoxy(x, y++);
		printf("=========================================");
		while ((row = mysql_fetch_row(result)) != NULL) {	//null�� ���� �� ���� �����͸� ������� �о�´�
			
			gotoxy(x, y++);
			printf(" |  %-2d |  %-15s |  %-9s |\n", rank,row[0], row[1]);	//���ʺ��� ��ŷ / ���� / �ش� ������ �ְ� ����  
			gotoxy(x, y++);
			printf("=========================================");
			rank++;
		}
	}

	mysql_close(connection);	//�����ͺ��̽� ����
	system("pause");
	system("cls");
	return;
}