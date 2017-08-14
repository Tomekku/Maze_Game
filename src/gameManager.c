#include "../include/gameManager.h"

void loadMenu(System *system_data)
{
    TEXT_STRUCT menuTexts;

    menuTexts.texts = (TEXT*)MENU_generateTexts(system_data->renderer, &menuTexts.textsCount);


    bool end = false;
    while(system_data->gameState == MENU)
    {
        SDL_RenderClear(system_data->renderer);
        MENU_processKeyEvent(system_data, &menuTexts);
        for(int i=0; i<menuTexts.textsCount; i++)
            SDL_RenderCopy(system_data->renderer, menuTexts.texts[i].texture, NULL, &menuTexts.texts[i].rect);
        SDL_RenderPresent(system_data->renderer);
        SDL_Delay(100);
    }
    MENU_freeTexts(&menuTexts);
}

void loading(System *system_data)
{
    SDL_RenderClear(system_data->renderer);
    SDL_Surface* surface = IMG_Load("../res/loading.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(system_data->renderer, surface);
    int windowH, windowW;
    SDL_GetWindowSize(system_data->window, &windowW, &windowH);
    SDL_Rect rect = {0, 0, windowW, windowH};
    SDL_RenderCopy(system_data->renderer, texture, NULL, &rect);
    SDL_RenderPresent(system_data->renderer);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void lastLevelInfo(System *system_data)
{
    SDL_Rect firstTmp_rect = {50, 100, 680, 200};
    SDL_Texture* firstTextTexture;
    SDL_Surface* firstTextSurface = MENU_generateTextsSurface("Congratulations!!!", true, 100);
    SDL_Rect secondTmp_rect = {45, 300, 690, 200};
    SDL_Texture* secondTextTexture;
    SDL_Surface* secondTextSurface = MENU_generateTextsSurface("You've complete all levels", false, 100);
    if( firstTextSurface != NULL || secondTextSurface != NULL)
    {
        firstTextTexture = SDL_CreateTextureFromSurface( system_data->renderer, firstTextSurface );
        secondTextTexture = SDL_CreateTextureFromSurface( system_data->renderer, secondTextSurface );
        if( firstTextTexture == NULL || secondTextTexture == NULL)
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }

        SDL_FreeSurface( firstTextSurface );
        SDL_FreeSurface( secondTextSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_RenderClear( system_data->renderer );
    SDL_RenderCopy(system_data->renderer, firstTextTexture, NULL, &firstTmp_rect);
    SDL_RenderCopy(system_data->renderer, secondTextTexture, NULL, &secondTmp_rect);
    SDL_RenderPresent( system_data->renderer );
    system_data->gameState = MENU;
    SDL_Delay(2000);
}

void playerDiedInfo(System *system_data)
{
    SDL_Rect firstTmp_rect = {50, 150, 680, 200};
    SDL_Texture* firstTextTexture;
    SDL_Surface* firstTextSurface = MENU_generateTextsSurface("You died :-(", true, 100);
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
    system_data->gameState = MENU;
    SDL_Delay(2000);
}

void noLevelInfo(System *system_data)
{
    SDL_Rect firstTmp_rect = {50, 150, 680, 200};
    SDL_Texture* firstTextTexture;
    SDL_Surface* firstTextSurface = MENU_generateTextsSurface("There is no level created :(", true, 100);
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
    system_data->gameState = MENU;
    SDL_Delay(2000);
}

void submitLastScore(System *system_data, Player *player, Level *level)
{
    char playerName[21] = "";
    SDL_Rect tmp_rect = {50, 100, 650, 200};
    PLAYER_getTextFromUser(system_data, tmp_rect, "Enter your name (max 20 characters)", playerName, 21);
    if(system_data->gameState != END)
        FILE_updateScoreList(playerName, player->score);
    player->isAlive = true;
    player->keyCount = 0;
    player->score = 0;
    player->direction = STOP;
    level->order = 0;
}

void openLevelGenerator(System *system_data)
{
    loading(system_data);

    SDL_Rect createButtonRect = {650,500,106,38};
    Button createButton = LEVEL_generateButton(system_data->renderer, B_CREATE, createButtonRect);
    SDL_Rect backButtonRect = {100, 550, 106, 38};
    Button backButton = LEVEL_generateButton(system_data->renderer, B_BACK, backButtonRect);
    Map_STRUCT map;
    map.posX = 0;
    map.posY = 0;
    map.mapElements = LEVEL_generateMap(&map.mapSizeX, &map.mapSizeY, system_data->renderer, system_data->mapElementsScreens, system_data->MapElementScreenCount, map.posX, map.posY);
    Legend_STRUCT legend;
    legend.legends = LEVEL_generateLegends(system_data->renderer, &legend.legendsCount, system_data->mapElementsScreens, system_data->MapElementScreenCount);
    legend.activelegendIndex = -1;
    legend.playerPosX = -1;
    legend.playerPosY = -1;
    legend.playerDestX = -1;
    legend.playerDestY = -1;


    while (system_data->gameState == CREATE_LEVEL)
    {
        SDL_RenderClear(system_data->renderer);
        LEVEL_processEvent(system_data, &map, &legend, &createButton, &backButton);

        for(int i=0; i<legend.legendsCount; i++)
        {
            SDL_RenderCopy(system_data->renderer,legend.legends[i].text.texture, NULL, &legend.legends[i].text.rect);
            SDL_RenderCopy(system_data->renderer, legend.legends[i].element.texture, NULL, &legend.legends[i].element.rect);
        }
        for(int x=0; x<map.mapSizeX; x++)
            for(int y=0; y<map.mapSizeY; y++)
                SDL_RenderCopy(system_data->renderer, map.mapElements[x][y].texture, NULL, &map.mapElements[x][y].rect);
        SDL_RenderCopy(system_data->renderer, createButton.texture, NULL, &createButton.rect);
        SDL_RenderCopy(system_data->renderer, backButton.texture, NULL, &backButton.rect);
        SDL_RenderPresent(system_data->renderer);
        SDL_Delay(50);
    }

    LEVEL_deleteButton(&createButton);
    LEVEL_deleteButton(&backButton);
    LEVEL_deleteLegend(&legend);
    LEVEL_deleteMap(&map);
}

void getLevel(Player *player, Level *level, System *system_data)
{
    char filename[8] = "";
    if(LEVEL_getNextLevel(&level->order, filename))
    {
        level->map = FILE_importLevelFromFile(filename, system_data, player, level);
        system_data->gameState = GAME;
    }
    else
    {
        if(level->order != 0)
        {
            lastLevelInfo(system_data);
            submitLastScore(system_data, player, level);
        }
        else
        {
            noLevelInfo(system_data);
        }
    }
}

void playGame(Player *player, Level *level, System *system_data)
{
    SDL_Texture* scoreTextTexture = NULL;
    SDL_Rect scoreTextRect = {610,20,60,30};
    SDL_Texture* keyCountTextTexture = NULL;
    SDL_Rect keyCountTextRect = {540,20,60,30};
    SDL_Texture* levelTextTexture = NULL;
    SDL_Rect levelTextRect = {460,20,60,30};
    SDL_Texture *mapTexture = NULL;

    LEVEL_generateMapTexture(system_data, &level->map, &mapTexture);

    while (system_data->gameState == GAME)
    {
        if(isCollision(player->rect, level->endRect))
        {
            level->order++;
            system_data->gameState = LEVEL;
            break;
        }
        if(!player->isAlive)
        {
            playerDiedInfo(system_data);
            submitLastScore(system_data, player, level);
            break;
        }
        PLAYER_processEvents(system_data, player);


        PLAYER_updatePlayerScore(system_data, player, &scoreTextTexture);
        PLAYER_updatePlayerKeyCount(system_data, player, &keyCountTextTexture);
        LEVEL_updateLevelNumber(system_data, level, &levelTextTexture);

        PLAYER_updatePlayer(player, level);
        animate(system_data, 'P', 1, player);
        ENEMY_updateEnemies(level);
        SDL_RenderClear(system_data->renderer);
        SDL_RenderCopy(system_data->renderer, mapTexture, NULL, NULL);
        SDL_RenderCopy(system_data->renderer, scoreTextTexture, NULL, &scoreTextRect);
        SDL_RenderCopy(system_data->renderer, keyCountTextTexture, NULL, &keyCountTextRect);
        SDL_RenderCopy(system_data->renderer, levelTextTexture, NULL, &levelTextRect);
        LEVEL_renderLevelItems(level, system_data);
        SDL_RenderCopy(system_data->renderer, player->texture, NULL, &player->rect);
        SDL_RenderPresent(system_data->renderer);
        SDL_Delay(10);
    }
    SDL_DestroyTexture(scoreTextTexture);
    SDL_DestroyTexture(levelTextTexture);
    LEVEL_deleteLevel(level);
}


void init(System *system_data, Level *level, Player *player)
{
    int IMGFlags = IMG_INIT_PNG;
    if(IMG_Init(IMGFlags) & IMGFlags != IMGFlags)
    {
        printf("IMG_Init: %s\n", IMG_GetError());
        system_data->gameState = END;
        return;
    }

    if(TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        system_data->gameState = END;
        return;
    }

    SDL_Init(SDL_INIT_VIDEO);
    system_data->gameState = MENU;
    system_data->window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600, 0);
    system_data->renderer = SDL_CreateRenderer(system_data->window, -1, SDL_RENDERER_ACCELERATED);

    ItemType itemtypes[] = {IT_WALL, IT_ENEMY, IT_COIN, IT_DOOR, IT_O_DOOR, IT_KEY, IT_EMPTY, IT_PPOS, IT_PFIN, IT_H_WALL, IT_H_ENEMY, IT_H_COIN, IT_H_DOOR, IT_H_KEY, IT_H_EMPTY, IT_H_PPOS, IT_H_PFIN};
    system_data->MapElementScreenCount = 17;
    system_data->mapElementsScreens = (MapElementScreen*)malloc(system_data->MapElementScreenCount*sizeof(MapElementScreen));
    for(int i=0; i<system_data->MapElementScreenCount && system_data->gameState != END; i++)
        system_data->mapElementsScreens[i] = LEVEL_createMapElementsScreen(itemtypes[i], system_data);

    level->order = 0;
    level->walls = NULL;
    level->coins = NULL;
    level->enemies = NULL;
    level->doors = NULL;
    level->keys = NULL;

    player->speed = 1;
    player->keyCount = 0;
    player->score = 0;
    player->isAlive = true;
    player->direction = STOP;
    player->texture = NULL;
    initAnimate(system_data, &player->animationStruct, 'P');
}

void cleanUp(System *system_data)
{
    SDL_RenderClear(system_data->renderer);
    LEVEL_deleteMapElementScreens(system_data->mapElementsScreens, system_data->MapElementScreenCount);
    SDL_DestroyRenderer(system_data->renderer);
    SDL_DestroyWindow(system_data->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void runGame()
{
    System system_data;
    Player player;
    Level level;
    init(&system_data, &level, &player);

    while(system_data.gameState != END)
    {
        switch(system_data.gameState)
        {
            case MENU:
                loadMenu(&system_data);
                break;
            case LEVEL:
                getLevel(&player, &level, &system_data);
                break;
            case GAME:
                playGame(&player, &level, &system_data);
                break;
            case CREATE_LEVEL:
                openLevelGenerator(&system_data);
                break;
        }
    }
    PLAYER_deletePlayer(&player);
    cleanUp(&system_data);
}
