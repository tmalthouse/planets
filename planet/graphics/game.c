//
//  game.c
//  planet
//
//  Created by Thomas Malthouse on 5/7/16.
//  Copyright © 2016 Thomas Malthouse. All rights reserved.
//

#include "game.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "texture.h"
#include "planet_sprite.h"
#include "../debug.h"
#include "../darray_types.h"
#include "../cbody.h"
#include "../planet.h"

ScreenComponents startgame()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't start SDL. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, NULL, NULL};
    }
    dprintf("Initialized video.\n");
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    SDL_Window *window = SDL_CreateWindow("planet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        fprintf(stderr, "Couldn't create a window. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, NULL, NULL};
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//For some reason, the flags aren't working.
    
    if (renderer == NULL) {
        fprintf(stderr, "Couldn't create a renderer. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, window, NULL};
    }
    
    SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x33, 0x55);
    
    int imgFlags = IMG_INIT_PNG;
    if(!( IMG_Init( imgFlags ) & imgFlags)) {
        fprintf(stderr, "Couldn't initialize SDL_Image. Error: %s\n", IMG_GetError());
        return (ScreenComponents){false, window, renderer};
    }
    
    return (ScreenComponents){true, window, renderer};
    
}

void closegame (ScreenComponents components)
{
    SDL_DestroyRenderer(components.renderer);
    SDL_DestroyWindow(components.window);
    
    IMG_Quit();
    SDL_Quit();
}

int rungame(Darray_CBody *system)
{
    int status = 0;
    ScreenComponents components = startgame();
    if (components.status == false) {
        status--;
        goto err;
    }
    dprintf("Components are good.\n");
    
    Texture *planettex = load_texture("/Users/Thomas/Desktop/planet.bmp", components.renderer);
    if (planettex == NULL) {
        status--;
        goto err;
    }
    
    bool quit = false;
    SDL_Event event;
    Darray_PSprite *disp_system = new_darray_PSprite(system->len);
    PSprite *sprite = disp_system->data;
    CBody *body = system->data;
    
    dprintf("Darray_PSprite *created. Initial len is %d, cap is %d\n.", disp_system->len, disp_system->cap);
    screencoord_set(absmaxpos(system));
    
    dprintf("Filling disp_system.\n");
    for (int i=0; i<system->len; i++) {
        darray_append_PSprite(disp_system, new_psprite(body+i, planettex));
        dprintf("Filled index %d. Name is %s\n", i, sprite[i].rootbody->name);
    }
    
    dprintf("Len of disp_system is %d\n", disp_system->len);
    #ifdef DEBUG
    int counter = 0;
    #endif
    
    while (!quit) {
        dprintf("Starting loop %d.\n", counter++);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        dprintf("Left event poll\n");
        cbody_update(system, 1*24*60*60);
        
        for (int i=0; i<disp_system->len; i++) {
            dprintf("Moving sprite %d\n", i);
            psprite_update(sprite+i);
            dprintf("The actual coordinates of body %d are (%f, %f)\n", i, body[i].pos.x, body[i].pos.y);
            dprintf("Its screen coordinates are (%f, %f)\n", sprite[i].screenpos.x, sprite[i].screenpos.y);
        }
        
        SDL_SetRenderDrawColor(components.renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(components.renderer);
        
        for (int i=0; i<disp_system->len; i++) {
            dprintf("Rendering sprite %d\n",i);
            psprite_render(sprite+i, components.renderer);
        }
        
        SDL_RenderPresent(components.renderer);
        //SDL_Delay(5);
    }
    free_darray_PSprite(disp_system);
    
    err://We jump here if there's an error, but passing here DOES NOT mean an error occured.
    
    closegame(components);
    return status;
}
