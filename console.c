#include "tetris.h"

void console_size(void) {
	system("mode con: cols=80 lines=30");   //�ܼ�â ũ�� ����
}

void CursorView(){                          //Ŀ���� ����
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void remove_scrollbar(){                    //��ũ�� �� ���� 
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

void setConsole(void) { //�ϳ��� ��� ȣ��ǰ� �����
	console_size();
    CursorView();
    remove_scrollbar();
}

void gotoxy(int x, int y) {
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    //��Ʈ������ ����鼭 ���ڴ� ���� �̹����� ũ�⿡ ���� �ݰ�����, ���� ���ڷ� ���������� �� �˾ҽ��ϴ�.
    //(A) (,) (a) ���� ���� �� ĭ�� ���������� ���� ó�� Ư�����ڴ� �� ĭ�� �����մϴ�.
    //�׷��� 2ĭ �������� ��ġ�� �� �ְ� X�κ��� ���ϱ� 2�� ���༭ 2ĭ �������� ��ġ�մϴ�.
}