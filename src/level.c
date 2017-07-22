#include "../include/level.h"


void LEVEL_deleteButton(Button *button)
{
    SDL_DestroyTexture(button->texture);
    SDL_FreeSurface(button->surface);
}

void LEVEL_deleteMapElement(MapElement *element)
{
    SDL_DestroyTexture(element->texture);
}

void LEVEL_deleteMap(Map_STRUCT *map)
{
    for(int x=0; x<map->mapSizeX; x++)
    {
        for(int y=0; y<map->mapSizeY; y++)
        {
            LEVEL_deleteMapElement(&map->mapElements[x][y]);
        }
        free(map->mapElements[x]);
    }
    free(map->mapElements);
}

void LEVEL_deleteDoors(Door_STRUCT *door)
{
    while(door)
    {
        Door_STRUCT* p = (Door_STRUCT*)door->next;
        SDL_DestroyTexture(door->door.openTexture);
        SDL_DestroyTexture(door->door.closedTexture);
        free(door);
        door = (Door_STRUCT*)p;
    }
}

void LEVEL_deleteCoins(Coin_STRUCT *coin )
{
    while(coin)
    {
        Coin_STRUCT* p = (Coin_STRUCT*)coin->next;
        SDL_DestroyTexture(coin->coin.texture);
        free(coin);
        coin = (Coin_STRUCT*)p;
    }
}

void LEVEL_deleteKeys(Key_STRUCT *key)
{
    while(key)
    {
        Key_STRUCT* p = (Key_STRUCT*)key->next;
        SDL_DestroyTexture(key->key.texture);
        free(key);
        key = (Key_STRUCT*)p;
    }
}

void LEVEL_deleteEnemies(Enemy_STRUCT *enemy)
{
    while(enemy)
    {
        Enemy_STRUCT* p = (Enemy_STRUCT*)enemy->next;
        SDL_DestroyTexture(enemy->enemy.texture);
        free(enemy);
        enemy = (Enemy_STRUCT*)p;
    }
}

void LEVEL_deleteWalls(Wall *wall)
{
    while(wall)
    {
        Wall* p = (Wall*)wall->next;
        free(wall);
        wall = (Wall*)p;
    }
}

void LEVEL_deleteLevel(Level *level)
{
    LEVEL_deleteWalls(level->walls);
    LEVEL_deleteEnemies(level->enemies);
    LEVEL_deleteKeys(level->keys);
    LEVEL_deleteCoins(level->coins);
    LEVEL_deleteDoors(level->doors);
    LEVEL_deleteMap(&level->map);
    level->walls = NULL;
    level->coins = NULL;
    level->enemies = NULL;
    level->doors = NULL;
    level->keys = NULL;
}

void LEVEL_deleteLegend(Legend_STRUCT *legend)
{
    for(int i=0; i<legend->legendsCount; i++)
    {
        SDL_DestroyTexture(legend->legends[i].text.texture);
        SDL_FreeSurface(legend->legends[i].text.surface);
        SDL_DestroyTexture(legend->legends[i].element.texture);
    }
    free(legend->legends);
}

void LEVEL_deleteMapElementScreens(MapElementScreen *mapElementsScreens, int elementScreensCount)
{
    for(int i=0; i<elementScreensCount; i++)
        SDL_FreeSurface(mapElementsScreens[i].surface);
    free(mapElementsScreens);
    mapElementsScreens = NULL;
}

MapElementScreen LEVEL_createMapElementsScreen(ItemType itemtype, System *system_data)
{
    MapElementScreen element;
    SDL_Surface *surface;
    switch (itemtype)
    {
        case IT_EMPTY:
            surface = IMG_Load("../res/ground.png");
        break;
        case IT_KEY:
            surface = IMG_Load("../res/key.png");
            break;
        case IT_COIN:
            surface = IMG_Load("../res/coin.gif");
            break;
        case IT_DOOR:
            surface = IMG_Load("../res/c_door.png");
            break;
        case IT_O_DOOR:
            surface = IMG_Load("../res/o_door.png");
            break;
        case IT_WALL:
            surface = IMG_Load("../res/wall.png");
            break;
        case IT_ENEMY:
            surface = IMG_Load("../res/spd1_fr1.png");
            break;
        case IT_PPOS:
            surface = IMG_Load("../res/player_pos.png");
            break;
        case IT_PFIN:
            surface = IMG_Load("../res/player_dest.png");
            break;
            //highlighted
        case IT_H_EMPTY:
            surface = IMG_Load("../res/highlighted/h_ground.png");
            break;
        case IT_H_KEY:
            surface = IMG_Load("../res/highlighted/h_key.png");
            break;
        case IT_H_COIN:
            surface = IMG_Load("../res/highlighted/h_coin.gif");
            break;
        case IT_H_DOOR:
            surface = IMG_Load("../res/highlighted/h_c_door.png");
            break;
        case IT_H_WALL:
            surface = IMG_Load("../res/highlighted/h_wall.png");
            break;
        case IT_H_ENEMY:
            surface = IMG_Load("../res/highlighted/h_spd1_fr1.png");
            break;
        case IT_H_PPOS:
            surface = IMG_Load("../res/highlighted/h_player_pos.png");
            break;
        case IT_H_PFIN:
            surface = IMG_Load("../res/highlighted/h_player_dest.png");
            break;
    }
    if(surface == NULL)
    {
        printf( "Unable to load image SDL_image Error: %s\n", IMG_GetError());
        system_data->gameState = END;
    }

    element.surface = surface;
    element.itemType = itemtype;
    return element;
}

SDL_Surface* LEVEL_findSurfaceByItemType(ItemType itemtype, MapElementScreen *elementScreens, int elementScreensCount)
{
    for(int i=0; i<elementScreensCount; i++)
        if(elementScreens[i].itemType == itemtype)
            return elementScreens[i].surface;
    return NULL;
}

MapElement LEVEL_generateMapElement(SDL_Rect rect, SDL_Renderer *renderer, ItemType itemtype, bool isHighlighted, MapElementScreen *elementScreens, int elementScreensCount)
{
    if(itemtype >= IT_EMPTY && itemtype <= IT_H_WALL)
    {
        SDL_Surface surface = (*LEVEL_findSurfaceByItemType(itemtype, elementScreens, elementScreensCount));
        MapElementScreen elementScreen = {itemtype, &surface};
        MapElement element = {elementScreen, SDL_CreateTextureFromSurface(renderer, &surface), rect, isHighlighted, false};
        return element;
    }

    SDL_Surface surface = (*LEVEL_findSurfaceByItemType(IT_EMPTY, elementScreens, elementScreensCount));
    MapElementScreen elementScreen = {IT_EMPTY, &surface};
    MapElement element = {elementScreen, SDL_CreateTextureFromSurface(renderer, &surface), rect, isHighlighted, false};
    return element;
}

TEXT LEVEL_generateLegendText(SDL_Renderer *renderer, TEXT *legendText, char* text, int ordinal)
{
    if(legendText)
    {
        legendText->text = text;
        legendText->surface = MENU_generateTextsSurface(legendText->text, false, 16);
        legendText->texture = SDL_CreateTextureFromSurface(renderer, legendText->surface);
        SDL_Rect legendTextRect = {650,30*ordinal+50,60,30};
        legendText->rect = legendTextRect;
    }
    return *legendText;
}

MapElement LEVEL_generateMapElementLeftToText(TEXT *text, SDL_Renderer *renderer, ItemType itemtype, MapElementScreen *elementScreens, int elementScreensCount)
{
    SDL_Rect rect = {text->rect.x-(text->rect.h+20), text->rect.y ,text->rect.h, text->rect.h-1};
    MapElement element = LEVEL_generateMapElement(rect, renderer, itemtype, false, elementScreens, elementScreensCount);
    return element;
}

Legend* LEVEL_generateLegends(SDL_Renderer *renderer, int *legendsCount, MapElementScreen *elementScreens, int elementScreensCount)
{
    (*legendsCount) = 8;
    char *texts[] = {"Wall", "Enemy", "Coin", "Door", "Key", "Empty", "Player pos", "Player dest"};
    ItemType itemtypes[] = {IT_WALL, IT_ENEMY, IT_COIN, IT_DOOR, IT_KEY, IT_EMPTY, IT_PPOS, IT_PFIN};
    Legend* legends;
    legends = (Legend*)malloc((*legendsCount)*sizeof(Legend));
    for(int i=0; i<(*legendsCount); i++)
    {
        legends[i].text = LEVEL_generateLegendText(renderer, &legends[i].text, texts[i], i);
        legends[i].element = LEVEL_generateMapElementLeftToText(&legends[i].text, renderer, itemtypes[i], elementScreens, elementScreensCount);
    }
    return legends;
}

MapElement** LEVEL_generateMap(int *mapSizeX, int *mapSizeY, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount, int positionX, int positionY)
{
    (*mapSizeX) = MAP_SIZE_X;
    (*mapSizeY) = MAP_SIZE_Y;

    MapElement** map = (MapElement**)malloc((*mapSizeX)*sizeof(MapElement*));
    for(int x=0; x<(*mapSizeX); x++)
    {
        map[x] = (MapElement*)malloc((*mapSizeY)*sizeof(MapElement));
        for(int y=0; y<(*mapSizeY); y++)
        {
            SDL_Rect rect = {x*BOX_SIZE + positionX, y*BOX_SIZE + positionY, BOX_SIZE, BOX_SIZE};
            map[x][y] = LEVEL_generateMapElement(rect, renderer, IT_EMPTY, false, elementScreens, elementScreensCount);
        }
    }
    return map;
}

void LEVEL_highlightMapElement(MapElement *element, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount)
{
    if(!element->isHighlighted)
    {
        SDL_Rect rect = element->rect;
        ItemType itemType = element->elementScreen.itemType + 'H';
        (*element) = LEVEL_generateMapElement(rect, renderer, itemType, true, elementScreens, elementScreensCount);
    }
}

void LEVEL_unHighlightMapElement(MapElement *element, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount)
{
    if(element->isHighlighted)
    {
        SDL_Rect rect = element->rect;
        ItemType itemType = element->elementScreen.itemType - 'H';
        (*element) = LEVEL_generateMapElement(rect, renderer, itemType, false, elementScreens, elementScreensCount);
    }
}

void LEVEL_changeHighlight(Map_STRUCT *map, Legend_STRUCT *legend, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount, int mouseX, int mouseY)
{
    for(int x=0; x<map->mapSizeX; x++)
    {
        for(int y=0; y<map->mapSizeY; y++)
        {
            if(isOverRect(map->mapElements[x][y].rect, mouseX, mouseY))
                LEVEL_highlightMapElement(&map->mapElements[x][y], renderer, elementScreens, elementScreensCount);
            else
                LEVEL_unHighlightMapElement(&map->mapElements[x][y], renderer, elementScreens, elementScreensCount);
        }
    }

    for(int i=0; i<legend->legendsCount; i++)
    {
        if(isOverRect(legend->legends[i].element.rect, mouseX, mouseY) || legend->legends[i].element.isActive)
            LEVEL_highlightMapElement(&legend->legends[i].element, renderer, elementScreens, elementScreensCount);
        else
            LEVEL_unHighlightMapElement(&legend->legends[i].element, renderer, elementScreens, elementScreensCount);
    }
}

void LEVEL_setOtherElementToMap(MapElement *element, SDL_Renderer *renderer, ItemType itemType, MapElementScreen *elementScreens, int elementScreensCount)
{
    if(element->elementScreen.itemType != itemType)
        (*element) = LEVEL_generateMapElement(element->rect, renderer, itemType - 'H', false, elementScreens, elementScreensCount);
}

void LEVEL_fileGeneratedSplashScreen(System *system_data)
{
    SDL_RenderClear(system_data->renderer);
    SDL_Surface* surface = MENU_generateTextsSurface("Everything went perfectly", false, 100);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(system_data->renderer, surface);
    SDL_Rect rect = {80, 60, 700, 300};
    SDL_RenderCopy(system_data->renderer, texture, NULL, &rect);
    SDL_RenderPresent(system_data->renderer);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void LEVEL_CantCreateInfo(System *system_data)
{
  SDL_Rect firstTmp_rect = {50, 150, 680, 200};
  SDL_Texture* firstTextTexture;
  SDL_Surface* firstTextSurface = MENU_generateTextsSurface("Can't create level", true, 100);
  if( firstTextSurface != NULL )
  {
      firstTextTexture = SDL_CreateTextureFromSurface( system_data->renderer, firstTextSurface );
      if( firstTextTexture == NULL)
      {
          printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
      }

      SDL_FreeSurface( firstTextSurface );
  }
  else
  {
      printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  SDL_RenderClear( system_data->renderer );
  SDL_RenderCopy(system_data->renderer, firstTextTexture, NULL, &firstTmp_rect);
  SDL_RenderPresent( system_data->renderer );
  SDL_Delay(2000);
}

void LEVEL_processClickEvent(Map_STRUCT *map, Legend_STRUCT *legend, Button *createButton, Button *backButton, System *system_data, int mouseX, int mouseY)
{
    if(isOverRect(createButton->rect, mouseX, mouseY))
    {
        if(legend->playerDestX == -1 || legend->playerPosX == -1)
        {
          LEVEL_CantCreateInfo(system_data);
          return;
        }
        char levelName[3] = "";
        SDL_Rect tmp_rect = {50, 100, 650, 200};
        PLAYER_getTextFromUser(system_data, tmp_rect, "Enter number of level (max = 99)", levelName, 3);
        if(system_data->gameState == CREATE_LEVEL)
        {
            FILE_exportLevelToFile(map, levelName);
            LEVEL_fileGeneratedSplashScreen(system_data);
            SDL_Delay(1200);
            system_data->gameState = MENU;
        }
        return;
    }

    if(isOverRect(backButton->rect, mouseX, mouseY))
    {
        system_data->gameState = MENU;
        return;
    }

    if(legend->activelegendIndex != -1)
    {
        for(int x=0; x<map->mapSizeX; x++)
        {
            for(int y=0; y<map->mapSizeY; y++)
            {
                if(isOverRect(map->mapElements[x][y].rect, mouseX, mouseY))
                {
                    ItemType itemType = legend->legends[legend->activelegendIndex].element.elementScreen.itemType;
                    if(itemType == IT_PPOS || itemType == IT_H_PPOS)
                    {
                        if(legend->playerPosX != -1)
                        {
                            LEVEL_setOtherElementToMap(&map->mapElements[legend->playerPosX][legend->playerPosY], system_data->renderer, IT_EMPTY, system_data->mapElementsScreens, system_data->MapElementScreenCount);
                        }

                        legend->playerPosX = x;
                        legend->playerPosY = y;
                    }
                    else if(itemType == IT_PFIN || itemType == IT_H_PFIN)
                    {
                        if(legend->playerDestX != -1)
                        {
                            LEVEL_setOtherElementToMap(&map->mapElements[legend->playerDestX][legend->playerDestY], system_data->renderer, IT_EMPTY, system_data->mapElementsScreens, system_data->MapElementScreenCount);
                        }
                        legend->playerDestX = x;
                        legend->playerDestY = y;
                    }
                    else if(legend->playerPosX == x && legend->playerPosY == y)
                    {
                      legend->playerPosX = -1;
                      legend->playerPosY = -1;
                    }
                    else if(legend->playerDestX == x && legend->playerDestY == y)
                    {
                      legend->playerDestX = -1;
                      legend->playerDestY = -1;
                    }
                    LEVEL_setOtherElementToMap(&map->mapElements[x][y], system_data->renderer, itemType, system_data->mapElementsScreens, system_data->MapElementScreenCount);
                }
            }
        }
    }

    for(int i=0; i<legend->legendsCount; i++)
    {
        if(legend->activelegendIndex != -1 && i != legend->activelegendIndex)
            legend->legends[i].element.isActive = false;
        if(isOverRect(legend->legends[i].element.rect, mouseX, mouseY))
        {
            if(legend->legends[i].element.isActive)
            {
                legend->legends[i].element.isActive = false;
                legend->activelegendIndex = -1;
            }
            else
            {
                legend->legends[i].element.isActive = true;
                legend->activelegendIndex = i;
            }
        }
    }

}


void LEVEL_processEvent(System *system_data, Map_STRUCT *map, Legend_STRUCT *legend, Button *createButton, Button *backButton)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEMOTION:
                LEVEL_changeHighlight(map, legend, system_data->renderer, system_data->mapElementsScreens, system_data->MapElementScreenCount, event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONUP:
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    LEVEL_processClickEvent(map, legend, createButton, backButton, system_data, event.button.x, event.button.y);
                        break;
                }
                break;
            }
            case SDL_WINDOWEVENT_CLOSE:
                system_data->gameState = END;
                break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        system_data->gameState = END;
                    break;
                }
                break;
            }
            case SDL_QUIT:
                system_data->gameState = END;
                break;
        }
    }
}

Button LEVEL_generateButton(SDL_Renderer *renderer, ButtonType buttonType, SDL_Rect rect)
{
    SDL_Surface *surface;
    switch (buttonType)
    {
        case B_CREATE:
            surface = IMG_Load("../res/button_create.png");
            break;
        case B_BACK:
            surface = IMG_Load("../res/button_back.png");
            break;
        default:
            surface = NULL;
    }
    if(surface == NULL)
    {
        printf( "Unable to load image SDL_image Error: %s\n", IMG_GetError());
        Button tmp;
        return tmp;
    }

    Button button = {surface, SDL_CreateTextureFromSurface(renderer, surface), rect};
    return button;
}

void LEVEL_updateLevelNumber(System *system_data, Level *level, SDL_Texture** levelTextTexture)
{
    char buffer[NAME_BUFFER_SIZE] = "";
    sprintf(buffer, "level: %d", level->order);
    SDL_Surface* levelTextsurface = MENU_generateTextsSurface(buffer, false, 50);
    (*levelTextTexture) = SDL_CreateTextureFromSurface(system_data->renderer, levelTextsurface);
    SDL_FreeSurface(levelTextsurface);
}

void LEVEL_generateMapTexture(System *system_data, Map_STRUCT *map, SDL_Texture** texture)
{
    (*texture) = SDL_CreateTexture(system_data->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    SDL_SetRenderTarget(system_data->renderer, (*texture));
    SDL_RenderClear( system_data->renderer );
    for(int x=0; x<map->mapSizeX; x++)
        for(int y=0; y<map->mapSizeY; y++)
            SDL_RenderCopy(system_data->renderer, map->mapElements[x][y].texture, NULL, &map->mapElements[x][y].rect);

    SDL_SetRenderTarget(system_data->renderer, NULL);
}

bool LEVEL_getNextLevel(int *currentLevel, char filename[8])
{
    bool isNextExists = false;
    for(int i=(*currentLevel); i < 100; i++)
    {
        memset(filename, 0, 8*sizeof(char));
        FILE *file;
        if(i < 10)
        {
            sprintf(filename, "0%d", i);
            strncat(filename, ".map", 4);
            if((file = (FILE*)fopen(filename, "rb+")) != NULL)
            {
                fclose(file);
                (*currentLevel) = i;
                isNextExists = true;
                break;
            }
            memset(filename, 0, 8*sizeof(char));
        }
        sprintf(filename, "%d", i);
        strncat(filename, ".map", 4);
        if((file = (FILE*)fopen(filename, "rb+")) != NULL)
        {
            fclose(file);
            isNextExists = true;
            (*currentLevel) = i;
            break;
        }
    }

    return isNextExists;
}

void LEVEL_renderLevelItems(Level *level, System *system_data)
{
    Enemy_STRUCT *E_tmp = level->enemies;
    while (E_tmp) {
        SDL_RenderCopy(system_data->renderer, E_tmp->enemy.texture, NULL, &E_tmp->enemy.rect);
        E_tmp = (Enemy_STRUCT*)E_tmp->next;
    }
    Door_STRUCT *D_tmp = level->doors;
    while (D_tmp) {
        if(D_tmp->door.isClosed)
            SDL_RenderCopy(system_data->renderer, D_tmp->door.closedTexture, NULL, &D_tmp->door.rect);
        else
            SDL_RenderCopy(system_data->renderer, D_tmp->door.openTexture, NULL, &D_tmp->door.rect);
        D_tmp = (Door_STRUCT*)D_tmp->next;
    }
    Key_STRUCT *K_tmp = level->keys;
    while (K_tmp) {
        SDL_RenderCopy(system_data->renderer, K_tmp->key.texture, NULL, &K_tmp->key.rect);
        K_tmp = (Key_STRUCT*)K_tmp->next;
    }
    Coin_STRUCT *C_tmp = level->coins;
    while (C_tmp) {
        SDL_RenderCopy(system_data->renderer, C_tmp->coin.texture, NULL, &C_tmp->coin.rect);
        C_tmp = (Coin_STRUCT*)C_tmp->next;
    }
}

void LEVEL_deleteCoinAtRect(Coin_STRUCT** head, SDL_Rect target)
{
    if((*head))
	{
        if(isCollision(target, (*head)->coin.rect))
		{
			Coin_STRUCT* tmp = (*head);
			(*head) = (Coin_STRUCT*)tmp->next;
			SDL_DestroyTexture(tmp->coin.texture);
            free(tmp);
			return;
		}
		if((*head)->next)
		{
			if(isCollision((*head)->next->coin.rect, target))
			{
                Coin_STRUCT* tmp = (Coin_STRUCT*)(*head)->next;
                (*head)->next = (*head)->next->next;
                SDL_DestroyTexture(tmp->coin.texture);
                free(tmp);
			}
			else
			{
				LEVEL_deleteCoinAtRect(&(*head)->next, target);
			}
		}
	}
}

void LEVEL_deleteKeyAtRect(Key_STRUCT** head, SDL_Rect target)
{
    if((*head))
	{
        if(isCollision(target, (*head)->key.rect))
		{
			Key_STRUCT* tmp = (*head);
			(*head) = (Key_STRUCT*)tmp->next;
			SDL_DestroyTexture(tmp->key.texture);
            free(tmp);
			return;
		}
		if((*head)->next)
		{
			if(isCollision((*head)->next->key.rect, target))
			{
                Key_STRUCT* tmp = (Key_STRUCT*)(*head)->next;
                (*head)->next = (*head)->next->next;
                SDL_DestroyTexture(tmp->key.texture);
                free(tmp);
			}
			else
			{
				LEVEL_deleteKeyAtRect(&(*head)->next, target);
			}
		}
	}
}
