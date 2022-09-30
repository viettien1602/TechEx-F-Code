#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "linearFunction.h"
#include "Equations.h"
#include "CALCULATOR.h"

#define MAX_MENU_LIST 5

#define WIDTH_LAYOUR 60
#define LENGTH_LAYOUR 37

void setColor(int code)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, code);
}
void color(int idColor, int idBackGround, int idAscii)
{
    setColor( 0 << 10 | idBackGround << 4 | idColor);
    printf("%c", idAscii);
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x + 50, y};
    SetConsoleCursorPosition(h, c);
}
void returnButton(int idBackGround)
{
    setColor(0 << 10 | idBackGround << 4 | 4);
    gotoxy(27, LENGTH_LAYOUR);
}
void setBackGround(int idBackGround)
{
    int x = 5, y = 2;
    system("cls");
    gotoxy(x, y);
    setColor(8);
    for (int i = 0; i < WIDTH_LAYOUR + 2; i++)
        printf("%c", 220);
    for (int i = 0; i < LENGTH_LAYOUR; i++)
    {
        gotoxy(x, y + 1 + i);
        setColor(8);
        printf("%c", 219);

        setColor(idBackGround);
        for (int j = 0; j < WIDTH_LAYOUR; j++)
            printf("%c", 219);

        setColor(8);
        printf("%c", 219);
    }
    gotoxy(x, y + LENGTH_LAYOUR);
    setColor(8);
    for (int i = 0; i < WIDTH_LAYOUR + 2; i++) printf("%c", 223);
}
void cleanPointer()
{
    gotoxy(0, LENGTH_LAYOUR + 4);
    setColor(0 << 10 | 0 << 4 | 0);
    return;
}

void printBigNumber(int number, int x, int y, int idColor)
{
    if (number == 0)
    {
        if (number % 10 == 0)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
    }
    while (number > 0)
    {
        if (number % 10 == 0)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 1)
        {
            gotoxy(x + 2, y);
            color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x + 2, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x + 2, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x + 2, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x + 2, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 2)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);

        }
        else if (number % 10 == 3)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);

        }
        else if (number % 10 == 4)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);

        }
        else if (number % 10 == 5)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 6)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 7)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 8)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        else if (number % 10 == 9)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 3);
            color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 4);
            color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219); color(idColor, 0, 219);
        }
        x -= 7;
        number /= 10;
    }
}
void printSmallNumber(int number, int x, int y, int idColor)
{
    if (number % 10 == 0)
    {
        gotoxy(x, y);
        color(idColor, 0, 219);  color(idColor, 0, 223); color(idColor, 0, 219);
        gotoxy(x, y + 1);
        color(idColor, 0, 219);  color(0, 0, 219); color(idColor, 0, 219);
        gotoxy(x, y + 2);
        color(idColor, 0, 223);  color(idColor, 0, 223); color(idColor, 0, 223);
        gotoxy(x, y + 3);
    }
    while (number > 0)
    {
        if (number % 10 == 0)
        {
            gotoxy(x, y);
            color(idColor, 0, 219);  color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219);  color(0, 0, 219); color(0, 0, 219); color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223);  color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
            gotoxy(x, y + 3);
        }
        else if (number % 10 == 1)
        {
            gotoxy(x + 1, y);
            color(idColor, 0, 219);
            gotoxy(x + 1, y + 1);
            color(idColor, 0, 219);
            gotoxy(x + 1, y + 2);
            color(idColor, 0, 223);
        }
        else if (number % 10 == 2)
        {
            gotoxy(x, y);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 223);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
        }
        else if (number % 10 == 3)
        {
            gotoxy(x, y);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);

        }
        else if (number % 10 == 4)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(0, 0, 223); color(0, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(0, 0, 223); color(0, 0, 223); color(0, 0, 223); color(idColor, 0, 223);

        }
        else if (number % 10 == 5)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
            gotoxy(x, y + 1);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
        }
        else if (number % 10 == 6)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
        }
        else if (number % 10 == 7)
        {
            gotoxy(x, y);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(0, 0, 223); color(0, 0, 223); color(0, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(0, 0, 223); color(0, 0, 223); color(0, 0, 223); color(idColor, 0, 223);

        }
        else if (number % 10 == 8)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
        }
        else if (number % 10 == 9)
        {
            gotoxy(x, y);
            color(idColor, 0, 219); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 219);
            gotoxy(x, y + 1);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);  color(idColor, 0, 219);
            gotoxy(x, y + 2);
            color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223); color(idColor, 0, 223);
        }
        x -= 5;
        number /= 10;
    }
}
void playGameLayour()
{
    setBackGround(0);
    srand((int) time(0));
    int numberOne, numberTwo, idColor, score = 0, temp, highScore = 0, pointer = 0;
    int count = 0, mod = 5;
    int x = 43, y = 9;
    char key;
    bool flag = 0, result;
    for (int i = 3; i >= 0; i--)
    {
        printBigNumber(i, 34, 18, 15);
        Sleep(500);
        printBigNumber(i, 34, 18, 0);
        Sleep(500);
    }
    FILE *Fi, *Fo;
    Fi = fopen("score.txt", "r");
        fscanf(Fi, "%d", &highScore);
    fclose(Fi);
    if (highScore < 10)
        printSmallNumber(highScore, 6, 5, 15);
    else if (highScore < 100)
        printSmallNumber(highScore, 13, 5, 15);
    else
        printSmallNumber(highScore, 20, 5, 15);

    while( flag == 0)
    {
        gotoxy(6, 3);
        for (int i = 0; i < WIDTH_LAYOUR; i++)
            color(0, 0, 219);
        key = "";
        idColor = rand() % 14 + 1;
        for (int i = 0; i < LENGTH_LAYOUR - 6; i++)
        {
            gotoxy(6, 8 + i);
            setColor(0);
            for (int j = 0; j < WIDTH_LAYOUR; j++)
                printf("%c", 219);
        }
        printSmallNumber(score - 1, 60, 5, 0);
        printSmallNumber(score, 60, 5, 15);
        ///-----FIRST NUMBER-----///
        numberOne = rand() % mod + mod;
        if (numberOne % 10 == 0)
            numberOne++;
        printBigNumber(numberOne, x, y, idColor);

        ///---+---///
        gotoxy(x - 25, y + 4);
        color(0, 0, 219); color(0, 0, 219); color(15, 0, 219); color(15, 0, 219);
        gotoxy(x - 25, y + 5);
        color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219);
        gotoxy(x - 25, y + 6);
        color(0, 0, 219); color(0, 0, 219); color(15, 0, 219); color(15, 0, 219);
        ///-----SECOND NUMBER -----///
        numberTwo = rand() % mod + mod;
        if (numberTwo % 10 == 0)
            numberTwo++;
        printBigNumber(numberTwo, x, y + 6, idColor);

        gotoxy(x - 25, y + 12);
        for (int i = 0; i < 35; i++)
            color(15, 0, 223);

        if (rand() % 2 == 1)
        {
            printBigNumber(numberOne + numberTwo, x, y + 14, idColor);
            result = 1;
        }
        else
        {
            temp = rand() % 6;
            if (temp == 0 && numberOne + numberTwo > 20)
                printBigNumber(numberOne + numberTwo + 10, x, y + 14, idColor);
            else if (temp == 1 && numberOne + numberTwo > 20)
                printBigNumber(numberOne + numberTwo - 10, x, y + 14, idColor);
            else if (temp == 2)
                printBigNumber(numberOne + numberTwo - 2, x, y + 14, idColor);
            else if (temp == 3)
                printBigNumber(numberOne + numberTwo + 2, x, y + 14, idColor);
            else if (temp == 4)
                printBigNumber(numberOne + numberTwo + 1, x, y + 14, idColor);
            else if (temp == 5 )
                printBigNumber(numberOne + numberTwo - 1, x, y + 14, idColor);
            else if (rand() % 2 == 0)
                printBigNumber(numberOne + numberTwo + 1, x, y + 14, idColor);
            else
                printBigNumber(numberOne + numberTwo - 1, x, y + 14, idColor);
            result = 0;
        }
        setColor(0 << 10 | 10 << 4 | 15);
        gotoxy(x - 30, 31);
        printf("        %c%c      ", 220, 220);
        gotoxy(x - 30, 32);
        printf("      %c%c        ", 219, 219);
        gotoxy(x - 30, 33);
        printf("    %c%c          ", 219, 219);
        gotoxy(x - 30, 34);
        printf("      %c%c        ", 219, 219);
        gotoxy(x - 30, 35);
        printf("        %c%c      ", 223, 223);

        setColor(0 << 10 | 4 << 4 | 15);
        gotoxy(x - 1, 31);
        printf("      %c%c        ", 220, 220);
        gotoxy(x - 1, 32);
        printf("        %c%c      ", 219, 219);
        gotoxy(x - 1, 33);
        printf("          %c%c    ", 219, 219);
        gotoxy(x - 1, 34);
        printf("        %c%c      ", 219, 219);
        gotoxy(x - 1, 35);
        printf("      %c%c        ", 223, 223);

        mod ++;
        gotoxy(6, 3); /// RESET
        for (int i = 0; i < WIDTH_LAYOUR; i++)
            color(0, 0, 219);

        gotoxy(6, 3);
        for (int i = 0; i < WIDTH_LAYOUR; i++)
        {
            color(15, 0, 219); /// TIME
            if(kbhit())
            {
                key = _getch();
                while(key == -32)
                    key = _getch();
                if (key == 75) /// TRUE
                {
                    if (result == 0)
                        flag = 1;
                    else
                        score++;
                    break;
                }
                if (key == 77) /// FALSE
                {
                    if (result == 0)
                        score++;
                    else
                        flag = 1;
                    break;
                }
            }
            Sleep(24);
        }
        if (key != 77 && key != 75)
            flag = 1;
    }
    if (score > highScore)
    {
        Fo = fopen("score.txt", "w");
        fprintf(Fo, "%d", score);
        highScore = score;
    }
    x = 15, y = 13;
    gotoxy(x - 1, y - 1);
    color(7, 7, 219);
    setColor(0 << 10 | 7 << 4 | 12);
    for (int i = 0; i < 40 + 2; i++)
        printf("%c", 220);
    color(7, 7, 219);

    for (int i = 0; i < 20; i++)
    {
        gotoxy(x - 1, y + i);
        color(7, 7, 219);
        color(12, 7, 219);
        for (int j = 0; j < 40; j++)
        {
            setColor(0 << 10 | 15 << 4 | 0);
            printf("%c", 219);
        }
        color(12, 7, 219);
        color(7, 7, 219);
    }

    gotoxy(x - 1, y + 19);
    color(7, 7, 219);
    setColor(0 << 10 | 7 << 4 | 12);
    for (int i = 0; i < 40 + 2; i++)
        printf("%c", 223);
    color(7, 7, 219);

    setColor(0 << 10 | 0 << 4 | 14);
    gotoxy(x + 14, y + 3);
    printf("HIGHEST SCORE");
    setColor(0 << 10 | 0 << 4 | 15);
    gotoxy(x + 20, y + 5);
    printf("%d", highScore);
    gotoxy(x + 16, y + 8);
    setColor(0 << 10 | 0 << 4 | 12);
    printf("YOUR SCORE");
    gotoxy(x + 20, y + 10);
    setColor(0 << 10 | 0 << 4 | 15);
    printf("%d", score);
    gotoxy(x + 9, y + 13);
    setColor(0 << 10 | 0 << 4 | 4);
    printf("PRESS ENTER TO CONTINUES");
    while(key != 13)
    {
        cleanPointer();
        key = _getch();
        if (key == 13)
        {
            Beep(400, 40);
            pointer = (pointer + 1) % 2;
        }
        if (key == 13)
        {
            if (pointer == 1)
            {
                gameLayour();
                return;
            }
        }
    }
    Sleep(10000);
    return;
}
void gameLayour()
{
    system("cls");
    setBackGround(0);
    returnButton(0);
    char key;
    int x = 14, y = 12;
    int pointer = 0, flag = 1;

    gotoxy(x + 35, y - 5);
    color(15, 0, 220); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 220);
    gotoxy(x + 35, y - 4);
    color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219);
    gotoxy(x + 35, y - 3);
    color(15, 0, 223); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 219); color(15, 0, 223);
    gotoxy(x + 35 + 5, y - 2);
    color(15, 0, 219); color(15, 0, 219); color(15, 0, 223);
    gotoxy(x + 35 + 4, y - 1);
    color(15, 0, 223); color(15, 0, 223);
    gotoxy(x + 38, y - 4);
    setColor(0 << 10 | 15 << 4 | 0);
    printf("1 + 1 = 2");

    ///----------------------MATH------------------------///
    gotoxy(x, y);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 220); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 220); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219);
    /*A*/               color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219); color(0, 0, 219);
    /*T*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219);
    /*H*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220);

    gotoxy(x, y + 1);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*A*/               color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220); color(0, 0, 219);
    /*T*/               color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219);
    /*H*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219);

    gotoxy(x, y + 2);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*A*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 220);
    /*T*/               color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
    /*H*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219);

    gotoxy(x, y + 3);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(9, 0, 223); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*A*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219);
    /*T*/               color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
    /*H*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219);

    gotoxy(x, y + 4);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*A*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*T*/               color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
    /*H*/               color(11, 0, 219); color(11, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(9, 0, 219);

    gotoxy(x, y + 5);
    /*M*/               color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223);
    /*A*/               color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219);
    /*T*/               color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219);
    /*H*/              color(0, 0, 219); color(9, 0, 223); color(9, 0, 223); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 223);

    ///--------------------GAME--------------------///
    gotoxy(x + 6, y + 7);
    /*G*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(0, 0, 219);
    /*A*/               color(11, 0, 220); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 220); color(0, 0, 219);
    /*M*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(0, 0, 219); color(0, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(0, 0, 219);
    /*E*/               color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219); color(11, 0, 219);
    gotoxy(x + 6, y + 8);
    /*G*/               color(3, 0, 219); color(3, 0, 219); color(0, 0, 219); color(0, 0, 219); color(3, 0, 220); color(3, 0, 220); color(3, 0, 220); color(0, 0, 219);
    /*A*/               color(3, 0, 219); color(3, 0, 219); color(3, 0, 220); color(3, 0, 220); color(3, 0, 220); color(3, 0, 219); color(3, 0, 219); color(0, 0, 219);
    /*M*/               color(3, 0, 219); color(3, 0, 219); color(0, 0, 219); color(3, 0, 219); color(3, 0, 219); color(0, 0, 219); color(3, 0, 219); color(3, 0, 219); color(0, 0, 219);
    /*E*/               color(3, 0, 219); color(3, 0, 219); color(3, 0, 220); color(3, 0, 220); color(3, 0, 220); color(3, 0, 220); color(3, 0, 220);
    gotoxy(x + 6, y + 9);
    /*G*/               color(9, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 223); color(9, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*A*/               color(9, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*M*/               color(9, 0, 219); color(9, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(9, 0, 219); color(9, 0, 219); color(0, 0, 219);
    /*E*/               color(9, 0, 219); color(9, 0, 219); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223); color(9, 0, 223);
    gotoxy(x + 6, y + 10);
    /*G*/               color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(0, 0, 219);
    /*A*/               color(1, 0, 219); color(1, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(1, 0, 219); color(1, 0, 219); color(0, 0, 219);
    /*M*/               color(1, 0, 219); color(1, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(0, 0, 219); color(1, 0, 219); color(1, 0, 219); color(0, 0, 219);
    /*E*/               color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219); color(1, 0, 219);

    while(flag)
    {
        gotoxy(x + 7, y + 15);
        setColor(0 << 10 | 11 << 4 | 0);
        printf("  PRESS ENTER BUTTON TO PLAY   ");
        cleanPointer();
        key = _getch();
        if (key == 13) /// ENTER
        {
            Beep(500, 50);
            Beep(500, 50);
            switch (pointer)
            {
                case 0:
                    playGameLayour();
                    break;
            }
        }
    }
    cleanPointer();
    return;
}
