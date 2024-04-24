#include <iostream>
#include "Renderer.hh"
#include "CelestialBodies.hh"
#include "Simulation.hh"

const int SCREEN_WIDTH = 1028;
const int SCREEN_HEIGHT = 720;


int main(int argc, char* args[]) {
    SDL_Event event; //event listener obj
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    Simulation sim;

    Vector2 center(SCREEN_WIDTH /2, SCREEN_HEIGHT /2);

    sim.celestialBodies.push_back(std::make_shared<Sun>(90000000000000000, center, Vector2(0,0), 25)); //add a sun at the center
    const SDL_Color planetColor1 = {129, 192, 160, 255};
    sim.celestialBodies.push_back(std::make_shared<Planet>(900, center - Vector2(SCREEN_WIDTH/4, 0), Vector2(0, -150/2), planetColor1, 12));
    
    const SDL_Color planetColor2 = {161, 119, 86, 255};
    sim.celestialBodies.push_back(std::make_shared<Planet>(400, center + Vector2(0, 300), Vector2(-135/2, 0), planetColor2, 10));
    
    const SDL_Color planetColor3 = {100, 119, 186, 255};
    sim.celestialBodies.push_back(std::make_shared<Planet>(250, center + Vector2(SCREEN_WIDTH/4, 0), Vector2(0, 60), planetColor3, 8));

    //Simulation loop
    while(true){
        sim.SimulationStep();
        renderer.drawSimulation(sim);
        
        //handle quit event
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) break;
    }

    return 0;
}