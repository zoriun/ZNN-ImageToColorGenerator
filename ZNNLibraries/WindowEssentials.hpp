// ZNN-ImageToColorGenerator
// Copyright (C) 2025 zoriun
// 
// Licensed under the ZNN-ImageToColorGenerator License v1.0 (February 2025):
// - You may use, copy, modify, and redistribute this software for non-commercial purposes.
// - You must provide visible credit to the original author:
//   Original project by zoriun — https://github.com/zoriun/ZNN-ImageToColorGenerator
// - You may not sell this software or use it in products/services for monetary gain.
// 
// Full license text is available in the LICENSE file included with this source code.

#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

float lerp(float a, float b, float t){
    return a + t * (b - a);
}

struct window
{
    int w, h;
    bool running = false;
    SDL_Window* windowOBJ;
    SDL_Renderer* rendererOBJ;
    window(const char* title, int w, int h);
    void PollEvents(SDL_Event* event);
    void CleanUp();
};

struct Rectangle
{
    SDL_FRect rectangleOBJ;
    Rectangle(float nx, float ny, float nw, float nh);
    void render(SDL_Renderer* renderer, int r, int g, int b);
};

struct TextureButton
{
    float x, y, w, h;
    SDL_Texture* ButtonTexture;
    TextureButton(float nx, float ny, float nw, float nh, SDL_Texture* DefiningTexture);
    void render(SDL_Renderer* ButtonRenderer);
    bool MouseOverlap();
};



// window definitions

window::window(const char* title, int w, int h){
    windowOBJ = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL);
    rendererOBJ = SDL_CreateRenderer(windowOBJ, NULL);
    running = true;
}

void window::PollEvents(SDL_Event* event){
    if (event->type == SDL_EVENT_QUIT){
        running = false;
    }
}

void window::CleanUp(){
    SDL_DestroyWindow(windowOBJ);
    SDL_DestroyRenderer(rendererOBJ);
}


// Rectangle Definitions

Rectangle::Rectangle(float nx, float ny, float nw, float nh){
    rectangleOBJ = {nx,ny,nw,nh};
};

void Rectangle::render(SDL_Renderer* renderer, int r, int g, int b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderRect(renderer, &rectangleOBJ);
    SDL_RenderFillRect(renderer, &rectangleOBJ);
};

// TextureButton Definitions

TextureButton::TextureButton(float nx, float ny, float nw, float nh, SDL_Texture* DefiningTexture){
    ButtonTexture = DefiningTexture;
    x = nx; y = ny; w = nw; h = nh;
}

void TextureButton::render(SDL_Renderer* ButtonRenderer){
    SDL_FRect ButtonRect = {x, y, w, h};
    SDL_RenderTexture(ButtonRenderer, ButtonTexture, NULL, &ButtonRect);
}

bool TextureButton::MouseOverlap(){
    float mx, my;
    SDL_GetMouseState(&mx, &my);

    if (mx >= x && mx <= x + w && my >= y && my <= y + h){
        return true;
    }

    return false;
}