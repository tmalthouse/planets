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
#include "message.h"
#include "../debug.h"
#include "../darray_types.h"
#include "../cbody.h"
#include "../planet.h"

ScreenComponents video_init()
{
    //Start the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Couldn't start SDL. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, NULL, NULL};
    }
    dprintf("Initialized video.\n");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //Create a window
    SDL_Window *window = SDL_CreateWindow("planet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Couldn't create a window. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, NULL, NULL};
    }

    //Set up a renderer system
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        fprintf(stderr, "Couldn't create a renderer. Error: %s\n", SDL_GetError());
        return (ScreenComponents){false, window, NULL};
    }

    //Give it whatever  this color is
    SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x33, 0x55);

    //Start the image subsystem
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

    //Save the things from startup
    ScreenComponents components = video_init();
    if (components.status == false) {
        status--;
        goto err;
    }
    dprintf("Components are good.\n");

    bool quit = false;
    SDL_Event event;

    //Prepare the solar system to be displayed
    Darray_PSprite *disp_system = new_darray_PSprite(system->len);
    PSprite *sprite = disp_system->data;
    CBody *body = system->data;

    dprintf("Darray_PSprite *created. Initial len is %d, cap is %d\n.", disp_system->len, disp_system->cap);
    
    
    //Set the screen conversion factor
    Coordinate max = absmaxpos(system);
    dprintf("x=%f, y=%f\n", max.x,  max.y);
    screencoord_set(max, vfmult(max, -1));
    
    
    
    //Start up the font for planet labels and message display
    TTF_Init();
    TTF_Font *lbl_font = TTF_OpenFont("/Library/Fonts/AppleGothic.ttf", 12);

    dprintf("Filling disp_system.\n");
    for (int i=0; i<system->len; i++) {
        //Set up the texture for each cbody
        Texture *tex = load_texture("/Users/Thomas/Desktop/planet.bmp", components.renderer);
        texture_set_color(tex, body[i].color);
        darray_append_PSprite(disp_system, new_psprite(body+i, tex));
        dprintf("Filled index %d. Name is %s\n", i, sprite[i].rootbody->name);

        //And create and save its label, in the same color as the body itself
        tex = create_label(body[i].name, body[i].color, lbl_font, components.renderer);
        disp_system->data[i].label = tex;
    }

    dprintf("Len of disp_system is %d\n", disp_system->len);

    //Set up the message system
    TTF_Font *messagefont = TTF_OpenFont("/Library/Fonts/AppleGothic.ttf", 16);
    Message m = new_message((Coordinate){360,80}, messagefont, components.renderer);

    //Set up variables for the main game loop
    int counter = 0;
    int updates_per_frame = 20;
    bool paused = false;
    Timer framecontrol = new_timer();

    while (!quit) {
        start_timer(&framecontrol);

        //Check for events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                
                case SDL_MOUSEWHEEL:
                    {
                        double direction = (event.wheel.y > 0) ? 1 : -1;
                        screencoord_zoom(direction);
                    }
                    break;
                
                case SDL_KEYDOWN:
                    {
                        //First, we handle keys that display a message (tw related stuff)
                        char tmp[50];
                        switch (event.key.keysym.sym) {
                            case SDLK_PERIOD://Increase time speed
                                updates_per_frame*=2;
                                sprintf(tmp, "Timewarp: %dx", updates_per_frame/10);
                                break;
                            case SDLK_COMMA://Decrease time speed, up to 0
                                if (updates_per_frame>1) {
                                    updates_per_frame/=2;
                                    sprintf(tmp, "Timewarp: %dx", updates_per_frame/10);
                                }
                                break;
                            case SDLK_ESCAPE://Pause the game
                                sprintf(tmp, "Game %s", paused?"unpaused":"paused");
                                paused = !paused;
                                break;
                            default:
                                sprintf(tmp, " ");
                                break;
                        }
                        update_message(&m, tmp, SDL_GetTicks());
                        dprintf("Updates per frame: %d\n", updates_per_frame);
                    }
                    
                    {
                        switch (event.key.keysym.sym) {
                            case SDLK_RIGHT:
                                screencoord_shift(10, 0);
                                break;
                            
                            case SDLK_LEFT:
                                screencoord_shift(-10, 0);
                                break;
                            
                            case SDLK_UP:
                                screencoord_shift(0, 10);
                                break;
                            
                            case SDLK_DOWN:
                                screencoord_shift(0, -10);
                                
                            default:
                                break;
                        }
                    }
                    break;//We're still in a switch statement here.
            }
        }

        //Update the solar system by `updates_per_frame` timesteps
        vdprintf("Left event poll\n"); //Only update if we're not paused
        for (int i=0; i<updates_per_frame*!paused; i++) {
            cbody_update(system, ONE_HOUR);
            counter++;
        }

        //Move each sprite to its updated position
        for (int i=0; i<disp_system->len; i++) {
            vdprintf("Moving sprite %d\n", i);
            psprite_update(sprite+i);
            vdprintf("The actual coordinates of body %d are (%f, %f)\n", i, body[i].pos.x, body[i].pos.y);
            vdprintf("Its screen coordinates are (%f, %f)\n", sprite[i].screenpos.x, sprite[i].screenpos.y);
        }

        //clear the screen
        SDL_SetRenderDrawColor(components.renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(components.renderer);

        //Render each planet dot
        for (int i=0; i<disp_system->len; i++) {
            psprite_render(sprite+i, components.renderer);
            vdprintf("rendering body %s at screencoord (%f, %f)\n", (sprite+i)->rootbody->name, (sprite+i)->screenpos.x, (sprite+i)->screenpos.y);
        }

        //Get the mouse position, and render labels for any nearby dots
        int x, y;
        SDL_GetMouseState(&x, &y);
        render_labels(disp_system, (Coordinate){x, y}, components.renderer);

        //Render the message, if it exists
        render_message(&m, SDL_GetTicks());

        //Update the screen
        SDL_RenderPresent(components.renderer);

        //Pause to stay under MAX_FPS
        if (get_time(&framecontrol) < 1000/MAX_FPS) {
            SDL_Delay((1000/MAX_FPS) - (uint32_t)get_time(&framecontrol));
        }

        //Send a log message every orbit of the earth
        if (counter%365==0) {
            printf("Starting earth year %d.\n", counter/365);
        }
    }
    for (int i=0; i<disp_system->len; i++) {
        free(disp_system->data[i].texture);
        disp_system->data[i].texture = NULL;

        free(disp_system->data[i].label);
        disp_system->data[i].label = NULL;
    }
    free_darray_PSprite(disp_system);
    disp_system = NULL;

    
err://We jump here if there's an error, but passing here DOES NOT mean an error occured.
    
    closegame(components);
    return status;
}
