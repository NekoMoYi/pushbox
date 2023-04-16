#include <vector>
#include <string>

using namespace std;

vector<string> movePlayer(vector<string> map, vector<string> sourceMap, int xstep, int ystep)
{
  int x = 0;
  int y = 0;
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].length(); j++)
    {
      if (map[i][j] == m_player)
      {
        x = j;
        y = i;
        break;
      }
    }
  }
  if (map[y + ystep][x + xstep] == m_wall)
  {
    return map;
  }
  if (map[y + ystep][x + xstep] == m_box)
  {
    if (map[y + ystep * 2][x + xstep * 2] == m_wall)
    {
      return map;
    }
    if (map[y + ystep * 2][x + xstep * 2] == m_box)
    {
      return map;
    }
    map[y + ystep * 2][x + xstep * 2] = m_box;
  }
  map[y][x] = m_space;
  if (sourceMap[y][x] == m_target)
    map[y][x] = m_target;
  map[y + ystep][x + xstep] = m_player;
  return map;
}

bool isWin(vector<string> map, vector<string> sourceMap)
{
  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].length(); j++)
    {
      if (map[i][j] == m_target)
      {
        return false;
      }
    }
  }

  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map[i].length(); j++)
    {
      if (map[i][j] == m_player)
      {
        if (sourceMap[i][j] == m_target)
        {
          return false;
        }
      }
    }
  }
  return true;
}

bool hasSaveData()
{
  ifstream file("save.dat");
  if (file.is_open())
  {
    // 第一行为playlist名
    string playList, mapName;
    getline(file, playList);
    getline(file, mapName);
    if (playList != "" && mapName != "")
    {
      file.close();
      return true;
    }
  }
  return false;
}

bool saveData(string playList, string mapName)
{
  ofstream file("save.dat");
  if (file.is_open())
  {
    file << playList << endl;
    file << mapName << endl;
    file.close();
    return true;
  }
  return false;
}

bool deleteSaveData()
{
  ofstream file("save.dat");
  if (file.is_open())
  {
    file << "" << endl;
    file << "" << endl;
    file.close();
    return true;
  }
  return false;
}

vector<string> loadSaveData()
{
  vector<string> saveData;
  ifstream file("save.dat");
  if (file.is_open())
  {
    string playList, mapName;
    getline(file, playList);
    getline(file, mapName);
    saveData.push_back(playList);
    saveData.push_back(mapName);
    file.close();
  }
  return saveData;
}

void showCongratulations()
{
  system("cls");
  COLOR_PRINT("____    ____  ______    __    __     ____    __    ____  __  .__   __. \n", 10);
  COLOR_PRINT("\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  | \n", 10);
  COLOR_PRINT(" \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  | \n", 10);
  COLOR_PRINT("  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  | \n", 10);
  COLOR_PRINT("    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   | \n", 10);
  COLOR_PRINT("    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__| \n", 10);
}