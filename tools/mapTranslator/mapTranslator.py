import configparser
import os
mapName = "DEFAULT.MAP"
mapSaveFolder = mapName.split('.')[0] + '/'
maps = []

cp = configparser.ConfigParser()
cp.read(mapName)

mapNum = int(cp['Maps']['MapNumber'])

for i in range(1, mapNum + 1):
    mapName = 'Map' + str(i)
    width = int(cp[mapName]['MapWidth'])
    height = int(cp[mapName]['MapHeight'])
    mapLines = []
    for j in range(1, height + 1):
        lineKey = 'MapLine' + str(j)
        mapLines.append(cp[mapName][lineKey])
    maps.append({
        "mapName": mapName,
        "width": width,
        "height": height,
        "map": mapLines
    })
replaceMap = {
    "0": " ",
    "1": " ",
    "2": "W",
    "3": "B",
    "4": "T",
    "5": "P"
}

if not os.path.exists(mapSaveFolder):
    os.makedirs(mapSaveFolder)

for map in maps:
    mapName = mapSaveFolder + map['mapName'] + ".map"
    with open(mapName, 'w') as f:
        for line in map['map']:
            for char in line:
                f.write(replaceMap[char])
            f.write('\n')
