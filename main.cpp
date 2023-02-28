#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <list>
#include <time.h>
#include "maps.h"
#include "syscon.h"
#include "gamectrl.h"

using namespace std;

void init();
void mainMenu();
void selectMap();
void randomMap();
void startGame(vector<string> map, string mapName);

void init()
{
  system("chcp 65001");
  system("cls");
  system("title PUSHBOX!");
  system("color 0f");
}

void mainMenu()
{
  system("cls");
  hideCursor();
  int selected = 0;
  while (true)
  {
    setCursorPos(0, 0);

    cout << "" << endl
         << "" << endl;

    cout << " .______    __    __       _______. __    __  .______     ______   ___   ___ " << endl;
    cout << " |   _  \\  |  |  |  |     /       ||  |  |  | |   _  \\   /  __  \\  \\  \\ /  / " << endl;
    cout << " |  |_)  | |  |  |  |    |   (----`|  |__|  | |  |_)  | |  |  |  |  \\  V  /  " << endl;
    cout << " |   ___/  |  |  |  |     \\   \\    |   __   | |   _  <  |  |  |  |   >   <   " << endl;
    cout << " |  |      |  `--'  | .----)   |   |  |  |  | |  |_)  | |  `--'  |  /  .  \\  " << endl;
    cout << " | _|       \\______/  |_______/    |__|  |__| |______/   \\______/  /__/ \\__\\" << endl;
    cout << endl
         << "@nekomoyi" << endl
         << endl;

    COLOR_PRINT("Use <UP> <DOWN> <ENTER> to select\n\n", 8);

    if (selected == 0)
    {
      COLOR_PRINT("Random Map", 0, 15);
      cout << endl;
    }
    else
    {
      COLOR_PRINT("Random Map", 15);
      cout << endl;
    }
    if (selected == 1)
    {
      COLOR_PRINT("Select Map", 0, 15);
      cout << endl;
    }
    else
    {
      COLOR_PRINT("Select Map", 15);
      cout << endl;
    }
    if (selected == 2)
    {
      COLOR_PRINT("Exit", 0, 15);
      cout << endl;
    }
    else
    {
      COLOR_PRINT("Exit", 15);
      cout << endl;
    }

    switch (getch())
    {
    case 72:
      selected--;
      if (selected < 0)
        selected = 2;
      break;
    case 80:
      selected++;
      if (selected > 2)
        selected = 0;
      break;
    case 13:
      switch (selected)
      {
      case 0:
        randomMap();
        break;
      case 1:
        selectMap();
        break;
      case 2:
        exit(0);
        break;
      }
      break;
    }
  }
}

void startGame(vector<string> map, string mapName)
{
  vector<string> sourceMap = map;
  system("cls");
  while (true)
  {
    setCursorPos(0, 0);
    cout << "Map: " << mapName << endl
         << endl;
    renderMap(map);
    if (isWin(map, sourceMap))
    {
      COLOR_PRINT("You Win!\n", 10);
      COLOR_PRINT("Press <ENTER> to menu\n", 8);
      while (true)
      {
        char ch = getch();
        if (ch == 13)
        {
          mainMenu();
        }
      }
    }
    switch (getch())
    {
    case 27:
      COLOR_PRINT("Press <ENTER> to menu, <ESC> to cancel\n", 8);
      while (true)
      {
        char ch = getch();
        if (ch == 13)
        {
          mainMenu();
        }
        else if (ch == 27)
        {
          system("cls");
          break;
        }
      }
      break;
    case 72:
      map = movePlayer(map, sourceMap, 0, -1);
      break;
    case 80:
      map = movePlayer(map, sourceMap, 0, 1);
      break;
    case 75:
      map = movePlayer(map, sourceMap, -1, 0);
      break;
    case 77:
      map = movePlayer(map, sourceMap, 1, 0);
      break;
    case 114:
      COLOR_PRINT("Press <ENTER> to restart, <ESC> to cancel\n", 8);
      while (true)
      {
        char ch = getch();
        if (ch == 13)
        {
          startGame(sourceMap, mapName);
        }
        else if (ch == 27)
        {
          system("cls");
          break;
        }
      }
      break;
    }
  }
}

void randomMap()
{
  vector<string> mapList = getMapList();
  srand(time(NULL));
  int mapIndex = rand() % mapList.size();
  string mapPath = mapList[mapIndex];
  vector<string> map = readMap(mapPath);
  startGame(map, getMapName(mapPath));
}

void selectMap()
{
  vector<string> mapList = getMapList();
  vector<string> mapNameList;
  int mapCount = mapList.size();
  int selectedMap = 0;
  for (int i = 0; i < mapCount; i++)
    mapNameList.push_back(getMapName(mapList[i]));
  system("cls");
  while (true)
  {
    setCursorPos(0, 0);
    COLOR_PRINT("Use <UP> <DOWN> <ENTER> to select a map\n\n", 8);
    for (int i = 0; i < mapCount; i++)
    {
      if (selectedMap == i)
        COLOR_PRINT(mapNameList[i].c_str(), 0, 15);
      else
        COLOR_PRINT(mapNameList[i].c_str(), 15);
      cout << endl;
    }
    cout << endl;
    if (selectedMap == mapCount)
      COLOR_PRINT("BACK", 0, 15);
    else
      COLOR_PRINT("BACK", 15);
    cout << endl;

    switch (getch())
    {
    case 72:
      selectedMap--;
      if (selectedMap < 0)
        selectedMap = mapCount;
      break;
    case 80:
      selectedMap++;
      if (selectedMap > mapCount)
        selectedMap = 0;
      break;
    case 13:
      if (selectedMap == mapCount)
        mainMenu();
      else
      {
        vector<string> map = readMap(mapList[selectedMap]);
        startGame(map, mapNameList[selectedMap]);
      }
    }
  }
}

int main()
{
  init();
  while (true)
    mainMenu();
  return 0;
}