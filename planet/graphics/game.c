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
#include "timer.h"
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
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
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
    
    TTF_Init();
    TTF_Font *lbl_font = TTF_OpenFont("/Users/Thomas/Library/Fonts/Consolas.ttf", 12);
    
    dprintf("Filling disp_system.\n");
    for (int i=0; i<system->len; i++) {
        Texture *tex = load_texture("/Users/Thomas/Desktop/planet.bmp", components.renderer);
        texture_set_color(tex, body[i].color);
        darray_append_PSprite(disp_system, new_psprite(body+i, tex));
        dprintf("Filled index %d. Name is %s\n", i, sprite[i].rootbody->name);
        
        tex = create_label(body[i].name, body[i].color, lbl_font, components.renderer);
        disp_system->data[i].label = tex;
    }
    
    dprintf("Len of disp_system is %d\n", disp_system->len);
    
    int counter = 0;
    int updates_per_frame = 20;
    bool paused = false;
    
    Timer framecontrol = new_timer();
    
    while (!quit) {
        start_timer(&framecontrol);
        
        //dprintf("Starting loop %d.\n", counter);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_PERIOD:
                        updates_per_frame+=10;
                        break;
                    case SDLK_COMMA:
                        if (updates_per_frame>=10) {
                            updates_per_frame-=10;
                        }
                        break;
                    case SDLK_ESCAPE:
                        paused = !paused;
                        break;
                    default:
                        break;
                }
                dprintf("Updates per frame: %d\n", updates_per_frame);
            }
        }
        
        vdprintf("Left event poll\n"); //Only update if we're not paused
        for (int i=0; i<updates_per_frame*!paused; i++) {
            cbody_update(system, ONE_DAY);
            counter++;
        }
        
        for (int i=0; i<disp_system->len; i++) {
            vdprintf("Moving sprite %d\n", i);
            psprite_update(sprite+i);
            vdprintf("The actual coordinates of body %d are (%f, %f)\n", i, body[i].pos.x, body[i].pos.y);
            vdprintf("Its screen coordinates are (%f, %f)\n", sprite[i].screenpos.x, sprite[i].screenpos.y);
        }
        
        SDL_SetRenderDrawColor(components.renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(components.renderer);
        
        for (int i=0; i<disp_system->len; i++) {
            psprite_render(sprite+i, components.renderer);
        }
        
        int x, y;
        SDL_GetMouseState(&x, &y);
        render_labels(disp_system, (Coordinate){x, y}, components.renderer);
        
        SDL_RenderPresent(components.renderer);
        
        if (get_time(&framecontrol) < 1000/MAX_FPS) {
            SDL_Delay((1000/MAX_FPS) - (uint32_t)get_time(&framecontrol));
        }
        if (counter%365==0) {
            printf("Starting earth year %d.\n", counter/365);
        }
    }
    for (int i=0; i<disp_system->len; i++) {
        free(disp_system->data[i].texture);
    }
    free_darray_PSprite(disp_system);
    
    err://We jump here if there's an error, but passing here DOES NOT mean an error occured.
    
    closegame(components);
    return status;
}
