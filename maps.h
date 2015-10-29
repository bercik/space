#ifndef MAPS_H
#define MAPS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "consts.h"

typedef struct
{
    char maps[MAX_MAPS][32];
    int a_map;
    int number_of_maps;
}Maps;

// CreateMaps: tworzy obiekt Maps
Maps CreateMaps();
// LoadMapsPaths: ładuje ścieżki do map z podanego pliku (w przypadku niepowodzenia zwraca false)
bool LoadMapsPaths(Maps* const maps, const char* const path);
// GetCurrentMapPath: zwraca ścieżkę do aktualnej mapy
inline const char* GetCurrentMapPath(const Maps* const maps);
// IncreaseActualMap: zwiększa aktualną mapę o 1, zwraca false jeżeli nie ma już kolejnych map
inline bool IncreaseActualMap(Maps* const maps);

#endif
