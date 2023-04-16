#include <string>
#include <vector>
#include <fileapi.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "config.h"
#include "colorprint.h"

using namespace std;

vector<string> getMapList()
{
  vector<string> mapList;
  string mapDir = "maps";
  string mapName;
  string mapPath;
  WIN32_FIND_DATAA findData;
  HANDLE hFind = FindFirstFileA((mapDir + "\\*").c_str(), &findData);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    do
    {
      mapName = findData.cFileName;
      if (mapName != "." && mapName != "..")
      {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
          mapPath = mapDir + "\\" + mapName;
          mapList.push_back(mapPath);
        }
      }
    } while (FindNextFileA(hFind, &findData));
    FindClose(hFind);
  }
  return mapList;
}

vector<string> getPlayLists(string playListDir){
  vector<string> playLists;
  string playListName;
  string playListPath;
  WIN32_FIND_DATAA findData;
  HANDLE hFind = FindFirstFileA((playListDir + "\\*").c_str(), &findData);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    do
    {
      playListName = findData.cFileName;
      if (playListName != "." && playListName != "..")
      {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
          playListPath = playListDir + "\\" + playListName;
          playLists.push_back(playListPath);
        }
      }
    } while (FindNextFileA(hFind, &findData));
    FindClose(hFind);
  }
  return playLists;
}

vector<string> readMap(string mapPath)
{
  vector<string> map;
  string line;
  ifstream mapFile;
  mapFile.open(mapPath.c_str());
  if (mapFile.is_open())
  {
    while (getline(mapFile, line))
    {
      map.push_back(line);
    }
    mapFile.close();
  }
  return map;
}

vector<string> readPlayList(string playListPath){
  // cout<<playListPath<<endl;
  vector<string> playList;
  string line;
  ifstream playListFile;
  playListFile.open(playListPath.c_str());
  if (playListFile.is_open())
  {
    while (getline(playListFile, line))
    {
      playList.push_back(line);
    }
    playListFile.close();
  }
  return playList;
}

string getMapName(string mapPath)
{
  int pos = mapPath.find_last_of('\\');
  int pos2 = mapPath.find_last_of('.');
  return mapPath.substr(pos + 1, pos2 - pos - 1);
}

void renderMap(vector<string> map)
{
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].length(); j++)
    {
      switch (map[i][j])
      {
      case m_player:
        COLOR_PRINT(s_player, c_player);
        break;
      case m_wall:
        COLOR_PRINT(s_wall, c_wall);
        break;
      case m_box:
        COLOR_PRINT(s_box, c_box);
        break;
      case m_target:
        COLOR_PRINT(s_target, c_target);
        break;
      case m_space:
        COLOR_PRINT(s_space, c_space);
        break;
      }
    }
    cout << endl;
  }
}