#include "tetris.h"

void Login(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//연결상태 유지
	MYSQL_RES* result = NULL;	//전체 테이블 내용 저장
	MYSQL_ROW* row = { 0 };		//행 단위 내용 저장

	char ID[15] = { 0 };
	char PASS[15] = { 0 };
	char buffer[200] = { 0 };

	//연결설정 초기화 : mysql_intit(구조체 주소)
	mysql_init(&mysql);

	//연결 : mysql_real_connect(구조체 주소, 호스트명, 유저명, 패스워드 , DB명, PORT번호 )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//에러체크
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//연결 정상
		UI_Login();	
		getchar();
		gotoxy(11, 9);
		printf("아이디 :┃ ");
		gets(ID);
		gotoxy(10, 11);
		printf("패스워드 :┃ ");
		gets(PASS);

		sprintf(buffer, "select ID , PASS ,BEST_SCORE from members where ID = '%s' AND PASS = '%s'", ID, PASS);
		//입력한 계정과 비밀번호가 동일한 회원이 있는지 조회하는 SQL문
		mysql_query(connection, buffer);	//SQL문 실행

		result = mysql_store_result(connection);	//실행한 SQL문의 전체 테이블을 가져온다

		if ((row = mysql_fetch_row(result)) != NULL) {	//행 단위로 읽어와서 값이 있고
			if (strcmp(ID, row[0]) == 0 && strcmp(PASS, row[1]) == 0) {	 //읽어온 계정과 비밀번호가 동일하면 로그인 성공  
				user_ID = row[0];
				user_best_score = row[2];
				gotoxy(15, 15);
				printf("어서오세요! %s 님", user_ID);
				gotoxy(15, 16);
				printf("로그인 성공");
			}
		}
		else {	//조회에서 나오는 계정이 없으면 로그아웃
			gotoxy(15, 15);
			printf("로그인 실패");
		}

		mysql_close(connection);	//데이터베이스 종료
		system("pause");
		system("cls");
	}
	return;
}

void Sing_up(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//연결상태 유지
	MYSQL_RES* result = NULL;	//전체 테이블 내용 저장
	MYSQL_ROW row = { 0 };		//행 단위 내용 저장

	char ID[15] = { 0 };
	char PASS[15] = { 0 };
	char buffer[200] = { 0 };

	//연결설정 초기화 : mysql_intit(구조체 주소)
	mysql_init(&mysql);

	//연결 : mysql_real_connect(구조체 주소, 호스트명, 유저명, 패스워드 , DB명, PORT번호 )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//에러체크 
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//연결 정상
		UI_SingUp();
		getchar();
		gotoxy(9, 9);
		printf("아이디 입력 : ");
		gets(ID);
		gotoxy(8, 11);
		printf("패스워드 입력 : ");
		gets(PASS);
		sprintf(buffer, "select ID from members where ID = '%s'", ID); //members 테이블에서 입력한 ID와 동일한 ID 을 검색
		
		mysql_query(connection, buffer); // 쿼리문 실행
	
		//실행한 SQL문의 전체 테이블을 가져온다
		result = mysql_store_result(connection);
		
			//행단위 읽어오기
		if ((row = mysql_fetch_row(result)) != NULL) {	//쿼리문을 실행하여 읽어온 값이 있으면 (ID중복)

			gotoxy(15, 15);
			printf("중복된 ID 입니다.\n");
			gotoxy(15, 16);
			printf("다시 가입해주세요\n");
		}
		else {	//쿼리문을 실행하여 읽어온 값이 없으면 (ID중복 X)

			//입력한 ID와 PASSWD를 members 테이블에 추가
			sprintf(buffer, "insert into members values (0,'%s','%s','0')", ID, PASS);
			
			mysql_query(connection, buffer);	//쿼리문 실행
			gotoxy(15, 15);
			printf("회원가입 성공\n");
			gotoxy(15, 15);
			printf("환영합니다! 로그인 해주세요!\n");
		}

		mysql_close(connection);	//데이터베이스 종료
		system("pause");
		system("cls");
		return;
	}
}

void Best_score(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//연결상태 유지
	MYSQL_RES* result = NULL;	//전체 테이블 내용 저장
	MYSQL_ROW row = { 0 };		//행 단위 내용 저장

	char buffer[200] = { 0 };

	//연결설정 초기화 : mysql_intit(구조체 주소)
	mysql_init(&mysql);

	//연결 : mysql_real_connect(구조체 주소, 호스트명, 유저명, 패스워드 , DB명, PORT번호 )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//에러체크
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	}
	else {	//연결 정상
		//members 테이블에서 로그인한 계정의 최고점수보다 현재점수가 높으면 데이터베이스에 최고 점수 새로 갱신
		sprintf(buffer, "update members set BEST_SCORE = '%d' where	ID = '%s' AND '%d' > BEST_SCORE ",score,user_ID,score);
		
		//SQL문 실행
		mysql_query(connection, buffer);
		
	}
	mysql_close(connection);	//데이터베이스 종료
	return;
}

void Ranking(void) {

	MYSQL mysql = { 0 };
	MYSQL* connection = NULL;	//연결상태 유지
	MYSQL_RES* result = NULL;	//전체 테이블 내용 저장
	MYSQL_ROW row = { 0 };		//행 단위 내용 저장

	char buffer[200] = { 0 };
	int rank = 1;
	int x = 10;
	int y = 3;

	//연결설정 초기화 : mysql_intit(구조체 주소)
	mysql_init(&mysql);

	//연결 : mysql_real_connect(구조체 주소, 호스트명, 유저명, 패스워드 , DB명, PORT번호 )
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWD, NAME, PORT, NULL, 0);

	if (connection == NULL) {	//에러 체크
		fprintf(stderr, "error : %s\n", mysql_error(&mysql));
	} 
	else {	//연결 정상
		//members 테이블에서 계정과 그 계정의 최고점수를 내림차순으로 최대 10개까지 가져온다.
		mysql_query(connection, "select  ID, BEST_SCORE from members order by BEST_SCORE DESC LIMIT 10");
		
		//실행한 SQL문의 전체 테이블을 가져온다
		result = mysql_store_result(connection);	

		gotoxy(11, 1);
		printf("              랭  킹");
		gotoxy(11, y++);
		printf("순위         닉네임        최고 점수");
		gotoxy(x, y++);
		printf("=========================================");
		while ((row = mysql_fetch_row(result)) != NULL) {	//null이 나올 때 까지 데이터를 행단위로 읽어온다
			
			gotoxy(x, y++);
			printf(" |  %-2d |  %-15s |  %-9s |\n", rank,row[0], row[1]);	//왼쪽부터 랭킹 / 계정 / 해당 계정의 최고 점수  
			gotoxy(x, y++);
			printf("=========================================");
			rank++;
		}
	}

	mysql_close(connection);	//데이터베이스 종료
	system("pause");
	system("cls");
	return;
}