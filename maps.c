#include "maps.h"

Maps CreateMaps()
{
    Maps maps;

    maps.a_map = 0;
    maps.number_of_maps = 0;

    return maps;
}

// LoadMapsPath: ładuje ścieżki do map z podanego pliku (w przypadku niepowodzenia zwraca false)
bool LoadMapsPaths(Maps* const maps, const char* const path)
{
    FILE* file = fopen(path, "r");

    if (!file)
        return false;

    // zmienne pomocnicze:
    int i, number_of_maps;
    char temp[32];

    fscanf(file, "%d", &number_of_maps);
    if (number_of_maps > MAX_MAPS)
        return false;

    maps->number_of_maps = number_of_maps;

    for (i = 0; i < number_of_maps; ++i)
    {
        fscanf(file, "%s", temp);

        strcpy(maps->maps[i], temp);
    }

    return true;
}

inline const char* GetCurrentMapPath(const Maps* const maps)
{
    return maps->maps[maps->a_map];
}

inline bool IncreaseActualMap(Maps* const maps)
{
    ++maps->a_map;

    return (maps->a_map < maps->number_of_maps);
}
