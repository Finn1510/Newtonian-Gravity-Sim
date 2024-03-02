#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include <iostream>
#include "Simulation.hh"
#include "CelestialBodies.hh"


class Renderer{
private:
    SDL_Window* window = nullptr;
public:
    SDL_Renderer* renderPtr = nullptr;

    Renderer(const int SCREEN_WIDTH, const int SCREEN_HEIGHT){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) { //initialize library
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        }

        window = SDL_CreateWindow("Newtonian Gravity Sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        renderPtr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderPtr == nullptr) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
    
    ~Renderer(){
        SDL_DestroyRenderer(renderPtr);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void drawSimulation(Simulation sim){
        //clear screen
        SDL_SetRenderDrawColor(renderPtr, 0, 0, 0, 255);
        SDL_RenderClear(renderPtr);

        //render each celestial body
        for(std::shared_ptr<CelestialBody> body : sim.celestialBodies){
            body->drawShape(renderPtr);
        }
        
        //submit frame
        SDL_RenderPresent(renderPtr);
    }

};

#endif