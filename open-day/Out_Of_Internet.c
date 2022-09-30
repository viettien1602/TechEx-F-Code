#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <MMsystem.h>

//function to handle console 
void DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void ShowScrollbar(BOOL Show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void DisableCtrButton(BOOL Close, BOOL Min, BOOL Max) {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    
    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void SetWindowSize(int width, int height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetScreenBufferSize(int width, int height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

void CursorType(BOOL cursor) {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = cursor;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

//function to handle game
void wait(clock_t time) {
    clock_t goal;
    goal = time + clock();
    while (goal > clock()) {}
}

int random(int max) {
	return 1 + rand() % max;
}

void gotoxy(int x, int y) {
    static HANDLE h = NULL;  
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };  
    SetConsoleCursorPosition(h,c);
}

void clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void changeColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Global variables used in functions
int border = 7;
int fill   = 9;
int bottomEdge = 1;
int twinkle = 15;
int bottomEdge_exception = 25;

char userName[30]; 
char password[30];
int  bestScore = 0;

char ground[4][151];
int k;

int filling1 = 7;

int detectedNewAccount = 0;
	// detectedNewAccount = 0: the account are signed up
	// detectedNewAccount = 1: the account are new, or user changes password

int flagMusic = 1; 	// flagMusic = 1: reset music 
					//flagMusic = 0: do not reset music
int signInStatus = 0; 	// signInStatus = 0: not the first time sign in 
						//signInStatus = 1: first time sign in
int playingStatus = 1; 	//playingStatus = 1: first time playing
						//playingStatus = 0: playing again 
						
//struct
struct data {
	char userName[30];
	char password[30];
	int  bestScore;
};
struct character {
	int x, y;
};

//funcitons to design console graphics
void printLetter_I(int x0, int y0) {
 	// border
	changeColor(border);
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 2); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 3); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 4); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 5); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 6); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 7); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 8); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 9); printf("%c    %c", 219, 219);
	gotoxy(x0, y0 + 10); printf("%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223);
 	// fill
  	changeColor(fill);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 2); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 4); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 5); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 6); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	// fill bottom edge
  	changeColor(bottomEdge);
  	gotoxy(x0 + 1, y0 + 9); printf("%c%c%c%c", 223, 223, 223, 223);
    // twinkle
  	changeColor(twinkle);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c", 219, 219);
}

void printLetter_N(int x0, int y0) {
    // border
  	changeColor(border);
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c    %c%c", 219, 219, 219);
	gotoxy(x0, y0 + 2); printf("%c     %c%c", 219, 219, 219);
	gotoxy(x0, y0 + 3); printf("%c      %c%c", 219, 219, 219);
	gotoxy(x0, y0 + 4); printf("%c       %c%c", 219, 219, 219);
	gotoxy(x0, y0 + 5); printf("%c        %c%c", 219, 219, 219);
	gotoxy(x0, y0 + 6); printf("%c    %c%c   %c", 219, 219, 219, 219);
	gotoxy(x0, y0 + 7); printf("%c    %c%c%c", 219, 219, 219, 219, 223);
	gotoxy(x0, y0 + 8); printf("%c    %c %c%c", 219, 219, 219, 219);
	gotoxy(x0, y0 + 9); printf("%c    %c  %c%c%c", 219, 219, 219, 219, 220);
	gotoxy(x0, y0 + 10); printf("%c%c%c%c%c%c   %c%c", 223, 223, 223, 223, 223, 223, 223, 223);
	
	gotoxy(x0 + 11, y0 + 0); printf("%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220);
	gotoxy(x0 + 11, y0 + 1); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 2); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 3); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 4); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 5); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 6); printf("%c    %c", 219, 219);
	gotoxy(x0 + 11, y0 + 7); printf("     %c", 219, 219);
	gotoxy(x0 + 11, y0 + 8); printf("     %c", 219, 219);
	gotoxy(x0 + 11, y0 + 9); printf("     %c", 219, 219);
	gotoxy(x0 + 11, y0 + 10); printf("%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223);
	// fill
  	changeColor(fill);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 2); printf("%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 3); printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 4); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 5); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219), 219, 219, 219, 219;
  	gotoxy(x0 + 1, y0 + 6); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	
  	gotoxy(x0 + 7, y0 + 6); printf("%c%c%c", 219, 219, 219);
  	gotoxy(x0 + 8, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219);
  	gotoxy(x0 + 9, y0 + 8); printf("%c%c%c", 219, 219, 219);
  	
  	gotoxy(x0 + 12, y0 + 1); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 2); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 4); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 5); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 6); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 12, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	
	// fill bottom edge
  	changeColor(bottomEdge);
  	gotoxy(x0 + 1, y0 + 9); printf("%c%c%c%c", 223, 223, 223, 223, 223);
  	gotoxy(x0 + 10, y0 + 9); printf("%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223);
  	
  	gotoxy(x0 + 7, y0 + 6); printf("%c", 223);
	gotoxy(x0 + 8, y0 + 7); printf("%c", 223);
	gotoxy(x0 + 9, y0 + 8); printf("%c", 223);
	
  	// twinkle
  	changeColor(twinkle);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c", 219, 219);
}

void printLetter_T(int x0, int y0) {
	// border
	changeColor(border);
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c            %c", 219, 219);
	gotoxy(x0, y0 + 2); printf("%c            %c", 219, 219);
	gotoxy(x0, y0 + 3); printf("%c%c%c%c%c    %c%c%c%c%c", 223, 223, 223, 223, 219, 219, 223, 223, 223, 223);
	
	gotoxy(x0, y0 + 4); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 5); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 6); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 7); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 8); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 9); printf("    %c    %c", 219, 219);
	gotoxy(x0, y0 + 10); printf("    %c%c%c%c%c%c", 223, 223, 223, 223, 223, 223);
	// fill
  	changeColor(fill);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 2); printf("%c%c%c%c", 219, 219, 219, 219, 219);
	gotoxy(x0 + 5, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 4); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 5); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 6); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 5, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	
  	// fill bottom edge
  	changeColor(bottomEdge);
  	gotoxy(x0 + 1, y0 + 2); printf("%c%c%c%c", 223, 223, 223, 223);
  	gotoxy(x0 + 9, y0 + 2); printf("%c%c%c%c", 223, 223, 223, 223);
	gotoxy(x0 + 5, y0 + 9); printf("%c%c%c%c", 223, 223, 223, 223);
	
	// twinkle
  	changeColor(twinkle);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c", 219, 219);
}

void printLetter_E(int x0, int y0) {
	// border
	changeColor(border);
	gotoxy(x0, y0 + 0); printf(" %c%c%c%c%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c%c         %c", 219, 223, 219);
	gotoxy(x0, y0 + 2); printf("%c          %c", 219, 219);
	gotoxy(x0, y0 + 3); printf("%c    %c%c%c%c%c%c%c", 219, 220, 220, 220, 220, 220, 220, 219);
	gotoxy(x0, y0 + 4); printf("%c       %c", 219, 219);
	gotoxy(x0, y0 + 5); printf("%c       %c", 219, 219);
	gotoxy(x0, y0 + 6); printf("%c       %c", 219, 219);
	gotoxy(x0, y0 + 7); printf("%c          %c", 219,  219);
	gotoxy(x0, y0 + 8); printf("%c          %c", 219, 219);
	gotoxy(x0, y0 + 9); printf("%c%c         %c", 219, 220, 219);
   gotoxy(x0, y0 + 10); printf(" %c%c%c%c%c%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
	
	changeColor(121);
	gotoxy(x0 + 5, y0 + 7); printf("%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220);
	
	// fill
	changeColor(fill);
	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(x0 + 1, y0 + 2); printf("%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
 
  	gotoxy(x0 + 1, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 4); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 5); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 6); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
 
	changeColor(151);
	gotoxy(x0 + 1, y0 + 1); printf("%c", 223);
	
	changeColor(25);
	gotoxy(x0 + 5, y0 + 2); printf("%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223);
	
	// fill bottom edge
  	changeColor(bottomEdge);
  	gotoxy(x0 + 2, y0 + 9); printf("%c%c%c%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
  	gotoxy(x0 + 5, y0 + 6); printf("%c%c%c", 223, 223, 223);
	
	// twinkle
  	changeColor(twinkle);
  	gotoxy(x0 + 2, y0 + 1); printf("%c%c", 219, 219);
}

void printLetter_R(int x0, int y0) {
	// border
	changeColor(border);
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c           %c%c", 219, 223, 219);
	gotoxy(x0, y0 + 2); printf("%c            %c", 219, 219);
	gotoxy(x0, y0 + 3); printf("%c    %c%c%c%c    %c", 219, 220, 220, 220, 220, 219);
	gotoxy(x0, y0 + 4); printf("%c            %c", 219, 219);
	gotoxy(x0, y0 + 5); printf("%c          %c%c%c", 219, 220, 220, 219);
	gotoxy(x0, y0 + 6); printf("%c            %c", 219, 219);
	gotoxy(x0, y0 + 7); printf("%c    %c%c%c%c    %c", 219, 220, 220, 220, 220, 219);
	gotoxy(x0, y0 + 8); printf("%c    %c  %c    %c", 219, 219, 219, 219);
	gotoxy(x0, y0 + 9); printf("%c    %c  %c    %c", 219, 219, 219, 219);
	gotoxy(x0, y0 + 10); printf("%c%c%c%c%c%c  %c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223);
	// fill
	changeColor(fill);
	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 2); printf("%c%c%c%c    %c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 4); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 5); printf("%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 6); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219, 219);
  	
  	gotoxy(x0 + 9, y0 + 3); printf("%c%c%c%c", 219, 219, 219, 219);
  	gotoxy(x0 + 9, y0 + 7); printf("%c%c%c%c", 219, 219, 219, 219);
  	gotoxy(x0 + 9, y0 + 8); printf("%c%c%c%c", 219, 219, 219, 219);
  	
  	changeColor(fill * 16 + bottomEdge);
  	gotoxy(x0 + 5, y0 + 2);  printf("%c%c%c%c", 220, 220, 220, 220);
  	gotoxy(x0 + 11, y0 + 4); printf("%c%c", 220, 220);
  	gotoxy(x0 + 5, y0 + 6);  printf("%c%c%c%c", 220, 220, 220, 220);
  	
  	// fill bottom edge
  	changeColor(bottomEdge);
  	gotoxy(x0 + 1, y0 + 9); printf("%c%c%c%c", 223, 223, 223, 223);
  	gotoxy(x0 + 9, y0 + 9); printf("%c%c%c%c", 223, 223, 223, 223);
  	
  	// twinkle
  	changeColor(twinkle);
  	gotoxy(x0 + 1, y0 + 1); printf("%c%c", 219, 219);

}

void printLetter_o(int x0, int y0) {
	changeColor(filling1);
	// shadow
	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177);
	gotoxy(x0 + 1, y0 + 2); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 3); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 4); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 5); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 6); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 7); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177);
	// border
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c", 219);
	gotoxy(x0, y0 + 2); printf("%c", 219);
	gotoxy(x0, y0 + 3); printf("%c", 219);
	gotoxy(x0, y0 + 4); printf("%c", 219);
	gotoxy(x0, y0 + 5); printf("%c", 219);
	gotoxy(x0, y0 + 6); printf("%c", 219);
	gotoxy(x0, y0 + 7); printf("%c%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223);
	
	gotoxy(x0 + 6, y0 + 1); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 2); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 3); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 4); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 5); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 6); printf("%c", 219);
	
}

void printLetter_u(int x0, int y0) {
	changeColor(filling1);
	// shadow
	gotoxy(x0 + 1, y0 + 1); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 2); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 3); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 4); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 5); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 6); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 7); printf("%c     %c", 177, 177);
	gotoxy(x0 + 1, y0 + 8); printf("%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177);
	// border
	gotoxy(x0, y0 + 0); printf("%c", 220);
	gotoxy(x0, y0 + 1); printf("%c", 219);
	gotoxy(x0, y0 + 2); printf("%c", 219);
	gotoxy(x0, y0 + 3); printf("%c", 219);
	gotoxy(x0, y0 + 4); printf("%c", 219);
	gotoxy(x0, y0 + 5); printf("%c", 219);
	gotoxy(x0, y0 + 6); printf("%c", 219);
	gotoxy(x0, y0 + 7); printf("%c%c%c%c%c%c%c", 223, 223, 223, 223, 223, 223, 223);
	
	gotoxy(x0 + 6, y0 + 0); printf("%c", 220);
	gotoxy(x0 + 6, y0 + 1); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 2); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 3); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 4); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 5); printf("%c", 219);
	gotoxy(x0 + 6, y0 + 6); printf("%c", 219);
}

void printLetter_t(int x0, int y0) {
	changeColor(filling1);
	// shadow
	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177);
	gotoxy(x0 + 4, y0 + 2); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 3); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 4); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 5); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 6); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 7); printf("%c", 177);
	gotoxy(x0 + 4, y0 + 8); printf("%c", 177);
	// border
	gotoxy(x0    , y0 + 0); printf("%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220);	
	gotoxy(x0 + 3, y0 + 1); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 2); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 3); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 4); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 5); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 6); printf("%c", 219);
	gotoxy(x0 + 3, y0 + 7); printf("%c", 223);
}

void printLetter_f(int x0, int y0) {
	changeColor(filling1);
	// shadow
	gotoxy(x0 + 1, y0 + 1); printf("%c%c%c%c%c%c%c", 177, 177, 177, 177, 177, 177, 177);
	gotoxy(x0 + 1, y0 + 2); printf("%c", 177);
	gotoxy(x0 + 1, y0 + 3); printf("%c%c%c%c%c", 177, 177, 177, 177, 177);
	gotoxy(x0 + 1, y0 + 4); printf("%c", 177);
	gotoxy(x0 + 1, y0 + 5); printf("%c", 177);
	gotoxy(x0 + 1, y0 + 6); printf("%c", 177);
	gotoxy(x0 + 1, y0 + 7); printf("%c", 177);
	gotoxy(x0 + 1, y0 + 8); printf("%c", 177);
	// border
	gotoxy(x0, y0 + 0); printf("%c%c%c%c%c%c%c", 220, 220, 220, 220, 220, 220, 220);
	gotoxy(x0, y0 + 1); printf("%c", 219);
	gotoxy(x0, y0 + 2); printf("%c%c%c%c%c", 219, 220, 220, 220, 220);
	gotoxy(x0, y0 + 3); printf("%c", 219);
	gotoxy(x0, y0 + 4); printf("%c", 219);
	gotoxy(x0, y0 + 5); printf("%c", 219);
	gotoxy(x0, y0 + 6); printf("%c", 219);
	gotoxy(x0, y0 + 7); printf("%c", 223);	
}

void printPlugOutIcon(int x0) {
	// border
	/*
	п  -- top
	л  -- block
	м  -- bottom
	*/
	
	changeColor(15);
	gotoxy(x0, 0);  printf("                                                      лл");
	gotoxy(x0, 1);  printf("                                                     лл");
	gotoxy(x0, 2);  printf("                                                    лл");
	gotoxy(x0, 3);  printf("                                                   лл");
	gotoxy(x0, 4);  printf("                              мммммммммммммммммммммлп");
	gotoxy(x0, 5);  printf("      лпл                   млппппппппппппппппппппп");
	gotoxy(x0, 6);  printf("      л лппппппм          млп");
	gotoxy(x0, 7);  printf("ппппппл л       пм      млп");
	gotoxy(x0, 8);  printf("      л л         ллллллп");
	gotoxy(x0, 9);  printf("ммммммл л       мп");
	gotoxy(x0, 10); printf("      л лммммммп");
	gotoxy(x0, 11); printf("      лмл"); 
	
	// fill
	changeColor(246);
	gotoxy(x0 + 9, 6);  printf("мммммм");
	
	changeColor(14);
	gotoxy(x0 + 9, 7);  printf("ллллллл");
	gotoxy(x0 + 9, 8);  printf("ллллллллл");
	gotoxy(x0 + 9, 9);  printf("ллллллл");
	
	changeColor(230);
	gotoxy(x0 + 9, 7);  printf("пппппп");
	gotoxy(x0 + 17, 8);  printf("п");
	
	changeColor(246);
	gotoxy(x0 + 16, 7);  printf("м");
	changeColor(254);
	gotoxy(x0 + 16, 9);  printf("п");
	changeColor(15);
}

void printXicon(int x0, int y0) {
	// border
	changeColor(4);
	gotoxy(x0 + 1, y0);  printf("мм      мм");
	gotoxy(x0, y0 + 1);  printf("ллллм  млллл");
	gotoxy(x0 + 1, y0 + 2);  printf("пллллллллп");
	gotoxy(x0 + 3, y0 + 3);  printf("лллллл");
	gotoxy(x0 + 1, y0 + 4); printf("мллллллллм");
	gotoxy(x0, y0 + 5); printf("ллллп  плллл");
	gotoxy(x0 + 1, y0 + 6); printf("пп      пп");
	
	/*
	п  -- top
	л  -- block
	м  -- bottom
	*/
	
	// shadow
	changeColor(12);	
	gotoxy(x0 + 1, y0); printf("мм"); gotoxy(x0 + 9, y0); printf("мм");
	gotoxy(x0 + 1, y0 + 4); printf("м"); gotoxy(x0 + 10, y0 + 4); printf("м");
	
	changeColor(76);
	gotoxy(x0 + 3, y0 + 1); printf("п"); gotoxy(x0 + 8, y0 + 1); printf("п"); 
	
	changeColor(12);
	gotoxy(x0 + 4, y0 + 1); printf("м"); gotoxy(x0 + 7, y0 + 1); printf("м"); 
	
	changeColor(76);
	gotoxy(x0 + 5, y0 + 2); printf("пп");
	
	changeColor(196);
	gotoxy(x0 + 11, y0 + 1); printf("м");
	gotoxy(x0 + 2, y0 + 4); printf("м");
	gotoxy(x0, y0 + 5); printf("м");
	gotoxy(x0 + 9, y0 + 4); printf("м");
	gotoxy(x0 + 11, y0 + 5); printf("м");
	changeColor(15);
}

void printWelcomeScreen() {
	printLetter_o(19, 4);
	printLetter_u(28, 4);
	printLetter_t(37, 4);
	printLetter_o(51, 4);
	printLetter_f(60, 4);
	
	printLetter_I(19, 14);
	printLetter_N(26, 14);
	printLetter_T(44, 14);
	printLetter_E(59, 14);
	printLetter_R(72, 14);
	printLetter_N(87, 14);
	printLetter_E(105, 14);
	printLetter_T(118, 14);
	
	printPlugOutIcon(80);
	printXicon(112, 2);
}

//functions to create scene
void initializeGround(char ground[4][151]) {
	srand(time(NULL));
	int i, t;
	
	for (i = 0; i < 150; i++) {
		ground[0][i] = 254;
		t = random(10);
		switch(t) {
			case 1 : ground[1][i] = '-'; ground[2][i] = ' '; ground[3][i] = ' '; break;
			case 2 : ground[1][i] = ' '; ground[2][i] = ' '; ground[3][i] = ' '; break;
			case 3 : ground[1][i] = '.'; ground[2][i] = ' '; ground[3][i] = ' '; break;
			case 4 : ground[1][i] = ' '; ground[2][i] = ' '; ground[3][i] = '.'; break;
			case 5 : ground[1][i] = ' '; ground[2][i] = '-'; ground[3][i] = ' '; break;
			case 6 : ground[1][i] = ' '; ground[2][i] = ' '; ground[3][i] = '-'; break;
			case 7 : ground[1][i] = 248; ground[2][i] = ' '; ground[3][i] = ' '; break;
			case 8 : ground[1][i] = ' '; ground[2][i] = '.'; ground[3][i] = '.'; break;
			case 9 : ground[1][i] = ' '; ground[2][i] = '$'; ground[3][i] = ' '; break;
			case 10: ground[1][i] = ' '; ground[2][i] = ' '; ground[3][i] = '$'; break;
		}
	}
	ground[0][150] = '\0';
	ground[1][150] = '\0';
	ground[2][150] = '\0';
	ground[3][150] = '\0';
}

void moveGround(char ground[4][151]) {
	gotoxy(0, 32);
	puts(&ground[0][0]);
	puts(&ground[1][0]);
	puts(&ground[2][0]);
	puts(&ground[3][0]);
	int i, t;
	for (i = 0; i <= 148; i++) {
		ground[1][i] = ground[1][i + 1];
		ground[2][i] = ground[2][i + 1];
		ground[3][i] = ground[3][i + 1];
	}
	
	t = random(10);
	switch(t) {
		case 1 : ground[1][149] = '-'; ground[2][149] = ' '; ground[3][149] = ' '; break;
		case 2 : ground[1][149] = ' '; ground[2][149] = ' '; ground[3][149] = ' '; break;
		case 3 : ground[1][149] = '.'; ground[2][149] = ' '; ground[3][149] = ' '; break;
		case 4 : ground[1][149] = ' '; ground[2][149] = ' '; ground[3][149] = '.'; break;
		case 5 : ground[1][149] = ' '; ground[2][149] = '-'; ground[3][149] = ' '; break;
		case 6 : ground[1][149] = ' '; ground[2][149] = ' '; ground[3][149] = '-'; break;
		case 7 : ground[1][149] = 248; ground[2][149] = ' '; ground[3][149] = ' '; break;
		case 8 : ground[1][149] = ' '; ground[2][149] = '$'; ground[3][149] = '.'; break;
		case 9 : ground[1][149] = ' '; ground[2][149] = '.'; ground[3][149] = ' '; break;
		case 10: ground[1][149] = ' '; ground[2][149] = ' '; ground[3][149] = '$'; break;
	}
}

void drawSun(int x, int y) {
	int i = 219, j = 176;
	gotoxy(x, y);
	printf("           %c%c                            \n", j, j);
	gotoxy(x, y + 1);
	printf("   %c%c      %c%c      %c%c                \n",j, j, i, i, j, j);
	gotoxy(x, y + 2);
	printf("     %c%c  %c%c%c%c%c%c  %c%c              \n", j, j ,i, i, i, i, i, i, j, j);
	gotoxy(x, y + 3);
	printf("       %c%c%c%c%c%c%c%c%c%c                \n", i, i, i, i, i, i, i, i, i, i);
	gotoxy(x, y + 4);
	printf("  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c \n", j, j, j ,i, i, i, i, i, i, i, i, i, i, i, i, i, i, j, j, j);
	gotoxy(x, y + 5);
	printf("       %c%c%c%c%c%c%c%c%c%c                \n", i, i, i, i, i, i, i, i, i, i);
	gotoxy(x, y + 6);
	printf("     %c%c  %c%c%c%c%c%c  %c%c              \n", j, j ,i, i, i, i, i, i, j, j);
	gotoxy(x, y + 7);
	printf("   %c%c      %c%c      %c%c                \n",j, j, i, i, j, j);
	gotoxy(x, y + 8);
	printf("           %c%c                            \n", j, j);
}

void deleteSun(int x, int y) {
	gotoxy(x, y);
	puts("                      ");
	gotoxy(x, y + 1);
	puts("                      ");
	gotoxy(x, y + 2);
	puts("                      ");
	gotoxy(x, y + 3);
	puts("                      ");
	gotoxy(x, y + 4);
	puts("                      ");
	gotoxy(x, y + 5);
	puts("                      ");
	gotoxy(x, y + 6);
	puts("                      ");
	gotoxy(x, y + 7);
	puts("                      ");
	gotoxy(x, y + 8);
	puts("                      ");
}

void drawMoon(int x, int y) {
	gotoxy(x, y);
	puts("   _.._  ");
	gotoxy(x, y + 1);
	puts(" .' .-'` ");
	gotoxy(x, y + 2);
	puts("/  /     ");
	gotoxy(x, y + 3);
	puts("|  |     ");
	gotoxy(x, y + 4);
	puts("\\  \\   ");
	gotoxy(x, y + 5);
	puts(" '._'-._ ");
	gotoxy(x, y + 6);
	puts("    ```  ");
}

void deleteMoon(int x, int y) {
	gotoxy(x, y);
	puts("         ");
	gotoxy(x, y + 1);
	puts("         ");
	gotoxy(x, y + 2);
	puts("         ");
	gotoxy(x, y + 3);
	puts("         ");
	gotoxy(x, y + 4);
	puts("         ");
	gotoxy(x, y + 5);
	puts("         ");
	gotoxy(x, y + 6);
	puts("         ");
}

void drawCloud(int x, int y) {
    gotoxy(x, y - 1);
    printf("        млллм        ");
    gotoxy(x, y);
    printf("      мллллллллм     ");
    gotoxy(x, y + 1);
    printf(" мммллллллллллллмм   ");
    gotoxy(x, y + 2);
    printf("лллллллллллллллллллм ");
    gotoxy(x, y + 3);
    printf(" плллллллллллллллллп ");
}

void deleteCloud(int x, int y) {
    gotoxy(x, y - 1);
    printf("                     ");
    gotoxy(x, y);
    printf("                     ");
    gotoxy(x, y + 1);
    printf("                     ");
    gotoxy(x, y + 2);
    printf("                     ");
    gotoxy(x, y + 3);
    printf("                     ");
}

void drawStar(int x, int y) {
	gotoxy(x, y);
	puts("  |  ");
	gotoxy(x, y + 1);
	puts("--o--");
	gotoxy(x, y + 2);
	puts("  |  ");
}

void deleteStar(int x, int y) {
	gotoxy(x, y);
	puts("     ");
	gotoxy(x, y + 1);
	puts("     ");
	gotoxy(x, y + 2);
	puts("     ");
}

//function to draw character
	//dino1
void drawDino1(int x, int y, int jump){
    static int a = 1;   
    if (jump == 0)
        k = 0;
    else if (jump == 2)
        k--;
    else
        k++;
    gotoxy(x, y - k);		printf("                 ");
    gotoxy(x, y + 1 - k);	printf("         млпллллм");
    gotoxy(x, y + 2 - k);	printf("         лллллллл");
    gotoxy(x, y + 3 - k);	printf("         лллллппп");
    gotoxy(x, y + 4 - k);	printf(" л      мллллппп ");
    gotoxy(x, y + 5 - k);	printf(" ллм  мллллллммм ");
    gotoxy(x, y + 6 - k);	printf(" пллллллллллл  п ");
    gotoxy(x, y + 7 - k);	printf("   плллллллп     ");
    gotoxy(x, y + 8 - k);
    if (jump == 1 || jump == 2) {
        printf("    ллп пл    ");
        gotoxy(x, y + 9 - k);
        printf("    лм   лм   ");
    }
    else if (a == 1) {
        printf("    пллп  ппп ");
        gotoxy(x, y + 9 - k);
        printf("      лм      ");
        a = 2;
    }
    else if (a == 2) {
        printf("    пллп  ппп ");
        gotoxy(x, y + 9 - k);
        printf("      лм      ");
        a = 3;
    }
    else if (a == 3) {
        printf("    пллп  ппп ");
        gotoxy(x, y + 9 - k);
        printf("      лм      ");
        a = 4;
    }
    else if (a == 4) {
        printf("     плм пл   ");
        gotoxy(x, y + 9 - k);
        printf("          лм  ");
        a = 5;
    }
    else if (a == 5) {
        printf("     плм пл   ");
        gotoxy(x, y + 9 - k);
        printf("          лм  ");
        a = 6;
    }
    else if (a == 6) {
        printf("     плм пл   ");
        gotoxy(x, y + 9 - k);
        printf("          лм  ");
        a = 1;
    }
    gotoxy(x, y + 10 - k);
    if (jump != 0) {
        printf("              ");
    }
    wait(15);
}

void deleteDino1(int x, int y, int jump) {
    static int a = 1;
    if (jump == 0)
        k = 0;
    gotoxy(x, y - k);
    printf("                     ");
    gotoxy(x, y + 1 - k);
    printf("                     ");
    gotoxy(x, y + 2 - k);
    printf("                     ");
    gotoxy(x, y + 3 - k);
    printf("                     ");
    gotoxy(x, y + 4 - k);
    printf("                     ");
    gotoxy(x, y + 5 - k);
    printf("                     ");
    gotoxy(x, y + 6 - k);
    printf("                     ");
    gotoxy(x, y + 7 - k);
    printf("                     ");
    gotoxy(x, y + 8 - k);
    printf("                     ");
    gotoxy(x, y + 9 - k);
    printf("                     ");
}

void drawSittingDino1(int x, int y) {
    gotoxy(x, y + 2); 	printf("           мллллмм");
    gotoxy(x, y + 3);	printf("           ллмлллл");
    gotoxy(x, y + 4);	printf("           лллллпп");
    gotoxy(x, y + 5);	printf("        ммллллпппп");
    gotoxy(x, y + 6);	printf("       ллллллллппп");    
    gotoxy(x, y + 7);	printf("      ллллллллпппп");
    gotoxy(x, y + 8);	printf("л   ллллллллллмл  ");
    gotoxy(x, y + 9);	printf("ллллллллллллллмммл");
    wait(15);
}

void deleteSittingDino1(int x, int y) {
    gotoxy(x, y + 2);
    printf("                    ");
    gotoxy(x, y + 3);
    printf("                    ");
    gotoxy(x, y + 4);
    printf("                    ");
    gotoxy(x, y + 5);
    printf("                    ");
    gotoxy(x, y + 6);
    printf("                    ");
    gotoxy(x, y + 7);
    printf("                    ");
    gotoxy(x, y + 8);
    printf("                    ");
    gotoxy(x, y + 9);
    printf("                    ");
}

void drawDeadDino1(int x, int y, int jump) {
	if (jump <= 2) {
		gotoxy(x, y + 1 - k);
	    printf("         млXллллм");
	}
	else {
		gotoxy(x, y + 3);
    	printf("           ллXлллл");
    }		
}

	//kaonashi
void drawKaonashi(int x, int y, int jump) {
    if (jump == 0)
        k = 0;
    else if (jump == 2)
        k--;
    else
        k++;
    gotoxy(x, y - 1 - k);
    printf("                   ");
    gotoxy(x, y - k);
    printf("    ммллппппмм     ");
    gotoxy(x, y + 1 - k);
    printf("   лллп л    лпм   ");
    gotoxy(x, y + 2 - k);
	printf("  лллп  мм   ммпм  ");
    gotoxy(x, y + 3 - k);
    printf(" мллл   м     м л  ");
    gotoxy(x, y + 4 - k);
    printf(" ллллм  п пмп п л  ");
    gotoxy(x, y + 5 - k);
    printf(" ллллллм      млллл ");
    gotoxy(x, y + 6 - k);
    if (jump == 1 || jump == 2) {	
		printf("  лллллллллллллллл ");
    	gotoxy(x, y + 7 - k);
		printf("   ллллллллллллм   ");
    	gotoxy(x, y + 8 - k);
        printf("    лллллллллл     ");
        gotoxy(x, y + 9 - k);
        printf("       ллллл       ");
    }
    else {	
		printf(" ллллллллллллллллл ");
    	gotoxy(x, y + 7 - k);	
		printf(" лллллллллллллллм  ");
    	gotoxy(x, y + 8 - k);
        printf(" лллллллллллллллл  ");
        gotoxy(x, y + 9 - k);
        printf("мллллллллллллллллм ");
    }
    gotoxy(x, y + 10 - k);
    if (jump != 0) {
        printf("                   ");
    }
    wait(15);
}

void deleteKaonashi(int x, int y, int jump) {
    static int a = 1;
    if (jump == 0)
        k = 0;
    gotoxy(x, y - 1 - k);
    printf("                   ");
    gotoxy(x, y - k);
    printf("                   ");
    gotoxy(x, y + 1 - k);
    printf("                   ");
    gotoxy(x, y + 2 - k);
    printf("                   ");
    gotoxy(x, y + 3 - k);
    printf("                   ");
    gotoxy(x, y + 4 - k);
    printf("                   ");
    gotoxy(x, y + 5 - k);
    printf("                   ");
    gotoxy(x, y + 6 - k);
    printf("                   ");
    gotoxy(x, y + 7 - k);
    printf("                   ");
    gotoxy(x, y + 8 - k);
	printf("                   ");
    gotoxy(x, y + 9 - k);
    printf("                   ");
}

void drawSittingKaonashi(int x, int y) {
    gotoxy(x, y + 2);
    printf("    ммллппппмм     ");
    gotoxy(x, y + 3);
    printf("   лллп л    лпм   ");
    gotoxy(x, y + 4);
    printf("  лллп  мм   ммпм  ");
    gotoxy(x, y + 5);
    printf(" мллл   м     м л  ");
    gotoxy(x, y + 6);
    printf(" ллллм  п пмп п л  ");
    gotoxy(x, y + 7);
    printf(" ллллллм      млллл");
    gotoxy(x, y + 8);
    printf(" лллллллллллллллллл");
    gotoxy(x, y + 9);
    printf(" лллллллллллллллм  ");
    wait(15);
}

void deleteSittingKaonashi(int x, int y) {
    gotoxy(x, y + 2);
    printf("                   ");
    gotoxy(x, y + 3);
    printf("                   ");
    gotoxy(x, y + 4);
    printf("                   ");
    gotoxy(x, y + 5);
    printf("                   ");
    gotoxy(x, y + 6);
    printf("                   ");
    gotoxy(x, y + 7);
    printf("                   ");
    gotoxy(x, y + 8);
    printf("                   ");
    gotoxy(x, y + 9);
    printf("                   ");
}

void drawDeadKaonashi(int x, int y, int jump) {
	if (jump <= 2) {
		gotoxy(x, y + 2 - k);
    	printf("  лллп  X    X пм  ");
    } else {
    	gotoxy(x, y + 2);
    	printf("  лллп  X    X пм  ");
    }
}

	//ironman
void drawIronMan(int x, int y, int jump) {
    static int a = 1;
    if (jump == 0)
        k = 0;
    else if (jump == 2)
        k--;
    else
        k++;
    gotoxy(x, y - 1 - k);
    printf("              ");
    gotoxy(x, y - k);
    printf("  мллллллллм  ");
    gotoxy(x, y + 1 - k);
    printf(" лллллллллллл ");
    gotoxy(x, y + 2 - k);
    printf(" лллммлллммлл ");
    gotoxy(x, y + 3 - k);
    printf(" лллллппплллл ");
    gotoxy(x, y + 4 - k);
    printf(" ппллллллллпп ");
    gotoxy(x, y + 5 - k);
    printf(" мллллппплллм ");
    gotoxy(x, y + 6 - k);
    printf("мллллллмлллллм");
    gotoxy(x, y + 7 - k);
    printf("пп лллллллл пп");
    gotoxy(x, y + 8 - k);
    printf("   ллл ллл    ");
    gotoxy(x, y + 9 - k);
    printf("   ллп пп     ");
    gotoxy(x, y + 10 - k);
    if (jump != 0)
    {
        printf("              ");
    }
    wait(15);
}

void deleteIronMan(int x, int y, int jump) {
    static int a = 1;
    if (jump == 0)
        k = 0;
    gotoxy(x, y - 1 - k);
    printf("              ");
    gotoxy(x, y - k);
    printf("              ");
    gotoxy(x, y + 1 - k);
    printf("              ");
    gotoxy(x, y + 2 - k);
    printf("              ");
    gotoxy(x, y + 3 - k);
    printf("              ");
    gotoxy(x, y + 4 - k);
    printf("              ");
    gotoxy(x, y + 5 - k);
    printf("              ");
    gotoxy(x, y + 6 - k);
    printf("              ");
    gotoxy(x, y + 7 - k);
    printf("              ");
    gotoxy(x, y + 8 - k);
    printf("              ");
    gotoxy(x, y + 9 - k);
    printf("              ");
}

void drawSittingIronMan(int x, int y) {
    gotoxy(x, y + 1);
    printf("  мллллллллм  ");
    gotoxy(x, y + 2);
    printf(" лллллллллллл ");
    gotoxy(x, y + 3);
    printf(" лллммлллммлл ");
    gotoxy(x, y + 4) ;
    printf(" лллллппплллл ");
    gotoxy(x, y + 5);
    printf(" ппллллллллпп ");
    gotoxy(x, y + 6);
    printf(" мллллппплллм ");
    gotoxy(x, y + 7);
    printf("мллллллмлллллм");
    gotoxy(x, y + 8);
    printf("пп лллллллл пп");
    gotoxy(x, y + 9);
    printf("  мллл лллм   ");
    wait(15);
}

void deleteSittingIronMan(int x, int y) {
    gotoxy(x, y + 1);
    printf("              ");
    gotoxy(x, y + 2);
    printf("              ");
    gotoxy(x, y + 3) ;
    printf("              ");
    gotoxy(x, y + 4);
    printf("              ");
    gotoxy(x, y + 5);
    printf("              ");
    gotoxy(x, y + 6);
    printf("              ");
    gotoxy(x, y + 7);
    printf("              ");
    gotoxy(x, y + 8);
    printf("              ");
    gotoxy(x, y + 9);
    printf("              ");
}

void drawDeadIronMan(int x, int y, int jump) {
	if (jump <= 2) {
		gotoxy(x, y + 2 - k);
    	printf(" лллмXлллXмлл ");
    } else {
    	gotoxy(x, y + 3);
    	printf(" лллмXлллXмлл ");
    }
}
	
	//managing character
void drawDino(int x, int y, int jump, int choice) {
    if (choice == 1) drawDino1(x, y, jump);
    if (choice == 2) drawKaonashi(x, y, jump);
    if (choice == 3) drawIronMan(x, y, jump);
}

void deleteDino(int x, int y, int jump, int choice) {
    if (choice == 1) deleteDino1(x, y, jump);
    if (choice == 2) deleteKaonashi(x, y, jump);
    if (choice == 3) deleteIronMan(x, y, jump);
}

void drawSittingDino(int x, int y, int choice) {
    if (choice == 1) drawSittingDino1(x, y);
    if (choice == 2) drawSittingKaonashi(x, y);
    if (choice == 3) drawSittingIronMan(x, y);
}

void deleteSittingDino(int x, int y, int choice) {
    if (choice == 1) deleteSittingDino1(x, y);
    if (choice == 2) deleteSittingKaonashi(x, y);
    if (choice == 3) deleteSittingIronMan(x, y);
}

void drawDeadDino(int x, int y, int jump, int choice) {
	if (choice == 1) drawDeadDino1(x, y, jump);
	if (choice == 2) drawDeadKaonashi(x, y, jump);
	if (choice == 3) drawDeadIronMan(x, y, jump);
}

//handling obstacle
void printObstacle(int type, int x, int y0, int height) {
	switch (type) {
		case 1: // 1 large (height = 5, breadth = 3
			gotoxy(x, y0 - 4); printf(" %c%c  ", 186, 186);
			gotoxy(x, y0 - 3); printf("%c%c%c  ", 186, 186, 186);
			gotoxy(x, y0 - 2); printf("%c%c%c  ", 186, 204, 188);
			gotoxy(x, y0 - 1); printf("%c%c  ", 200, 185);
			gotoxy(x, y0);     printf(" %c  ", 186);
			break;		
		case 2: // 1 small (height = 3, breadth = 2
			gotoxy(x, y0 - 2); printf(" %c%c  ", 186, 186);
			gotoxy(x, y0 - 1); printf(" %c%c  ", 200, 186);
			gotoxy(x, y0);     printf("  %c  ", 186);
			break;
		case 3: // 1 large + 1 small (breadth = 5)
			gotoxy(x, y0 - 4); printf(" %c%c  ", 186, 186);		
			gotoxy(x, y0 - 3); printf("%c%c%c  ", 186, 186, 186);	
			gotoxy(x, y0 - 2); printf("%c%c%c", 186, 204, 188); printf("%c%c  ", 186, 186);
			gotoxy(x, y0 - 1); printf("%c%c ", 200, 185); 		printf("%c%c  ", 200, 186);
			gotoxy(x, y0);     printf(" %c ", 186); 			printf(" %c  ", 186);
			break;	
		case 4: // 1 large + 1 small + 1 large (breadth = 8)
			gotoxy(x, y0 - 4); printf(" %c%c  ", 186, 186); 		printf(" %c%c  ", 186, 186);			
			gotoxy(x, y0 - 3); printf("%c%c%c  ", 186, 186, 186); 	printf("%c%c%c  ", 186, 186, 186);	
			gotoxy(x, y0 - 2); printf("%c%c%c", 186, 204, 188); 	printf("%c%c", 186, 186); 			printf("%c%c%c  ", 186, 204, 188);
			gotoxy(x, y0 - 1); printf("%c%c ", 200, 185); 			printf("%c%c", 200, 186); 			printf("%c%c  ", 200, 185);
			gotoxy(x, y0);     printf(" %c ", 186); 				printf(" %c", 186); 				printf(" %c  ", 186);
			break;	
		case 5: // 1 large + 1 small + 1 large + 1 large (breadth = 11)
			gotoxy(x, y0 - 4); printf(" %c%c  ", 186, 186); 		printf(" %c%c", 186, 186); 			printf(" %c%c  ", 186, 186);   		
			gotoxy(x, y0 - 3); printf("%c%c%c  ", 186, 186, 186); 	printf("%c%c%c", 186, 186, 186); 	printf("%c%c%c  ", 186, 186, 186);	
			gotoxy(x, y0 - 2); printf("%c%c%c", 186, 204, 188); 	printf("%c%c", 186, 186); 			printf("%c%c%c", 186, 204, 188); 	printf("%c%c%c  ", 186, 204, 188);
			gotoxy(x, y0 - 1); printf("%c%c ", 200, 185); 			printf("%c%c", 200, 186); 			printf("%c%c ", 200, 185); 			printf("%c%c  ", 200, 185);
			gotoxy(x, y0);     printf(" %c ", 186); 				printf(" %c", 186); 				printf(" %c ", 186); 				printf(" %c  ", 186);
			break;
		case 6: // helicopter 1 height = 8 
			gotoxy(x, y0 - height - 3); 	printf("________   ");
			gotoxy(x, y0 - height - 2); 	printf("  ,-'-.____()  ");
			gotoxy(x, y0 - height - 1); 	printf(" (____.--'''   ");
			gotoxy(x, y0 - height); 		printf(" -'--'-   ");
		default: break;
		
	}
}

void disappearObstacle(int x, int y0, int type, int height) {
// helicopter
	if (type == 6) {
		gotoxy(x, y0 - height - 3);		printf("                ");
		gotoxy(x, y0 - height - 2); 	printf("                ");
		gotoxy(x, y0 - height - 1); 	printf("                ");
		gotoxy(x, y0 - height); 		printf("                ");
	}
// cactus
	else {
		gotoxy(x, y0 - 4); printf("               ");
		gotoxy(x, y0 - 3); printf("               ");
		gotoxy(x, y0 - 2); printf("               ");
		gotoxy(x, y0 - 1); printf("               ");
		gotoxy(x, y0);     printf("               ");
	}
}

void drawMetiorite(int x, int y0) {
    gotoxy(x, y0 - 7);
    printf("        ");
	gotoxy(x, y0 - 6);
    printf("м      л");
    gotoxy(x, y0 - 5);
    printf("л  м пмл");
    gotoxy(x, y0 - 4);
    printf("л л пм л");
    gotoxy(x, y0 - 3);
    printf("лллллллл");
    gotoxy(x, y0 - 2);
    printf("лллллллл");
    gotoxy(x, y0 - 1);
    printf("лллллллл");
    gotoxy(x, y0);
    printf(" ппллпп ");
}

void deleteMetiorite(int x, int y0) {
	gotoxy(x, y0 - 7);
    printf("        ");
    gotoxy(x, y0 - 6);
    printf("        ");
    gotoxy(x, y0 - 5);
    printf("        ");
    gotoxy(x, y0 - 4);
    printf("        ");
    gotoxy(x, y0 - 3);
    printf("        ");
    gotoxy(x, y0 - 2);
    printf("        ");
    gotoxy(x, y0 - 1);
    printf("        ");
    gotoxy(x, y0);
    printf("        ");
}

void drawGameOver(int x, int y, int score, int bestScore) {
    //draw Game
    gotoxy(x, y);
    printf("млпллм  млпплм  ллм млл  ллпппп");
    gotoxy(x, y + 1);
    printf("лл      лл  лл  ллллллл  лл    ");
    gotoxy(x, y + 2);
    printf("лл плл  ллпплл  лл п лл  ллпп  ");
    gotoxy(x, y + 3);
    printf("плммлл  лл  лл  лл   лл  ллмммм");

    //draw Over
    gotoxy(x, y + 5);
    printf("млпплм  лл  лл  ллпппп   ллпплм");
    gotoxy(x, y + 6);
    printf("лл  лл  лл  лл  лл       лл  лл");
    gotoxy(x, y + 7);
    printf("лл  лл  пллллп  ллпп     ллплл ");
    gotoxy(x, y + 8);
    printf("плммлп   пллп   ллмммм   лл  лл");
    
    //draw your score
    gotoxy(x + 8, y + 10);
    printf("Your Score: %d", score);
    gotoxy(x + 8, y + 11);
    printf("Best Score: %d", bestScore);
}

void drawBorderGameOver(int x, int y) {
    int i, j;
    //delete around
	for (i = -1; i <= 20; i++) {
    	for (j = -1; j <= 42; j++) {
    		gotoxy(x + j, y + i);
			printf(" ");
    	}
    }
    
	//top
    for (i = 0; i < 42; i++)
    {
    	gotoxy(x + i, y);
    	printf("л");
    }
    //bottom
    for (i = 0; i < 42; i++)
    {
    	gotoxy(x + i, y + 20);
    	printf("л");
    }
    //left
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x, y + i);
        printf("л");
    }
    //right
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x + 41, y + i);
        printf("л");
    }
}

//collision
int checkCollision(int x, int y, int jump, int obstacleType, int obstaclePos, int y0, int height, int choice) {
	int i, j, yx[32][151];
	
	//set 0
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 151; j++) {
			yx[i][j] = 0;
		}
	}
	
	//set dino position
	if (choice == 1) { //dino1
		if (jump <= 2) {
			for (i = 9; i <= 16; i++) {
				yx[y + 1 - k][x + i] = 1;
			}
			yx[y + 2 - k][x + 9] = 1;
			yx[y + 2 - k][x + 16] = 1;
			yx[y + 3 - k][x + 9] = 1;
			yx[y + 3 - k][x + 16] = 1;
			yx[y + 4 - k][x + 1] = 1;
			yx[y + 4 - k][x + 8] = 1;
			yx[y + 4 - k][x + 15] = 1;
			yx[y + 5 - k][x + 1] = 1;
			yx[y + 5 - k][x + 15] = 1;
			yx[y + 6 - k][x + 1] = 1;
			yx[y + 6 - k][x + 15] = 1;
			yx[y + 7 - k][x + 3] = 1;
			yx[y + 7 - k][x + 3] = 1;
			yx[y + 7 - k][x + 4] = 1;
			yx[y + 7 - k][x + 5] = 1;
			yx[y + 7 - k][x + 9] = 1;
			yx[y + 7 - k][x + 10] = 1;
			yx[y + 7 - k][x + 11] = 1;
			if (jump == 1 || jump == 2) {
				yx[y + 8 - k][x + 4] = 1;
				yx[y + 8 - k][x + 9] = 1;
				yx[y + 9 - k][x + 4] = 1;
				yx[y + 9 - k][x + 5] = 1;
				yx[y + 9 - k][x + 9] = 1;
				yx[y + 9 - k][x + 10] = 1;
			}
			
		}
		else {
			for (i = 11; i <= 17; i++) {
				yx[y + 2][x + i] = 1;
			}
			yx[y + 3][x + 11] = 1;
			yx[y + 3][x + 17] = 1;
			yx[y + 4][x + 11] = 1;
			yx[y + 4][x + 17] = 1;
			yx[y + 5][x + 8] = 1;
			yx[y + 5][x + 17] = 1;
			yx[y + 6][x + 7] = 1;
			yx[y + 6][x + 17] = 1;
			yx[y + 7][x + 6] = 1;
			yx[y + 7][x + 17] = 1;
			yx[y + 8][x] = 1;
			yx[y + 8][x + 4] = 1;
			yx[y + 9][x] = 1;
			yx[y + 9][x + 17] = 1;
		}
	}
	
	else if (choice == 2) { //kaonashi
		if (jump <= 2) {
			for (i = 4; i <= 13; i++) {
				yx[y - k][x + i] = 1;
			}
			yx[y + 1 - k][x + 3] = 1;
			yx[y + 1 - k][x + 15] = 1;
			yx[y + 2 - k][x + 2] = 1;
			yx[y + 2 - k][x + 16] = 1;
			yx[y + 3 - k][x + 1] = 1;
			yx[y + 3 - k][x + 16] = 1;
			yx[y + 4 - k][x + 1] = 1;
			yx[y + 4 - k][x + 16] = 1;
			yx[y + 5 - k][x + 1] = 1;
			yx[y + 5 - k][x + 18] = 1;
			if (jump == 1 || jump == 2) {
				yx[y + 6 - k][x + 2] = 1;
				yx[y + 6 - k][x + 17] = 1;
				yx[y + 7 - k][x + 3] = 1;
				yx[y + 7 - k][x + 15] = 1;
				yx[y + 8 - k][x + 4] = 1;
				yx[y + 8 - k][x + 13] = 1;
				yx[y + 9 - k][x + 7] = 1;
				yx[y + 9 - k][x + 11] = 1;
			}
			else {
				yx[y + 6 - k][x + 1] = 1;
				yx[y + 6 - k][x + 17] = 1;
				yx[y + 7 - k][x + 1] = 1;
				yx[y + 7 - k][x + 16] = 1;
				yx[y + 8 - k][x + 1] = 1;
				yx[y + 8 - k][x + 2] = 1;
				yx[y + 8 - k][x + 3] = 1;
				yx[y + 8 - k][x + 4] = 1;
				yx[y + 8 - k][x + 13] = 1;
				yx[y + 8 - k][x + 14] = 1;
				yx[y + 8 - k][x + 15] = 1;
				yx[y + 8 - k][x + 16] = 1;
				yx[y + 9 - k][x + 1] = 1;
				yx[y + 9 - k][x + 16] = 1;
			}
		}
		else {
			for (i = 4; i <= 13; i++) {
				yx[y + 2][x + i] = 1;
			}
			yx[y + 3][x + 3] = 1;
			yx[y + 3][x + 15] = 1;
			yx[y + 4][x + 2] = 1;
			yx[y + 4][x + 16] = 1;
			yx[y + 5][x + 1] = 1;
			yx[y + 5][x + 16] = 1;
			yx[y + 6][x + 1] = 1;
			yx[y + 6][x + 16] = 1;
			yx[y + 7][x + 1] = 1;
			yx[y + 7][x + 18] = 1;
			yx[y + 8][x + 1] = 1;
			yx[y + 8][x + 18] = 1;
			yx[y + 9][x + 1] = 1;
			yx[y + 9][x + 16] = 1;
		}
	}
	else if (choice == 3) { //Iron man
		if (jump <= 2) {
			for (i = 2; i <= 11; i++) {
				yx[y - k][x + i] = 1;
			}
			for (i = 1; i <= 5; i++) {
				yx[y - k + i][x + 1] = 1;
				yx[y - k + i][x + 12] = 1;
			}
			yx[y + 6 - k][x] = 1;
			yx[y + 6 - k][x + 13] = 1;
			yx[y + 7 - k][x] = 1;
			yx[y + 7 - k][x + 13] = 1;
			yx[y + 7 - k][x + 2] = 1;
			yx[y + 7 - k][x + 12] = 1;
			yx[y + 8 - k][x + 3] = 1;
			yx[y + 8 - k][x + 4] = 1;
			yx[y + 8 - k][x + 5] = 1;
			yx[y + 8 - k][x + 6] = 1;
			yx[y + 8 - k][x + 7] = 1;
			yx[y + 8 - k][x + 8] = 1;
			yx[y + 9 - k][x + 3] = 1;
			yx[y + 9 - k][x + 4] = 1;
			yx[y + 9 - k][x + 5] = 1;
			yx[y + 9 - k][x + 7] = 1;
			yx[y + 9 - k][x + 8] = 1;
			
		}
		else {
			for (i = 2; i <= 11; i++) {
				yx[y + 1][x + i] = 1;
			}
			for (i = 2; i <= 6; i++) {
				yx[y + i][x + 1] = 1;
				yx[y + i][x + 12] = 1;
			}
			yx[y + 7][x] = 1;
			yx[y + 7][x + 13] = 1;
			yx[y + 8][x] = 1;
			yx[y + 8][x + 13] = 1;
		}
	}
	
	//check obstacle position
	switch(obstacleType) {
		case 1:
			if (yx[y0 - 4][obstaclePos + 1]) return 1;
			if (yx[y0 - 4][obstaclePos + 2]) return 1;
			if (yx[y0 - 3][obstaclePos]) return 1;
			if (yx[y0 - 3][obstaclePos + 2]) return 1;
			if (yx[y0 - 2][obstaclePos]) return 1;
			if (yx[y0 - 2][obstaclePos + 2]) return 1;
			break;
		case 2:
			if (yx[y0 - 2][obstaclePos + 1]) return 1;
			if (yx[y0 - 2][obstaclePos + 2]) return 1;
			if (yx[y0 - 1][obstaclePos + 1]) return 1;
			if (yx[y0 - 1][obstaclePos + 2]) return 1;
			break;
		case 3:
			if (yx[y0 - 4][obstaclePos + 1]) return 1;
			if (yx[y0 - 4][obstaclePos + 2]) return 1;
			if (yx[y0 - 3][obstaclePos]) return 1;
			if (yx[y0 - 3][obstaclePos + 2]) return 1;
			if (yx[y0 - 2][obstaclePos]) return 1;
			if (yx[y0 - 2][obstaclePos + 3]) return 1;
			if (yx[y0 - 2][obstaclePos + 4]) return 1;
			if (yx[y0 - 1][obstaclePos]) return 1;
			if (yx[y0 - 1][obstaclePos + 4]) return 1;
			break;
		case 4:
			if (yx[y0 - 4][obstaclePos + 1]) return 1;
			if (yx[y0 - 4][obstaclePos + 2]) return 1;
			if (yx[y0 - 4][obstaclePos + 6]) return 1;
			if (yx[y0 - 4][obstaclePos + 7]) return 1;
			if (yx[y0 - 4][obstaclePos + 8]) return 1;
			if (yx[y0 - 4][obstaclePos + 9]) return 1;
			if (yx[y0 - 3][obstaclePos]) return 1;
			if (yx[y0 - 3][obstaclePos + 7]) return 1;
			if (yx[y0 - 3][obstaclePos + 8]) return 1;
			if (yx[y0 - 2][obstaclePos]) return 1;
			if (yx[y0 - 2][obstaclePos + 6]) return 1;
			if (yx[y0 - 2][obstaclePos + 7]) return 1;
			if (yx[y0 - 2][obstaclePos + 8]) return 1;
			if (yx[y0 - 1][obstaclePos]) return 1;
			if (yx[y0 - 1][obstaclePos + 6]) return 1;
			break;
		case 5:
			if (yx[y0 - 4][obstaclePos + 1]) return 1;
			if (yx[y0 - 4][obstaclePos + 2]) return 1;
			if (yx[y0 - 4][obstaclePos + 6]) return 1;
			if (yx[y0 - 4][obstaclePos + 7]) return 1;
			if (yx[y0 - 4][obstaclePos + 9]) return 1;
			if (yx[y0 - 4][obstaclePos + 10]) return 1;
			if (yx[y0 - 4][obstaclePos + 11]) return 1;
			if (yx[y0 - 4][obstaclePos + 12]) return 1;
			if (yx[y0 - 3][obstaclePos]) return 1;
			if (yx[y0 - 3][obstaclePos + 10]) return 1;
			if (yx[y0 - 3][obstaclePos + 11]) return 1;
			if (yx[y0 - 3][obstaclePos + 12]) return 1;
			if (yx[y0 - 2][obstaclePos]) return 1;
			if (yx[y0 - 2][obstaclePos + 10]) return 1;
			if (yx[y0 - 2][obstaclePos + 11]) return 1;
			if (yx[y0 - 1][obstaclePos]) return 1;
			if (yx[y0 - 1][obstaclePos + 9]) return 1;
			break;
		case 6:
			for (i = 0; i <= 7; i++) {
				if (yx[y0 - height - 3][obstaclePos + i]) return 1;
			}
			if (yx[y0 - height - 2][obstaclePos + 11]) return 1;
			if (yx[y0 - height - 2][obstaclePos + 12]) return 1;
			if (yx[y0 - height - 1][obstaclePos + 1]) return 1;
			if (yx[y0 - height - 1][obstaclePos + 10]) return 1;
			if (yx[y0 - height - 1][obstaclePos + 11]) return 1;
			for (i = 1; i <= 6; i++) {
				if (yx[y0 - height][obstaclePos + i]) return 1;
			}
			break;
		case 7:
			if (yx[y0 - 2][obstaclePos + 1]) return 1;
			if (yx[y0 - 2][obstaclePos + 2]) return 1;
			if (yx[y0 - 1][obstaclePos + 1]) return 1;
			if (yx[y0 - 1][obstaclePos + 2]) return 1;
			break;
		case 8:
			for (i = 6; i >= 1; i--) {
				if (yx[y0 - i][obstaclePos]) return 1;
				if (yx[y0 - i][obstaclePos + 7]) return 1;
			}
			for (i = 1; i <= 6; i++) {
				if (yx[y0][obstaclePos + i]) return 1;
			}
			break;
	}
	return 0;
}		
	
//functions to run game
void NEWGAME(int choice) {
	gotoxy(2, 39); printf("> Click on the screen to PAUSE, press ENTER to CONTINUE, ESC to exit.                     ");
	//variables
	struct character object, cloud1, cloud2, cloud3, star, dino, metiorite;
	int score = 0, t, i, count = 0, jump = 0, flag = 0;  
    char inputKey;
    int y0 = 31;
    int obstaclePos = 154, obstacleType, obstacle = 0;
    float time = 20;
    int dayOrNight = 0; 	//dayOrNight = 1: day
    						//dayOrNight = 0: night
    
	//initialize objects
	initializeGround(ground);
	object.x = 70;
	object.y = 2;
	cloud1.x = 4;
	cloud1.y = 3;
	cloud2.x = 33;
	cloud2.y = 5;
	cloud3.x = 100;
	cloud3.y = 6;
	star.x = 140;
	star.y = 5;
	dino.x = 15;
    dino.y = 22;

	drawSun(object.x, object.y);
	drawCloud(cloud1.x, cloud1.y);
	drawCloud(cloud2.x, cloud2.y);
	drawCloud(cloud3.x, cloud3.y);
	
	//height of the helicopter
	int height;
	if (choice == 1 || choice == 2) height = 8;
	else height = 9;
	
	//playing game
	while(1) {
		//Display score
		gotoxy(2,0);
		printf("Score: %d", score);
		
		//day or night and display sun or moon
		if (score % 2000 == 0) {
			if (dayOrNight == 0) {
				dayOrNight = 1;
				deleteStar(star.x, star.y);
				system("color 70");
				playSceneSound(); //music
			}
			else {
				dayOrNight = 0;
				deleteSun(object.x, object.y);
				system("color 07");
				playSceneSound(); //music
			}
		}
		if (dayOrNight == 1) {
			object.x--;
			drawSun(object.x, object.y);
			if (object.x == 0) {
				deleteSun(object.x, object.y);
				object.x = 125;
			}
		}
		else {
			object.x--;
			drawMoon(object.x, object.y + 2);
			if (object.x == 0) {
				deleteMoon(object.x, object.y + 2);
				object.x = 125;
			}
		}
		
		//display star
		if (dayOrNight == 0) {
			deleteStar(star.x, star.y);
			t = random(5);
			switch(t) {
				case 1: 
					star.x = 10; star.y = 3;
					drawStar(star.x, star.y);
					break;
				case 2: 
					star.x = 80; star.y = 2;
					drawStar(star.x, star.y);
					break;
				case 3: 
					star.x = 30; star.y = 14;
					drawStar(star.x, star.y);
					break;
				case 4: 
					star.x = 100; star.y = 15;
					drawStar(star.x, star.y);
					break;
				case 5: 
					star.x = 140; star.y = 10;
					drawStar(star.x, star.y);
					break;
			}
		}
		
		//display cloud1
		cloud1.x--;
		drawCloud(cloud1.x, cloud1.y);
		if (cloud1.x == 0) {
			deleteCloud(cloud1.x, cloud1.y);
			cloud1.x = 125;
		}
		
		//display cloud2
		cloud2.x--;
		drawCloud(cloud2.x, cloud2.y);
		if (cloud2.x == 0) {
			deleteCloud(cloud2.x, cloud2.y);
			cloud2.x = 125;
		}
		
		//display cloud3
		cloud3.x--;
		drawCloud(cloud3.x, cloud3.y);
		if (cloud3.x == 0) {
			deleteCloud(cloud3.x, cloud3.y);
			cloud3.x = 125;
		}
		
		//display Ground	
		moveGround(ground);
		
		//move dino
        if (jump == 0) drawDino(dino.x, dino.y, 0, choice);
        if (jump == 3) drawSittingDino(dino.x, dino.y, choice);
        if (kbhit() && (jump == 0 || jump == 3)) {
	        inputKey = getch();
	        if (inputKey == 'w') {
	        	if (jump == 3) deleteSittingDino(dino.x, dino.y, choice);
	        	playJumpSound(); //music
				jump = 1;
			}
	        else if (inputKey == 'd') {
	        	if (jump == 3) {
	        		deleteSittingDino(dino.x, dino.y, choice);
	        		jump = 0;
	        	}
	        	else {
	            	deleteDino(dino.x, dino.y, 0, choice);
	            }
	            if (dino.x <= 110) dino.x += 3;
	            else dino.x = 113;
	            drawDino(dino.x, dino.y, 0, choice);
	        }
	        else if (inputKey == 'a') {
	            if (jump == 3) {
	        		deleteSittingDino(dino.x, dino.y, choice);
	        		jump = 0;
	        	}
	        	else {
	            	deleteDino(dino.x, dino.y, 0, choice);
	            }
	            if (dino.x >= 18) dino.x -= 3;
	            else dino.x = 15;
	            drawDino(dino.x, dino.y, 0, choice);
	        }
	        else if (inputKey == 's') {
	            deleteDino(dino.x, dino.y, 0, choice);
	        	drawSittingDino(dino.x, dino.y, choice);
	        	playJumpSound(); //music
				jump = 3;  
	        }
	        else if (inputKey == 27) {
	        	clrscr();
	        	flagMusic = 1;
	        	Main_Menu();
	        }
		}
		if (jump == 1) {
			drawDino(dino.x, dino.y, 1, choice);
			if (count < 11) count++;
			if (count == 11) jump = 2;
		}
		else if (jump == 2) {
			if (count > 1) drawDino(dino.x, dino.y, 2, choice);
			else if (count == 1) drawDino(dino.x, dino.y, 0, choice);
			count--;
			if (count == 0) jump = 0;
		}
		
		//draw obstacles
		if (obstacle == 0) {
			obstacle = 1;
			if (score < 1000) obstacleType = random(6);
			else if (score < 2000) random(7);
			else if (score < 5000) obstacleType = random(8);
			else obstacleType = random(9);
			if (obstacleType == 1) obstaclePos = 154 - 10;
			if (obstacleType == 2) obstaclePos = 154 - 10;
			if (obstacleType == 3) obstaclePos = 154 - 10;
			if (obstacleType == 4) obstaclePos = 154 - 14;
			if (obstacleType == 5) obstaclePos = 154 - 18;
			if (obstacleType == 6) obstaclePos = 154 - 18;
			if (obstacleType == 7) {
				obstaclePos = 4;
				flag = 1;
			}
			if (obstacleType == 8 || obstacleType == 9) {
				obstacleType = 8;
				flag = 2;
				if (choice == 1 || choice == 2) metiorite.x = dino.x + 15;
				else metiorite.x = dino.x + 10;
				metiorite.y = 8;
			}
			
		}
		
		if (obstacle == 1) {
			if (flag == 0) {
				obstaclePos -= 1.5;
				printObstacle(obstacleType, obstaclePos, y0, height);
			}
			else if (flag == 1) {
				obstaclePos += 1.5;
				printObstacle(2, obstaclePos, y0, height);
			}
			else if (flag == 2) {
				metiorite.y++;
				drawMetiorite(metiorite.x, metiorite.y);
			}
		}
		
		if (flag == 0 && obstaclePos == 2) {
			obstacle = 0;
			disappearObstacle(obstaclePos, y0, obstacleType, height);
		}
		if (flag == 1 && obstaclePos == 154 - 9) {
			obstacle = 0;
			disappearObstacle(obstaclePos, y0, 2, height);
			flag = 0;
		}
		if (flag == 2 && metiorite.y == 31) {
			obstacle = 0;
			deleteMetiorite(metiorite.x, metiorite.y);
			flag = 0;
		}
		
		// execute collision
		if (obstacleType <= 7) {
			if (checkCollision(dino.x, dino.y, jump, obstacleType, obstaclePos, y0, height, choice) == 1) {
				drawDeadDino(dino.x, dino.y, jump, choice);
				playDeadMusic(); //music
				gotoxy(2, 0);  printf("             ");
				if (score > bestScore) bestScore = score;
				drawBorderGameOver(53, 7);
				drawGameOver(58, 12, score, bestScore);
				gotoxy(2, 39); printf("> Press ENTER to play again, press ESC to exit.                     ");
				break;
			}
		}
		else {
			if (checkCollision(dino.x, dino.y, jump, obstacleType, metiorite.x, metiorite.y, height, choice) == 1) {
				drawDeadDino(dino.x, dino.y, jump, choice);
				playDeadMusic(); //music
				gotoxy(2, 0);  printf("             ");
				if (score > bestScore) bestScore = score;
				drawBorderGameOver(53, 7);
				drawGameOver(58, 12, score, bestScore);
				gotoxy(2, 39); printf("> Press ENTER to play again, press ESC to exit.                     ");
				break;
			}
		}

		//Handling score and time
		score += 5;
		if (score >= 1000 && score % 500 == 0 && time >= 0.25) time -= 3.95;
		wait(time);   
	}		
	
	if (score > bestScore) bestScore = score;
	Recording();
	while (1) {
		char move = getch();
		if (move == 27) {
			flagMusic = 1;
			Main_Menu();
		}
		else if (move == 13) {
			playingStatus = 0;
			chooseCharacter();
		}
	}
}

//function to choose character
void drawDino1_ch(int x, int y) {
    gotoxy(x, y );
    printf("                 ");
    gotoxy(x, y + 1);
    printf("         млпллллм ");
    gotoxy(x, y + 2);
    printf("         лллллллл ");
    gotoxy(x, y + 3);
    printf("         лллллппп ");
    gotoxy(x, y + 4);
    printf(" л      мллллппп  ");
    gotoxy(x, y + 5);
    printf(" ллм  мллллллммм  ");
    gotoxy(x, y + 6);
    printf(" пллллллллллл  п  ");
    gotoxy(x, y + 7);
    printf("   плллллллп      ");
    gotoxy(x, y + 8);
    printf("    ллп пл        ");
    gotoxy(x, y + 9);
    printf("    лм   лм       ");
    gotoxy(x, y + 10);
    printf("                  ");

}

void drawKaonashi_ch(int x, int y) {
    gotoxy(x, y - 1);
    printf("                   ");
    gotoxy(x, y);
    printf("    ммллппппмм     ");
    gotoxy(x, y + 1);
    printf("   лллп л    лпм   ");
    gotoxy(x, y + 2);
    printf("  лллп  мм   ммпм  ");
    gotoxy(x, y + 3);
    printf(" мллл   м     м л  ");
    gotoxy(x, y + 4);
    printf(" ллллм  п пмп п л  ");
    gotoxy(x, y + 5);
    printf(" ллллллм      млллл");
    gotoxy(x, y + 6);
    printf(" ллллллллллллллллл ");
    gotoxy(x, y + 7);
    printf(" лллллллллллллллм  ");
    gotoxy(x, y + 8);
    printf(" лллллллллллллллл  ");
    gotoxy(x, y + 9);
    printf("мллллллллллллллллм ");
    gotoxy(x, y + 10);
    printf("                   ");  
}

void drawIronMan_ch(int x, int y) {
	gotoxy(x, y - 1);
    printf("              ");
    gotoxy(x, y);
    printf("  мллллллллм  ");
    gotoxy(x, y + 1);
    printf(" лллллллллллл ");
    gotoxy(x, y + 2);
    printf(" лллммлллммлл ");
    gotoxy(x, y + 3);
    printf(" лллллппплллл ");
    gotoxy(x, y + 4);
    printf(" ппллллллллпп ");
    gotoxy(x, y + 5);
    printf(" мллллппплллм ");
    gotoxy(x, y + 6);
    printf("мллллллмлллллм");
    gotoxy(x, y + 7);
    printf("пп лллллллл пп");
    gotoxy(x, y + 8);
    printf("   ллл ллл    ");
    gotoxy(x, y + 9);
    printf("   ллп пп     ");
}

void drawBorder(int x, int y) {
    int i;
    //top
    for (i = 0; i <= 96; i++) {
    	gotoxy(x + i, y);
    	printf("л");
    }
    //bottom
    for (i = 0; i <= 96; i++) {
    	gotoxy(x + i, y + 20);
    	printf("л");
    }
    //left
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x, y + i);
        printf("л");
    }
    //right
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x + 96, y + i);
        printf("л");
    }
    //mid1 
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x + 32, y + i);
        printf("л");
    }
    //mid2 
    for (i = 1; i <= 19; i++)
    {
        gotoxy(x + 64, y + i);
        printf("л");
    }
}

void drawDino1Select(int x, int y, int space) {
    changeColor(15);
    gotoxy(x + space, y);
    printf("     KAONASHI     ");
    gotoxy(x + 2 * space - 3, y);
    printf("     IRON-MAN     ");
    gotoxy(x, y);
    changeColor(96);
    printf("    >> T-REX <<   ");
}

void drawKaonashiSelect(int x, int y, int space) {
    changeColor(15);
    gotoxy(x, y);
    printf("       T-REX      ");
    gotoxy(x + 2 * space - 3, y);
    printf("     IRON-MAN     ");
    gotoxy(x + space, y);
    changeColor(96);
    printf("  >> KAONASHI <<  ");
}

void drawIronManSelect(int x, int y, int space) {
	changeColor(15);
    gotoxy(x, y);
    printf("       T-REX      ");
    gotoxy(x + space, y);
    printf("     KAONASHI     ");
    gotoxy(x + 2 * space - 3, y);
    changeColor(96);
    printf("  >> IRON-MAN <<  ");
}

void chooseCharacter() {
	// clear welcome screen
	changeColor(15);				
	clrscr();
	int ix, jx;
	for (ix = 0; ix <= 150; ix++) 
		for (jx = 0; jx <= 40; jx++) {
			gotoxy(ix, jx);
			printf(" ");
		}
		
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ENTER to select, A to slide left, D to slide right, ESC to exit.                   ");
	changeColor(15);
	
	//choose character
	char inputKey;
    int i, choice, x = 30, y = 15, space = 35, character = 1;
    
    drawDino1_ch(x, y);
    drawKaonashi_ch(x + space, y);
    drawIronMan_ch(x + 2 * space - 1, y);
    drawDino1Select(x, y + 12, space);
    changeColor(9);
    drawBorder(x - 5 , y - 5);
    changeColor(15);
    
    while (1) {
        inputKey = getch();
        if (inputKey == 'd') {
            if (character == 1) {
            	drawKaonashiSelect(x, y + 12, space);
                character = 2;
        	} else if (character == 2) {
        		drawIronManSelect(x, y + 12, space);
                character = 3;
        	} else {
        		drawDino1Select(x, y + 12, space);
                character = 1;
            }
        }
		else if (inputKey == 'a') {
            if (character == 1) {
            	drawIronManSelect(x, y + 12, space);
                character = 3;
        	} else if (character == 2) {
        		drawDino1Select(x, y + 12, space);
                character = 1;
        	} else {
        		drawKaonashiSelect(x, y + 12, space);
                character = 2;
            }
        }  
		else if (inputKey == 13) {
        	clrscr();
			break;
    	} 
		else if (inputKey == 27) {
    		clrscr();
    		if (playingStatus == 1) flagMusic = 0;
    		else {
    			flagMusic = 1;
    			playingStatus = 1;
    		}
    		Main_Menu();
    	}
	}
	
    NEWGAME(character);
    return;
}

//function to design menu
void NEW_GAME_select() {
	gotoxy(59, 28);
	changeColor(207);
	printf("      >> NEW GAME <<       ");
	
	gotoxy(59, 30);
	changeColor(15);
	printf("    PROFILE AND ACCOUNT    ");
	
	gotoxy(59, 32);
	changeColor(15);
	printf("        INSTRUCTION        ");
	
	gotoxy(59, 34);
	changeColor(15);
	printf("         SIGN OUT          ");
	
	gotoxy(59, 36);
	changeColor(15);
	printf("           QUIT            ");
}

void PROFILE_AND_ACCOUNT_select() {
	gotoxy(59, 28);
	changeColor(15);
	printf("         NEW GAME          ");
	
	gotoxy(59, 30);
	changeColor(207);
	printf(" >> PROFILE AND ACCOUNT << ");
	
	gotoxy(59, 32);
	changeColor(15);
	printf("        INSTRUCTION        ");
	
	gotoxy(59, 34);
	changeColor(15);
	printf("         SIGN OUT          ");
	
	gotoxy(59, 36);
	changeColor(15);
	printf("           QUIT            ");
}

void INSTRUCTION_select() {
	gotoxy(59, 28);
	changeColor(15);
	printf("         NEW GAME          ");
	
	gotoxy(59, 30);
	changeColor(15);
	printf("    PROFILE AND ACCOUNT    ");
	
	gotoxy(59, 32);
	changeColor(207);
	printf("     >> INSTRUCTION <<     ");
	
	gotoxy(59, 34);
	changeColor(15);
	printf("         SIGN OUT          ");
	
	gotoxy(59, 36);
	changeColor(15);
	printf("           QUIT            ");
} 

void SIGN_OUT_select() {
	gotoxy(59, 28);
	changeColor(15);
	printf("         NEW GAME          ");
	
	gotoxy(59, 30);
	changeColor(15);
	printf("    PROFILE AND ACCOUNT    ");
	
	gotoxy(59, 32);
	changeColor(15);
	printf("        INSTRUCTION        ");
	
	gotoxy(59, 34);
	changeColor(207);
	printf("      >> SIGN OUT <<       ");
	
	gotoxy(59, 36);
	changeColor(15);
	printf("           QUIT            ");
} 

void QUIT_select() {
	gotoxy(59, 28);
	changeColor(15);
	printf("         NEW GAME          ");
	
	gotoxy(59, 30);
	changeColor(15);
	printf("    PROFILE AND ACCOUNT    ");
	
	gotoxy(59, 32);
	changeColor(15);
	printf("        INSTRUCTION        ");
	
	gotoxy(59, 34);
	changeColor(15);
	printf("         SIGN OUT          ");
	
	gotoxy(59, 36);
	changeColor(207);
	printf("        >> QUIT <<         ");
} 

void Change_select() {					
	gotoxy(59, 28);
	changeColor(63);
	printf(" >> CHANGE PASSWORD << ");
	
	gotoxy(59, 30);
	changeColor(15);
	printf("          RANK         ");
}

void Rank_select() {
	gotoxy(59, 28);
	changeColor(15);
	printf("    CHANGE PASSWORD    ");
	
	gotoxy(59, 30);
	changeColor(63);
	printf("       >> RANK <<      ");
}

void changePassword() { 	// Change Pasword
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ESC to exit.                                                          ");
	// cursor
	CursorType(1);
	
	changeColor(175);
	gotoxy(56, 28); printf("%c Your user's name:", 175);
  	gotoxy(56, 30); printf("%c Your recent password:", 175);
  	
  	changeColor(15);
  	gotoxy(80, 28); printf("%s", userName);
  	
  	char password_tmp[30];
  	
  	while (1) {
		gotoxy(80, 30); printf("                              ");
		
		gotoxy(80, 30); 
		// change password into a string of asterisks
				char BACKSPACE = (char) 8;
				char RETURN    = (char) 13;
				char ESCAPE    = (char) 27;
				char ch;
				int i; 
				for (i = 0; i < 30; i++) password_tmp[i] = '\0';
				int n = 0; // length of password
				while(1) {  
				    ch = getch();
				    if (ch == ESCAPE) {
				    	changeColor(15);
						gotoxy(56, 28); printf("                                            ");
						gotoxy(56, 30); printf("                                            ");
						gotoxy(56, 32); printf("                                            ");
						gotoxy(56, 34); printf("                                            ");
				    	PROFILE_AND_ACCOUNT();
				    	return;
					}
				    if (ch == RETURN && n != 0) break;
				    if (ch == BACKSPACE) {
				        if(n != 0) {
				            printf("\b \b");
				            password_tmp[n - 1] = '\0';
							n--;
				        }
				    } else if (ch != RETURN) {
				        password_tmp[n] = ch;
				        printf("*");
				        n++;
				    }
				}
				// end of change password into a string of asterisks
				
		if (strcmp(password, password_tmp) == 0) break;      // password is correct
		else {												 // password is incorrect
			gotoxy(71, 32); printf("Wrong Password. Enter Again!");
		}
	}
	gotoxy(71, 32); printf("                            ");
	
	changeColor(175);
	gotoxy(56, 32); printf("%c Your new password:", 175);
	
	changeColor(15);
	
	gotoxy(80, 32);
	// change password into a string of asterisks
				char BACKSPACE = (char) 8;
				char RETURN    = (char) 13;
				char ESCAPE    = (char) 27;
				char ch;
				int i; 
				for (i = 0; i < 30; i++) password[i] = '\0';
				int n = 0; // length of password
				while(1) {  
				    ch = getch();
				    if (ch == ESCAPE) {
				    	changeColor(15);
						gotoxy(56, 28); printf("                                            ");
						gotoxy(56, 30); printf("                                            ");
						gotoxy(56, 32); printf("                                            ");
						gotoxy(56, 34); printf("                                            ");
				    	PROFILE_AND_ACCOUNT();
				    	return;
					}
				    if (ch == RETURN && n != 0) break;
				    if (ch == BACKSPACE) {
				        if(n != 0) {
				            printf("\b \b");
				            password[n - 1] = '\0';
							n--;
				        }
				    } else if (ch != RETURN) {
				        password[n] = ch;
				        printf("*");
				        n++;
				    }
				}
				// end of change password into a string of asterisks

	gotoxy(80, 34); printf("Password Updated.");
	
	Recording();
	
	char move;
	while (1) {
		move = getch();
		if (move == 27) {
			changeColor(15);
			gotoxy(56, 28); printf("                                            ");
			gotoxy(56, 30); printf("                                            ");
			gotoxy(56, 32); printf("                                            ");
			gotoxy(56, 34); printf("                                            ");
			PROFILE_AND_ACCOUNT();
			break;
			return;
		}
	}
}

int comparator(const void* p, const void* q) { 
    return (((struct data*)q)->bestScore - ((struct data*)p)->bestScore); 
} 

void Rank() {
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ESC to exit.                                                   ");
	struct data user[6000];
	
	FILE *record;
	record = fopen("record.txt","a+");
	
	int n = 1;
	gotoxy(0, 0); 
	while (1) { 
		fgets(user[n].userName, 30, record);
		if (user[n].userName[0] == '\0') break;
	 	user[n].userName[strlen(user[n].userName) - 1] = '\0';
		
		fgets(user[n].password, 30, record);
		user[n].password[strlen(user[n].password) - 1] = '\0';
		
		fscanf(record, "%d", &user[n].bestScore);
		
		int i;
		for (i = 1; i <= n - 1; i++)	// finding a registered account with the same name before
			if (strcmp(user[i].userName, user[n].userName) == 0) {
			// update the password
				int j;
				for (j = 0; j < strlen(user[i].password); j++) user[i].password[j] = '\0';
				for (j = 0; j < strlen(user[n].password); j++)  
					user[i].password[j] = user[n].password[j];
			// update the best score
				user[i].bestScore = user[n].bestScore;
			// update the n-th element of array
					// update username
						for (j = 0; j < strlen(user[n].userName); j++) user[n].userName[j] = '\0';
					// update password
						for (j = 0; j < strlen(user[n].password); j++) user[n].password[j] = '\0';
			// break the loop as met the registered account with the same name before
				n--;
				break;
			}
		
		n++;
		char ignore[30];
		fgets(ignore, 30, record);
		fgets(ignore, 30, record);
	}
	fclose(record);
	
	n--;
	
	qsort(user + 1, n, sizeof(struct data), comparator); 
	
	gotoxy(61, 28);
	changeColor(15);  printf("1. ");
	changeColor(224); printf("%s : %d", user[1].userName, user[1].bestScore);
	
	gotoxy(61, 30);
	changeColor(15);  printf("2. ");
	changeColor(128); printf("%s : %d", user[2].userName, user[2].bestScore);
	
	gotoxy(61, 32);
	changeColor(15);  printf("3. ");
	changeColor(111); printf("%s : %d", user[3].userName, user[3].bestScore);
	
	gotoxy(61, 34);
	changeColor(15);  printf("4. ");
					  printf("%s : %d", user[4].userName, user[4].bestScore);
	
	gotoxy(61, 36);
	changeColor(15);  printf("5. ");
					  printf("%s : %d", user[5].userName, user[5].bestScore);
	
	char move;
	while (1) {
		move = getch();
		if (move == 27) {
			changeColor(15);
			gotoxy(61, 28); printf("                                   ");
			gotoxy(59, 30); printf("                                   ");
			gotoxy(61, 32); printf("                                   ");
			gotoxy(61, 34); printf("                                   ");
			gotoxy(61, 36); printf("                                   ");
			PROFILE_AND_ACCOUNT();
			return;
		}
	}
}

void PROFILE_AND_ACCOUNT() {
	// cursor
	CursorType(0);
	
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ENTER to select, W to go up, S to go down, ESC to exit.");
	
	Change_select();
	char move;
	int cur = 1;
	// cur = 1: the cursion is at Change Password tag
	// cur = 2: the cursion is at Rank tag
	while (1) {
		move = getch();
		if (move == 'w') {
			if (cur == 1) Change_select(); else
			if (cur == 2) {
				Change_select();
				cur = 1;
			} 
		}
		if (move == 's') {
			if (cur == 1) {
				Rank_select();
				cur = 2;
			} else
			if (cur == 2) Rank_select();
		}
		if (move == 13) {
			changeColor(15);
			gotoxy(59, 28); printf("                               ");
			gotoxy(59, 30); printf("                               ");
			break;
		}
		if (move == 27) {
			changeColor(15);
			gotoxy(59, 28); printf("                               ");
			gotoxy(59, 30); printf("                               ");
			flagMusic = 0;
			Main_Menu();
			return;
		}
	}
	if (cur == 1) { 	// Change password
		changePassword();
	}
	if (cur == 2) {
		Rank();
	}
}

void INSTRUCTION() {
	CursorType(0);
	changeColor(15);				// clear welcome screen
	clrscr();
	int ix, jx;
	for (ix = 0; ix <= 150; ix++) 
		for (jx = 0; jx <= 40; jx++) {
			gotoxy(ix, jx);
			printf(" ");
		}
	gotoxy(19, 3); printf("If this is your first time registering for this game and you want to skip this intruction, please press ESC");
	gotoxy(14, 4); printf("to go to main menu.");
	
	gotoxy(19, 6); printf("Welcome to the everyone-know game. If you have not really known this game yet, unplug your network, type a few");
	gotoxy(14, 7); printf("letters in the browse search box, and enjoy the original version. Just kidding, but that's why this game is called");
	gotoxy(14, 8); printf("'OUT OF INTERNET'.");
	
	gotoxy(19, 10); printf("'OUT OF INTERNET' is very simple to play. From the third perspective, you need to move a particular character over");
	gotoxy(14, 11); printf("obstacles (cacti, helicopters, or even ... meteors).");
	
	gotoxy(19, 13); printf("Control keys in the game:");
	gotoxy(24, 14); printf("+ Press 'w' KEY to control character to jump up.");
	gotoxy(24, 15); printf("+ Press 's' KEY to control character to sit down.");
	gotoxy(24, 16); printf("+ Press 'a' KEY to control character to left.");
	gotoxy(24, 17); printf("+ Press 'd' KEY to control character to right.");
	
	gotoxy(19, 19); printf("Control keys in menu:");
	gotoxy(24, 20); printf("+ Press 'w' KEY to go to the selection bar above.");
	gotoxy(24, 21); printf("+ Press 's' KEY to go to the selection bar below.");
	gotoxy(24, 22); printf("+ Press ENTER KEY to select a bar.");
	gotoxy(24, 23); printf("+ Press ESC KEY to return to the previous menu panel.");
	
	
	gotoxy(19, 26); printf("Note: + Check your 'Caps Lock' KEY to make sure the key system works.");
	
	gotoxy(25, 28); printf("+ Turn off unikey to experience this game in the most comfortable way.");
	
	gotoxy(19, 30); printf("Hope you enjoy the game,");
	
	gotoxy(19, 32); printf("Thanks,");
	
	gotoxy(19, 34); printf("'Out Of Internet' development team.");
	
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ESC to exit.                                                   ");
	
	while (1) {
		char move = getch();
		if (move == 27) {
			clrscr();
			if (signInStatus == 0) flagMusic = 0;
			else {
				flagMusic = 1;
				signInStatus = 0;
			}
			Main_Menu();
			return;
		}
		
	}
}

void Main_Menu() {
	// Clear Screen
	system("color 07");
	clrscr();
	CursorType(0);
	
	// Show name game
	printWelcomeScreen();
	NEW_GAME_select();
	
	// Show instructions
	changeColor(9);
	gotoxy(2, 39); printf("> Press ENTER to select, W to go up, S to go down.                          ");
	
	if (flagMusic == 1) playIntroMusic(); //music
	
	char move;
	int cur = 1;
	// cur = 1: the cursion is at NEW GAME tag
	// cur = 2: the cursion is at PROFILE AND ACCOUNT tag
	// cur = 3: the cursion is at INSTRUCTION tag
	// cur = 4: the cursion is at SIGN OUT tag
	// cur = 5 the cursion is at QUIT tag
  	while (1) {
			move = getch();
			if (move == 'w') {
				if (cur == 1) NEW_GAME_select(); 
				else if (cur == 2) {
					NEW_GAME_select();
					cur = 1;
				} 
				else if (cur == 3) {
					PROFILE_AND_ACCOUNT_select();
					cur = 2;
				} 
				else if (cur == 4) {
					INSTRUCTION_select();
					cur = 3;
				}
				else if (cur == 5) {
					SIGN_OUT_select();
					cur = 4;
				}
			}
			if (move == 's') {
				if (cur == 1) {
					PROFILE_AND_ACCOUNT_select();
					cur = 2;
				} else
				if (cur == 2) {
					INSTRUCTION_select();
					cur = 3;
				} else 
				if (cur == 3) {
					SIGN_OUT_select();
					cur = 4;
				} else
				if (cur == 4) {
					QUIT_select();
					cur = 5;
				}
				else QUIT_select();
			}
			
			if (move == 13) {
				changeColor(15);
				gotoxy(59, 28); printf("                               ");
				gotoxy(59, 30); printf("                               ");
				gotoxy(59, 32); printf("                               ");
				gotoxy(59, 34); printf("                               ");
				gotoxy(59, 36); printf("                               ");
				break;	
			}
	}
	
	if (cur == 1) {		// NEW GAME
		clrscr();
		chooseCharacter();
	}
	if (cur == 2) { 	// PROFILE AND ACCOUNT
		PROFILE_AND_ACCOUNT();
	}
	if (cur == 3) {		// INSTRUCTION
		clrscr();
		INSTRUCTION();
	}	
	if (cur == 4) {		// SIGN_OUT	
		LogIn_SignIn();
	}
	if (cur == 5) {		// QUIT
		gotoxy(2, 39); printf("                                                                              ");
		system("cls");
		gotoxy(2, 35);
		exit(0);
	}
}

void LogIn_SignIn() {
	//cursor
	CursorType(1);
	
	//turn off music
	turnOffMusic();
	
	//print Instruction
	changeColor(9);
	gotoxy(2, 39); printf("> Press ESC to change account.                                                        ");
	changeColor(15);
	
	//delete last account
	gotoxy(69, 32); printf("                                                                                       ");
	gotoxy(69, 34); printf("                                                                                       ");
	gotoxy(33, 36); printf("                                                                                       ");
	gotoxy(52, 38); printf("                                                                                       ");
	
	//reset score	
	bestScore = 0;
	
	//log in
	gotoxy(57, 27); printf("Please log in to your account");
	gotoxy(57, 29); printf("If you do not have, create one !");
	changeColor(79);
	gotoxy(52, 32); printf("%c User's name: ", 175);
  	gotoxy(52, 34); printf("%c Password: ", 175);
	
	changeColor(15);
	
   	FILE *record;
	int registeredAccount = 0; 
	  
	record = fopen("record.txt","a+");
	
	while (1) {
		gotoxy(69, 32); printf("                                            ");
		gotoxy(69, 32); gets(userName);
		if (userName[0] != '\0') break;
	}
		
	// check if username are registered
	while (1) {
		char userName_tmp[30];
		char ignore[30];
		fgets(userName_tmp, 30, record);
		userName_tmp[strlen(userName_tmp) - 1] = '\0';
			
		if (userName_tmp[0] == '\0') break; // check if it's the end of the list (= 0)
		
	
		if (strcmp(userName, userName_tmp) == 0) {					 // meet an registered account
			registeredAccount = 1;
			fgets(password, 30, record);
			fscanf(record, "%d", &bestScore);
			
			fgets(ignore, 30, record);
			fgets(ignore, 30, record);
		} else {
			fgets(ignore, 30, record);
			fgets(ignore, 30, record);
			fgets(ignore, 30, record);
		}
	}
				
	fclose(record);
	
	password[strlen(password) - 1] = '\0';
	
	
	
	if (registeredAccount == 1) { 			// it's a registered account >> check the password            
			
			char password_tmp[30];
			while (1) {
				gotoxy(69, 34); printf("                              ");
				
				gotoxy(69, 34); 
				// change password into a string of asterisks
				char BACKSPACE = (char) 8;
				char RETURN    = (char) 13;
				char ESCAPE    = (char) 27;
				char ch;
				int i; 
				for (i = 0; i < 30; i++) password_tmp[i] = '\0';
				int n = 0; // length of password
				while(1) { 
				    ch = getch();
				    if (ch == ESCAPE) {
				    	LogIn_SignIn();
				    	return;
					}
				    if (ch == RETURN && n != 0) break; 
				    if (ch == BACKSPACE) {
				        if(n != 0) {
				            printf("\b \b");
				            password_tmp[n - 1] = '\0';
							n--;
				        }
				    } else if (ch != RETURN) {
				        password_tmp[n] = ch;
				        printf("*");
				        n++;
				    }
				}
				// end of change password into a string of asterisks 
				
				if (strcmp(password, password_tmp) == 0) {				 // successfully log in
						gotoxy(57, 27); printf("                                             ");
						gotoxy(57, 29); printf("                                             ");
						gotoxy(52, 32); printf("                                             ");
					  	gotoxy(52, 34); printf("                                             ");
					  	gotoxy(72, 36);	printf("                                             ");
					  	flagMusic = 1;
					  	Main_Menu();
						return;         
				}
				else {												 	 // password is incorrect
					gotoxy(72, 36); 
					printf("Wrong Password. Enter Again!");
				}
			}
	} 
	else {								// if no (the username is new) >> create a new one
		while (1) {	
			gotoxy(69, 34); printf("                                                                                   ");
			gotoxy(33, 36);	printf("                                                                                        ");
			gotoxy(52, 38);	printf("                                                                                   ");
		
		// enter password - first time -
			gotoxy(69, 34);
			// change password into a string of asterisks
			char BACKSPACE = (char) 8;
			char RETURN    = (char) 13;
			char ESCAPE    = (char) 27;
			char ch;
			int i; 
			for (i = 0; i < 30; i++) password[i] = '\0';
			int n = 0; // length of password
			while(1) {  
				ch = getch();
				if (ch == ESCAPE) {
				    LogIn_SignIn();
				    return;
				}
				if (ch == RETURN && n != 0) break;
				if (ch == BACKSPACE) {
				    if(n != 0) {
				        printf("\b \b");
				        password[n - 1] = '\0';
						n--;
				    }
				} else if (ch != RETURN) {
				    password[n] = ch;
				    printf("*");
				    n++;
				}
			}
			// end of change password into a string of asterisks
				
				
		// enter password - second time -
			changeColor(79);
			gotoxy(52, 38); printf("%c Re-enter Password: ", 175);
			changeColor(15);
			gotoxy(33, 36); printf("It seems that this is the first time you have logged in. Please enter password again.");
			gotoxy(75, 38);
			char password_2[30];
			// change password into a string of asterisks
				BACKSPACE = (char) 8;
				RETURN    = (char) 13; 
				ESCAPE    = (char) 27;
				for (i = 0; i < 30; i++) password_2[i] = '\0';
				n = 0; // length of password
				while(1) {  
					ch = getch();
					if (ch == ESCAPE) {
				    	LogIn_SignIn();
				    	return;
					}
					if (ch == RETURN && n != 0) break;
					if (ch == BACKSPACE) {
					    if(n != 0) {
					        printf("\b \b");
					        password_2[n - 1] = '\0';
							n--;
					    }
					} else if (ch != RETURN) {
					    password_2[n] = ch;
					    printf("*");
					    n++;
					}
				} 
				// end of change password_2 into a string of asterisks
				if (strcmp(password, password_2) == 0) break;
				gotoxy(55, 36); printf("The password is not match!");
			}
			
			registeredAccount = 1;
			gotoxy(57, 27); printf("                                        ");
			gotoxy(57, 29); printf("                                        ");
			gotoxy(52, 32); printf("                                        ");
			gotoxy(52, 34); printf("                                        ");
			gotoxy(72, 36);	printf("                                        ");
			Recording();
			// if this is the first time users visit this game, bring them to INSTRUCTION first
			signInStatus = 1;
			INSTRUCTION();
			Main_Menu();
			return;
	}
}

void Recording() {
	FILE *record;
	record = fopen("record.txt","a+");
	fprintf(record, "%s\n", userName);
	fprintf(record, "%s\n", password);
	fprintf(record, "%d\n", bestScore);
	fprintf(record, "-----\n");
	fclose(record);
}

//play music
void playIntroMusic() {
	PlaySound(TEXT("theme.wav"), NULL, SND_ASYNC);		
}

void playJumpSound() {
	PlaySound(TEXT("jump.wav"), NULL, SND_ASYNC);	
}

void playDeadMusic() {
	PlaySound(TEXT("harrypotter.wav"), NULL, SND_ASYNC);	
}

void playSceneSound() {
	PlaySound(TEXT("scene.wav"), NULL, SND_ASYNC);
}

void turnOffMusic() {
	PlaySound(NULL, NULL, SND_ASYNC);
}


int main(){
// Handling console
	SetWindowSize(150, 40);
	SetScreenBufferSize(151, 41);
	DisableCtrButton(0, 0, 1);
   	DisableResizeWindow();
   	ShowScrollbar(0);
	srand(time(NULL));
// Showing name game
	printWelcomeScreen();
// Logging in & Signing up
	LogIn_SignIn();
	
    return 0;
}

