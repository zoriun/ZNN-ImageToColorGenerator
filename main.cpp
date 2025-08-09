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

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "ZNNLibraries/WindowEssentials.hpp"
#include "ZNNLibraries/ZNN.hpp"
#include <random>
#include <algorithm>

ZNNColorGenerationModelElythra CGMElythra;

std::vector<double> RandomShade1 = CGMElythra.GenerateColorFromTraining();
std::vector<double> RandomShade2 = CGMElythra.GenerateColorFromTraining();
std::vector<double> RandomShade3 = CGMElythra.GenerateColorFromTraining();
std::vector<double> RandomShade4 = CGMElythra.GenerateColorFromTraining();

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> distrib(0.0, 1.0);

SDL_Texture* ActiveChosenFileTexture;
SDL_Surface* ActiveChosenFileSurface;
SDL_Renderer* GlobalRenderer;

bool RPriority = true;
bool GPriority = true;
bool BPriority = true;

float SIZE_SCALE = 0.2;

void FILEINITFORMODEL(){
    Uint64 TotalR = 0, TotalG = 0, TotalB = 0;
    int w, h;

    std::vector<double> TrainingData;
    std::vector<double> TrainingBias;

    w = ActiveChosenFileSurface->w;
    h = ActiveChosenFileSurface->h;

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            Uint8 CR, CG, CB, CA;
            SDL_ReadSurfacePixel(ActiveChosenFileSurface, x, y, &CR, &CG, &CB, &CA);
            TotalR += CR;
            TotalG += CG;
            TotalB += CB;
        }
    }

    TotalR /= (w*h);
    TotalG /= (w*h);
    TotalB /= (w*h);

    std::cout << (float)TotalR/255 << std::endl;
    std::cout << (float)TotalG/255 << std::endl;
    std::cout << (float)TotalB/255 << std::endl;

    double RBias = (float)TotalR/255;
    double GBias = (float)TotalG/255;
    double BBias = (float)TotalB/255;

    double ROffset = RBias;
    double GOffset = GBias;
    double BOffset = BBias;

    if (RPriority == true){
        ROffset = RBias;
    }else if (RPriority == false){
        ROffset = 0;
        RBias = 0.9;
    }

    if (GPriority == true){
        GOffset = GBias;
    }else if (GPriority == false){
        GOffset = 0;
        GBias = 0.9;
    }

    if (BPriority == true){
        BOffset = BBias;
    }else if (BPriority == false){
        BOffset = 0;
        BBias = 0.9;
    }

    std::uniform_real_distribution<double> JitterRNG(-0.2, 0.2);

    for (int i = 0; i <= 100; i++){
        TrainingData.push_back(std::clamp(RBias + JitterRNG(gen), 0.0, 1.0));
        TrainingData.push_back(std::clamp(GBias + JitterRNG(gen), 0.0, 1.0));
        TrainingData.push_back(std::clamp(BBias + JitterRNG(gen), 0.0, 1.0));

        TrainingBias.push_back(std::clamp(RBias + JitterRNG(gen), 0.0, 1.0));
        TrainingBias.push_back(std::clamp(GBias + JitterRNG(gen), 0.0, 1.0));
        TrainingBias.push_back(std::clamp(BBias + JitterRNG(gen), 0.0, 1.0));
    }

    CGMElythra.TrainZNN(TrainingBias, TrainingData);

    RandomShade1 = CGMElythra.GenerateColorFromTraining();
    RandomShade2 = CGMElythra.GenerateColorFromTraining();
    RandomShade3 = CGMElythra.GenerateColorFromTraining();
    RandomShade4 = CGMElythra.GenerateColorFromTraining();
}

void FileOpenContext(void* UserData, const char* const Files[], int FileAmount){
    if (Files[0] != NULL){
        std::cout << Files[0] << std::endl;
        ActiveChosenFileTexture = IMG_LoadTexture(GlobalRenderer, Files[0]);
        ActiveChosenFileSurface = IMG_Load(Files[0]);
        FILEINITFORMODEL();
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    window MainWindow("ImageToColorGenerator", 500, 450);

    GlobalRenderer = MainWindow.rendererOBJ;

    Rectangle ColorSuggestionOne(300, 50, 50, 50);
    Rectangle ColorSuggestionTwo(300, 150, 50, 50);
    Rectangle ColorSuggestionThree(300, 250, 50, 50);
    Rectangle ColorSuggestionFour(300, 350, 50, 50);

    SDL_Texture* AddButtonTexture = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/AddSymbol.png");
    SDL_Texture* RActive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/RActive.png");
    SDL_Texture* RInactive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/RInactive.png");

    SDL_Texture* GActive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/GActive.png");
    SDL_Texture* GInactive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/GInactive.png");

    SDL_Texture* BActive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/BActive.png");
    SDL_Texture* BInactive = IMG_LoadTexture(MainWindow.rendererOBJ, "Textures/BInactive.png");

    TextureButton AddButton(20, 400, 32, 32, AddButtonTexture);

    TextureButton RChannelButton(10, 10, 18, 18, RInactive);
    TextureButton GChannelButton(46, 10, 18, 18, GInactive);
    TextureButton BChannelButton(46+(18*2), 10, 18, 18, BInactive);

    while (MainWindow.running == true)
    {
        SDL_SetRenderDrawColor(MainWindow.rendererOBJ, 255,255,255,255);
        SDL_RenderClear(MainWindow.rendererOBJ);

        ColorSuggestionOne.render(MainWindow.rendererOBJ, RandomShade1[0]*255, RandomShade1[1]*255, RandomShade1[2]*255);
        ColorSuggestionTwo.render(MainWindow.rendererOBJ, RandomShade2[0]*255, RandomShade2[1]*255, RandomShade2[2]*255);
        ColorSuggestionThree.render(MainWindow.rendererOBJ, RandomShade3[0]*255, RandomShade3[1]*255, RandomShade3[2]*255);
        ColorSuggestionFour.render(MainWindow.rendererOBJ, RandomShade4[0]*255, RandomShade4[1]*255, RandomShade4[2]*255);

        AddButton.render(MainWindow.rendererOBJ);

        if (ActiveChosenFileTexture != NULL){
            SDL_FRect ACFTRect = {(float)100-(ActiveChosenFileTexture->w*SIZE_SCALE)/4, (float)225-((ActiveChosenFileTexture->h*SIZE_SCALE)/2), (float)ActiveChosenFileTexture->w*SIZE_SCALE, (float)ActiveChosenFileTexture->h*SIZE_SCALE};
            SDL_RenderTexture(MainWindow.rendererOBJ, ActiveChosenFileTexture, NULL, &ACFTRect);
        }

        RChannelButton.render(MainWindow.rendererOBJ);
        GChannelButton.render(MainWindow.rendererOBJ);
        BChannelButton.render(MainWindow.rendererOBJ);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            MainWindow.PollEvents(&event);

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

                if (AddButton.MouseOverlap() == true){
                    SDL_ShowOpenFileDialog(FileOpenContext, NULL, MainWindow.windowOBJ, NULL, 0, NULL, false);
                }

                if (RChannelButton.MouseOverlap() == true) {
                    
                    if (RPriority == true){
                        RPriority = false;
                        RChannelButton.ButtonTexture = RActive;
                    } else {
                        RPriority = true;
                        RChannelButton.ButtonTexture = RInactive;
                    }

                }

                if (GChannelButton.MouseOverlap() == true) {
                    
                    if (GPriority == true){
                        GPriority = false;
                        GChannelButton.ButtonTexture = GActive;
                    } else {
                        GPriority = true;
                        GChannelButton.ButtonTexture = GInactive;
                    }

                }

                if (BChannelButton.MouseOverlap() == true) {

                    if (BPriority == true){
                        BPriority = false;
                        BChannelButton.ButtonTexture = BActive;
                    } else {
                        BPriority = true;
                        BChannelButton.ButtonTexture = BInactive;
                    }  

                }

            }
        }
        
        SDL_RenderPresent(MainWindow.rendererOBJ);
    }
    
    MainWindow.CleanUp();
    SDL_Quit();
};