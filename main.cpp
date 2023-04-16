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
void startGame(vector<string> map, string mapName, bool inList);
void selectPlayList();
void playInList(vector<string> playList, string currentMap, string playListName);
void continuePlayList();

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
  if (!hasSaveData())
    selected = 1;
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
    string options[] = {"Continue", "Start Game", "Random Map", "Select Map", "Exit"};
    int num_options = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < num_options; i++)
    {
      if (i == 0)
      {
        if (!hasSaveData())
        {
          COLOR_PRINT("Continue", 8);
          cout << endl;
          continue;
        }
      }
      if (selected == i)
      {
        COLOR_PRINT(options[i].c_str(), 0, 15);
      }
      else
      {
        COLOR_PRINT(options[i].c_str(), 15);
      }
      cout << endl;
    }

    switch (getch())
    {
    case 72:
      selected--;
      if (selected < 0)
        selected = num_options - 1;
      if (selected == 0 && !hasSaveData())
        selected = num_options - 1;
      break;
    case 80:
      selected++;
      if (selected > num_options - 1)
        selected = 0;
      if (selected == 0 && !hasSaveData())
        selected = 1;
      break;
    case 13:
      switch (selected)
      {
      case 0:
        continuePlayList();
      case 1:
        selectPlayList();
        break;
      case 2:
        randomMap();
        break;
      case 3:
        selectMap();
        break;
      case 4:
        exit(0);
        break;
      }
      break;
    }
  }
}

void startGame(vector<string> map, string mapName, bool inList)
{
  vector<string> sourceMap = map;
  system("cls");
  bool win = false;
  while (true)
  {
    setCursorPos(0, 0);
    cout << "Map: " << mapName << endl
         << endl;
    renderMap(map);
    if (isWin(map, sourceMap))
    {
      win = true;
      COLOR_PRINT("You Win!\n", 10);
      if (!inList)
      {
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
      else
      {
        COLOR_PRINT("Press <ENTER> to next map\n", 8);
        while (true)
        {
          char ch = getch();
          if (ch == 13)
          {
            break;
          }
        }
      }
    }
    if(win) break;
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
          map = sourceMap;
          system("cls");
          break;
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
  startGame(map, getMapName(mapPath), false);
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
        startGame(map, mapNameList[selectedMap], false);
      }
    }
  }
}

void selectPlayList()
{
  string playListDir = "playlists";
  vector<string> playLists = getPlayLists(playListDir);
  int playListCount = playLists.size();
  int selectedPlayList = 0;
  system("cls");
  while (true)
  {
    setCursorPos(0, 0);
    COLOR_PRINT("Use <UP> <DOWN> <ENTER> to select a playlist\n\n", 8);
    for (int i = 0; i < playListCount; i++)
    {
      string playListDisplayName = playLists[i].substr(playListDir.length() + 1);
      playListDisplayName = playListDisplayName.substr(0, playListDisplayName.length() - 4);
      if (selectedPlayList == i)
        COLOR_PRINT(playListDisplayName.c_str(), 0, 15);
      else
        COLOR_PRINT(playListDisplayName.c_str(), 15);
      cout << endl;
    }
    cout << endl;
    if (selectedPlayList == playListCount)
      COLOR_PRINT("BACK", 0, 15);
    else
      COLOR_PRINT("BACK", 15);
    cout << endl;

    switch (getch())
    {
    case 72:
      selectedPlayList--;
      if (selectedPlayList < 0)
        selectedPlayList = playListCount;
      break;
    case 80:
      selectedPlayList++;
      if (selectedPlayList > playListCount)
        selectedPlayList = 0;
      break;
    case 13:
      if (selectedPlayList == playListCount)
        mainMenu();
      else
      {
        vector<string> playList = readPlayList(playLists[selectedPlayList]);
        if (hasSaveData())
        {
          COLOR_PRINT("You have save data, press <ENTER> to overwrite, <ESC> to cancel\n", 8);
          while (true)
          {
            char ch = getch();
            if (ch == 13)
            {
              break;
            }
            else if (ch == 27)
            {
              mainMenu();
            }
          }
        }
        playInList(playList, playList[0], playLists[selectedPlayList]);
      }
    }
  }
}

void playInList(vector<string> playList, string currentMap, string playListName)
{
  for (int i = 0; i < playList.size(); i++)
  {
    if (playList[i] == currentMap)
    {
      for (int j = i; j < playList.size(); j++)
      {
        vector<string> map = readMap("maps/" + playList[j]);
        saveData(playListName, playList[j]);
        startGame(map, getMapName(playList[j]), true);
      }
    }
  }
  showCongratulations();
  
  COLOR_PRINT("\nCongratulations!\nYou have finished the playlist\n", 8);
  COLOR_PRINT("Press <ENTER> to return to main menu\n", 8);
  while (true)
  {
    char ch = getch();
    if (ch == 13)
    {
      deleteSaveData();
      mainMenu();
    }
  }
}

void continuePlayList(){
  vector<string> saveData = loadSaveData();
  string playListName = saveData[0];
  string currentMap = saveData[1];
  playInList(readPlayList(playListName), currentMap, playListName);
}

int main()
{
  init();
  while (true)
    mainMenu();
  return 0;
}