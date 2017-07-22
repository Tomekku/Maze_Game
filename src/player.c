#include "../include/player.h"

void PLAYER_updatePlayer(Player *player, Level *level)
{
    if(isCollideWithCoins(player->rect, level->coins))
    {
        player->score++;
        LEVEL_deleteCoinAtRect(&level->coins, player->rect);
    }
    if(isCollideWithKeys(player->rect, level->keys))
    {
        player->keyCount++;
        LEVEL_deleteKeyAtRect(&level->keys, player->rect);
    }
    
    PLAYER_updatePlayerRect(player, level); 
    if(isCollideWithEnemies(player->rect, level->enemies))
        player->isAlive = false;
}

void PLAYER_updatePlayerRect(Player *player, Level *level)
{
    SDL_Rect tmp_rect = player->rect;
    switch (player->direction) {
        case LEFT:
            tmp_rect.x -= player->speed;
            break;
        case LEFT_UP:
            tmp_rect.x -= player->speed;
            tmp_rect.y -= player->speed;
            break;
        case LEFT_DOWN:
            tmp_rect.x -= player->speed;
            tmp_rect.y += player->speed;
            break;
        case RIGHT:
            tmp_rect.x += player->speed;
            break;
        case RIGHT_UP:
            tmp_rect.x += player->speed;
            tmp_rect.y -= player->speed;
            break;
        case RIGHT_DOWN:
            tmp_rect.x += player->speed;
            tmp_rect.y += player->speed;
            break;
        case UP:
            tmp_rect.y -= player->speed;
            break;
        case DOWN:
            tmp_rect.y += player->speed;
            break;
        default:
            break;
    }
    if(!isCollideWithWalls(tmp_rect, level->walls) && !isPlayerCollideWithDoors(player, tmp_rect, level->doors) && !isOutsideMap(tmp_rect, level))
        player->rect = tmp_rect;
}

void PLAYER_processEvents(System *system_data, Player *player)
{
    
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        
        switch (event.type) 
        {
            case SDL_WINDOWEVENT_CLOSE:
                system_data->gameState = END;
                break;
            case SDL_QUIT:
                system_data->gameState = END;
                break;
            default:
                break;
        }
    }    
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_A])
        player->direction = LEFT_UP;
    else if(keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_D])
        player->direction = RIGHT_UP;
    else if(keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_A])
        player->direction = LEFT_DOWN;
    else if(keystate[SDL_SCANCODE_S] && keystate[SDL_SCANCODE_D])
        player->direction = RIGHT_DOWN;
    else if(keystate[SDL_SCANCODE_W] )
        player->direction = UP;
    else if(keystate[SDL_SCANCODE_S])
        player->direction = DOWN;
    else if(keystate[SDL_SCANCODE_A] )
        player->direction = LEFT;
    else if(keystate[SDL_SCANCODE_D])
        player->direction = RIGHT;
    else if(keystate[SDL_SCANCODE_ESCAPE])
        system_data->gameState = MENU;
    else if(!keystate[SDL_SCANCODE_D] && !keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_S] && !keystate[SDL_SCANCODE_W])
        player->direction = STOP;
            
}

void PLAYER_getTextFromUser(System *system_data, SDL_Rect entryTextRect, char* entryText, char* inputText, int inputTextSize)
{
    bool quit = false;
    
    SDL_Event e;
    int currentLast = -1;
    
    SDL_Texture* entryTextTexture = NULL;
    SDL_Surface* entryTextSurface = MENU_generateTextsSurface(entryText, false, 100);
    if( entryTextSurface != NULL )
    {
        entryTextTexture = SDL_CreateTextureFromSurface( system_data->renderer, entryTextSurface );
        if( entryTextTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        
        SDL_FreeSurface( entryTextSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_RenderClear( system_data->renderer );
    SDL_RenderCopy(system_data->renderer, entryTextTexture, NULL, &entryTextRect);
    SDL_RenderPresent( system_data->renderer );
    SDL_StartTextInput();

    while( !quit )
    {
        
        bool renderText = false;
        SDL_Texture *texture = NULL;
        while( SDL_PollEvent( &e ))
        {
            if( e.type == SDL_QUIT )
            {
                system_data->gameState = END;
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                if( e.key.keysym.sym == SDLK_BACKSPACE && currentLast >= 0 )
                {
                    if(currentLast == 0)
                        inputText[currentLast] = ' ';
                    else
                        inputText[currentLast] = '\0';
                    currentLast--;
                    
                    renderText = true;
                } else if(e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER)
                {
                    if(inputText[0] != '\0' && inputText[0] != ' ')
                        quit = true;
                }
            }
            else if( e.type == SDL_TEXTINPUT )
            {
                if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
                {
                    if(currentLast+1 < inputTextSize-1)
                    {
                        currentLast++;
                        inputText[currentLast] = e.text.text[0];
                    }
                    renderText = true;
                }
            }
        }
        if( renderText )
        {
            if( inputText != "" )
            {
                SDL_Surface* textSurface = MENU_generateTextsSurface(inputText, true, 100);
                if( textSurface != NULL )
                {
                    texture = SDL_CreateTextureFromSurface( system_data->renderer, textSurface );
                    if( texture == NULL )
                    {
                        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                    }
                    
                    SDL_FreeSurface( textSurface );
                }
                else
                {
                    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
                }
            }
            else
            {
                SDL_Surface* textSurface = MENU_generateTextsSurface(" ", false, 100);
                if( textSurface != NULL )
                {
                    texture = SDL_CreateTextureFromSurface( system_data->renderer, textSurface );
                    if( texture == NULL )
                    {
                        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
                    }
                
                    SDL_FreeSurface( textSurface );
                }
                else
                {
                    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
                }
            }
            
            SDL_Rect rect = {entryTextRect.x, entryTextRect.y+entryTextRect.h, (entryTextRect.w/strlen(entryText))*(currentLast+1), entryTextRect.h/3};
            SDL_RenderClear( system_data->renderer );
            SDL_RenderCopy(system_data->renderer, entryTextTexture, NULL, &entryTextRect);
            SDL_RenderCopy(system_data->renderer, texture, NULL, &rect);
            SDL_RenderPresent( system_data->renderer );
        }
        
    }
    
    SDL_StopTextInput();
}

void PLAYER_updatePlayerScore(System *system_data, Player *player, SDL_Texture** scoreTextTexture)
{
    char buffer[NAME_BUFFER_SIZE] = "";
    sprintf(buffer, "score: %d", player->score);
    SDL_Surface* scoreTextsurface = MENU_generateTextsSurface(buffer, false, 50);
    (*scoreTextTexture) = SDL_CreateTextureFromSurface(system_data->renderer, scoreTextsurface);
    SDL_FreeSurface(scoreTextsurface);
}

void PLAYER_updatePlayerKeyCount(System *system_data, Player *player, SDL_Texture** keyCountTextTexture)
{
    char buffer[NAME_BUFFER_SIZE] = "";
    sprintf(buffer, "keys: %d", player->keyCount);
    SDL_Surface* keyCountTextsurface = MENU_generateTextsSurface(buffer, false, 50);
    (*keyCountTextTexture) = SDL_CreateTextureFromSurface(system_data->renderer, keyCountTextsurface);
    SDL_FreeSurface(keyCountTextsurface);
}

void PLAYER_deletePlayer(Player *player)
{
    SDL_FreeSurface(player->surface);
    SDL_DestroyTexture(player->texture);
}