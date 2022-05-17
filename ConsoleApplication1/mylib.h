#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include<iostream>
#define Enter 13
#define PASSWORD "abcdef"
#include <iomanip>

void HideCursor(bool isHide)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = !isHide;
    SetConsoleCursorInfo(consoleHandle, &info);
}
char* Pwd() {
    char S[40]; int i = 0;
    while ((S[i] = _getch()) != Enter)
    {
        printf("%c", '*'); i++;
    }
    S[i] = '\0';
    return S;
}

int CheckPwd() {
    int dem = 0;
    for (dem = 1; dem <= 3; dem++)
    {
        printf("Password :");
        if (strcmp(Pwd(), PASSWORD) == 0)   return 1;
        else printf("\nPassword sai. Hay nhap lai\n");
    }
    return 0;
}
// dua con tro chuot den vi tri x y
void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
// vi tri X cua con tro chuot
int wherex(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}
// vi tri Y cua con tro chuot
int wherey(void)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
//xoa vi tri con tro
void clreol() {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
    gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}
//set mau cho chu
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// set mau cho nen
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//xoa man hinh
void clrscr() {
    system("cls");
}
////
//void TextColor (int color){	
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
//	}
void rectagle(int x, int y, int width, int height) {
    gotoxy(x, y);
    std::cout << std::setfill((char)196);
    std::cout << char(218) << std::setw(width - 1) << char(191);
    std::cout << std::setfill(' ');
    for (int i = 1; i < height; i++)
    {
        gotoxy(x, y + i);
        std::cout << char(179) << std::setw(width - 1) << char(179);
    }
    gotoxy(x, y + height);
    std::cout << std::setfill((char)196);
    std::cout << char(192) << std::setw(width - 1) << char(217);
}
void SizeConsole(SHORT Width, SHORT height)
{
    HANDLE stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT SizeW = { 0,0,Width - 1,height - 1 };
    COORD sizebuff = { Width,height };
    BOOL BSize = SetConsoleWindowInfo(stdhandle, true, &SizeW);
    SetConsoleScreenBufferSize(stdhandle, sizebuff);
    if (!BSize) SetConsoleWindowInfo(stdhandle, true, &SizeW);
}

void SetSizeWindows(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}
int inputKey()
{
    int key = _getch();
    if (key == 224 || key == 0)	// special key
    {
        key = _getch();
        return key;
    }
    return key;
}
int GetKey() {
    char key;
    key = _getch();
    if (key == -32 || key == 0)
        return -_getch();
    else return key;
}
void RemoveScrollbar()
{
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

