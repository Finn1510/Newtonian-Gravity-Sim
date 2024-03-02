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
    sim.celestialBodies.push_back(std::make_shared<Planet>(500, center + Vector2(0, -300), Vector2(-100, 0), planetColor1, 12));
    
    const SDL_Color planetColor2 = {161, 119, 86, 255};
    sim.celestialBodies.push_back(std::make_shared<Planet>(400, center + Vector2(0, 100), Vector2(200, 0), planetColor2, 10));
    
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