#include "tetris.h"

void console_size(void) {
	system("mode con: cols=80 lines=30");   //콘솔창 크기 조정
}

void CursorView(){                          //커서를 제거
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void remove_scrollbar(){                    //스크롤 바 제거 
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

void setConsole(void) { //하나로 묶어서 호출되게 만든다
	console_size();
    CursorView();
    remove_scrollbar();
}

void gotoxy(int x, int y) {
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    //테트리스를 만들면서 문자는 문자 이미지의 크기에 따라 반각문자, 전각 문자로 나누어지는 걸 알았습니다.
    //(A) (,) (a) 공백 등은 반 칸을 차지하지만 ■블록 처럼 특수문자는 한 칸을 차지합니다.
    //그래서 2칸 간격으로 배치할 수 있게 X부분을 곱하기 2를 해줘서 2칸 간격으로 배치합니다.
}