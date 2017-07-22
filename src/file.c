#include "../include/file.h"

void FILE_exportLevelToFile(Map_STRUCT *map, char* fileName)
{
    int fileNameSize = strlen(fileName)+1;
    char extention[5] = ".map";
    char _fileName[fileNameSize+4];
    int i=0;
    for(;i<fileNameSize-1; i++)
        _fileName[i] = fileName[i];
    for(int j=0;j<5;j++)
        _fileName[i+j] = extention[j];
        
    map->posX = 100;
    map->posY = 60;
    
    FILE* file;
    if((file = (FILE*)fopen(_fileName, "rb+")) == NULL)
    {
        if((file = (FILE*)fopen(_fileName, "wb+")) == NULL)
        {
            printf("ERROR: Can't create file\n");
            return;
        }
    }
    fwrite(&map->posX, sizeof(int), 1, file);
    fwrite(&map->posY, sizeof(int), 1, file);
    for(int x=0; x<map->mapSizeX; x++)
    {
        
        for(int y=0; y<map->mapSizeY; y++)
        {
            fwrite(&map->mapElements[x][y].elementScreen.itemType, sizeof(ItemType), 1, file);
        }
    }

    fclose(file);
}

Map_STRUCT FILE_importLevelFromFile(char* fileName, System* system_data, Player *player, Level *level)
{
    Map_STRUCT map;
    FILE* file;
    if((file = (FILE*)fopen(fileName, "rb+")) == NULL)
    {
        if((file = (FILE*)fopen(fileName, "wb+")) == NULL)
        {
            printf("ERROR: Can't create file\n");
            return map;
        }
    }
    
    fread(&map.posX, sizeof(int), 1, file);
    fread(&map.posY, sizeof(int), 1, file);
    map.mapElements = LEVEL_generateMap(&map.mapSizeX, &map.mapSizeY, system_data->renderer, system_data->mapElementsScreens, system_data->MapElementScreenCount, map.posX, map.posY);
    for(int x=0; x<map.mapSizeX; x++)
    {
        
        for(int y=0; y<map.mapSizeY; y++)
        {
            ItemType itemType;
            fread(&itemType, sizeof(ItemType), 1, file);
            
            switch (itemType) {
                case IT_WALL:
                {
                    Wall *tmp = (Wall*)malloc(sizeof(Wall));
                    tmp->rect = map.mapElements[x][y].rect;
                    tmp->next = (struct Wall*)level->walls;
                    level->walls = (Wall*)tmp;
                    break; 
                }
                case IT_ENEMY:
                {
                    SDL_Surface surface = (*LEVEL_findSurfaceByItemType(itemType, system_data->mapElementsScreens, system_data->MapElementScreenCount));
                    Enemy enemy = {surface ,SDL_CreateTextureFromSurface(system_data->renderer, &surface) ,map.mapElements[x][y].rect, 1, true, LEFT};
                    Enemy_STRUCT *tmp = (Enemy_STRUCT*)malloc(sizeof(Enemy_STRUCT));
                    tmp->enemy = enemy;
                    tmp->next = (struct Enemy_STRUCT*)level->enemies;
                    level->enemies = (Enemy_STRUCT*)tmp;
                    itemType = IT_EMPTY;
                    break;
                }
                case IT_COIN:
                {
                    SDL_Surface surface = (*LEVEL_findSurfaceByItemType(itemType, system_data->mapElementsScreens, system_data->MapElementScreenCount));
                    Coin coin = {surface ,SDL_CreateTextureFromSurface(system_data->renderer, &surface) ,map.mapElements[x][y].rect};
                    Coin_STRUCT *tmp = (Coin_STRUCT*)malloc(sizeof(Coin_STRUCT));
                    tmp->coin = coin;
                    tmp->next = (struct Coin_STRUCT*)level->coins;
                    level->coins = (Coin_STRUCT*)tmp;
                    itemType = IT_EMPTY;
                    break;
                }
                case IT_KEY:
                {
                    SDL_Surface surface = (*LEVEL_findSurfaceByItemType(itemType, system_data->mapElementsScreens, system_data->MapElementScreenCount));
                    Key key = {surface ,SDL_CreateTextureFromSurface(system_data->renderer, &surface) ,map.mapElements[x][y].rect};
                    Key_STRUCT *tmp = (Key_STRUCT*)malloc(sizeof(Key_STRUCT));
                    tmp->key = key;
                    tmp->next = (struct Key_STRUCT*)level->keys;
                    level->keys = (Key_STRUCT*)tmp;
                    itemType = IT_EMPTY;
                    break;
                }
                case IT_DOOR:
                {
                    SDL_Surface closedSurface = (*LEVEL_findSurfaceByItemType(itemType, system_data->mapElementsScreens, system_data->MapElementScreenCount));
                    SDL_Surface openSurface = (*LEVEL_findSurfaceByItemType(IT_O_DOOR, system_data->mapElementsScreens, system_data->MapElementScreenCount));
                    Door door = {closedSurface, SDL_CreateTextureFromSurface(system_data->renderer, &openSurface), SDL_CreateTextureFromSurface(system_data->renderer, &closedSurface), map.mapElements[x][y].rect,true};
                    Door_STRUCT *tmp = (Door_STRUCT*)malloc(sizeof(Door_STRUCT));
                    tmp->door = door;
                    tmp->next = (struct Door_STRUCT*)level->doors;
                    level->doors = (Door_STRUCT*)tmp;
                    itemType = IT_EMPTY;
                    break;
                }
                case IT_PPOS:
                {
                    player->rect = map.mapElements[x][y].rect;
                    itemType = IT_EMPTY;
                    break;
                }
                case IT_PFIN:
                {
                    level->endRect = map.mapElements[x][y].rect;
                    break;
                }
            }
            
            map.mapElements[x][y] = LEVEL_generateMapElement(map.mapElements[x][y].rect, system_data->renderer, itemType, false, system_data->mapElementsScreens, system_data->MapElementScreenCount);
            
        }
    }
    fclose(file);
    return map;
}

void FILE_updateScoreList(char playerName[21], int score)
{
    FILE* file;
    if((file = (FILE*)fopen("scores.txt", "a+")) == NULL)
    {
        printf("ERROR: Can't create file\n");
        return;
    }
    fprintf(file, "%s .............................. %d\n", playerName, score );
    
    fclose(file);
}