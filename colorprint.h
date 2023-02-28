#include <windows.h>

/*
0 = 黑色    8   = 灰色
1 = 蓝色    9   = 淡蓝色
2 = 绿色    10  = 淡绿色
3 = 浅绿色  11  = 淡浅绿色
4 = 红色    12  = 淡红色
5 = 紫色    13  = 淡紫色
6 = 黄色    14  = 淡黄色
7 = 白色    15  = 亮白色
*/

void COLOR_PRINT(const char *s, int color)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
  printf("%s", s);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

void COLOR_PRINT(const char *s, int color, int bgcolor)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color | (bgcolor << 4));
  printf("%s", s);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

void COLOR_PRINT(char s, int color)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
  printf("%c", s);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

void COLOR_PRINT(char s, int color, int bgcolor)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color | (bgcolor << 4));
  printf("%c", s);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}