#include "../include/mainMenu.h"


SDL_Surface* MENU_generateTextsSurface(char* text, bool active, int fontSize)
{
    char fontPath[10000];
    const char *fontName = "../res/Aleo-Regular.otf";
    realpath(fontName, fontPath);
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if(font == NULL)
    {
        printf( "Unable to load font   Error: %s\n", TTF_GetError());
    }

    SDL_Surface* surface;
    SDL_Color activeColor = {0, 0, 255};
    SDL_Color inactiveColor = {255, 255, 255};
    if(active)
        surface = TTF_RenderText_Solid(font, text, activeColor);
    else
        surface = TTF_RenderText_Solid(font, text, inactiveColor);
    TTF_CloseFont(font);
    return surface;
}

TEXT* MENU_generateTexts(SDL_Renderer *renderer, int *textsCount)
{
    (*textsCount) = 3;
    char *texts[] = {"Start game", "Create level", "     Exit     "};

    TEXT* menuTexts;
    menuTexts = (TEXT*)malloc((*textsCount)*sizeof(TEXT));
    for(int i=0; i<(*textsCount); i++)
    {
        menuTexts[i].text = texts[i];
        menuTexts[i].surface = MENU_generateTextsSurface(menuTexts[i].text, false, 36);
        menuTexts[i].texture = SDL_CreateTextureFromSurface(renderer, menuTexts[i].surface);
        SDL_Rect menuTextsRect = {250,100*i+70,300,70};
        menuTexts[i].rect = menuTextsRect;
    }
    return menuTexts;
}

void MENU_freeTexts(TEXT_STRUCT* menuTexts)
{
    for(int i=0; i<menuTexts->textsCount; i++){
        SDL_DestroyTexture(menuTexts->texts[i].texture);
        SDL_FreeSurface(menuTexts->texts[i].surface);
    }
    free(menuTexts->texts);
}

void MENU_changeTextColor(TEXT_STRUCT* menuTexts, SDL_Renderer *renderer, int mouseX, int mouseY)
{
    int index = -1;
    for(int i=0; i<menuTexts->textsCount; i++)
    {
        SDL_FreeSurface(menuTexts->texts[i].surface);
        if(isOverRect(menuTexts->texts[i].rect, mouseX, mouseY))
            menuTexts->texts[i].highlighted = true;
        else
            menuTexts->texts[i].highlighted = false;
            
        menuTexts->texts[i].surface = MENU_generateTextsSurface(menuTexts->texts[i].text, menuTexts->texts[i].highlighted, 36);

        SDL_DestroyTexture(menuTexts->texts[i].texture);
        menuTexts->texts[i].texture = SDL_CreateTextureFromSurface(renderer, menuTexts->texts[i].surface);
    }
}

void MENU_processEvents(System *system_data, TEXT_STRUCT* menuTexts, int mouseX, int mouseY)
{
    int index = -1;
    for(int i=0; i<menuTexts->textsCount; i++)
    {
        if(isOverRect(menuTexts->texts[i].rect, mouseX, mouseY))
        {
            index = i;
            break;
        }
    }
    switch (index)
    {
        case 0:
            //Start game
            system_data->gameState = LEVEL;
            break;
        case 1:
            // create level
            system_data->gameState = CREATE_LEVEL;
            break;
        case 2:
            // exit
            system_data->gameState = END;
            break;
        default:
            break;
    }
}

void MENU_processKeyEvent(System *system_data, TEXT_STRUCT* menuTexts)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEMOTION:
                MENU_changeTextColor(menuTexts, system_data->renderer, event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONUP:
            {
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        MENU_processEvents(system_data, menuTexts, event.button.x, event.button.y);
                        break;
                }
            }
            break;
            case SDL_WINDOWEVENT_CLOSE:
            {
                system_data->gameState = END;
            }
            break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        system_data->gameState = END;
                    break;
                }
            }
            break;
            case SDL_QUIT:
                system_data->gameState = END;
            break;
        }
    }
}
