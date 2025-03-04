#include "config.h"
#include <iostream>
#include <string>

/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *tex = NULL;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  // custom init
  std::string operating_system = "Unknown";
  std::string test_msg = "Unknown";
#ifdef SELECTED_OS_TEXT
  operating_system = SELECTED_OS_TEXT;
#endif
#ifdef TEST_MSG
  test_msg = TEST_MSG;
#endif

  std::cout << "Hello developer! You are on " << operating_system << '\n';
  std::cout << "Which is an operating system for a " << test_msg << '\n';
  // custom init

  /* Create the window */
  if (!SDL_CreateWindowAndRenderer("Hello World", 1600, 900,
                                   SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  // load texture
  SDL_Surface *bmp = SDL_LoadBMP("./farmer.bmp");
  if (bmp == nullptr) {
    std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return SDL_APP_FAILURE;
  }

  tex = SDL_CreateTextureFromSurface(renderer, bmp);
  SDL_DestroySurface(bmp);

  if (tex == nullptr) {
    std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  std::string message = "Test ";
  int w = 0, h = 0;
  float x, y;
  const float scale = 4.0f;

  /* Center the message and scale it up */
  SDL_GetRenderOutputSize(renderer, &w, &h);
  SDL_SetRenderScale(renderer, scale, scale);
  x = ((w / scale) -
       SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message.c_str())) /
      2;
  y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

  /* Draw the message */
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDebugText(renderer, x * 0.5f, y * 0.5f, (message + "1").c_str());
  SDL_RenderDebugText(renderer, x * 1.5f, y * 0.5f, (message + "2").c_str());
  SDL_RenderDebugText(renderer, x * 0.5f, y * 1.5f, (message + "3").c_str());
  SDL_RenderDebugText(renderer, x * 1.5f, y * 1.5f, (message + "4").c_str());

  SDL_FRect texture_rect;
  static int farmer_pos = 1;
  farmer_pos = (farmer_pos + 1) % static_cast<int>(w / scale);
  texture_rect.x = farmer_pos; // the x coordinate
  texture_rect.y = 0;          // the y coordinate
  texture_rect.w = 50;         // the width of the texture
  texture_rect.h = 50;         // the height of the texture
  SDL_RenderTexture(renderer, tex, NULL, &texture_rect);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
