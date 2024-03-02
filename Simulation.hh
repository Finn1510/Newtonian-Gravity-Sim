#ifndef SIMULATION
#define SIMULATION

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <iostream>
#include "CelestialBodies.hh"

const double gravitationConstant = 6.67430e-11;

class Simulation{
private:
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    double calcGravityForce(const std::shared_ptr<CelestialBody> body, const std::shared_ptr<CelestialBody> other) const{
        return gravitationConstant * (body->mass * other->mass  / pow(body->position.distance(other->position), 2));
    }

public:
    std::vector<std::shared_ptr<CelestialBody>> celestialBodies;

    void SimulationStep(){
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;

        for(std::shared_ptr<CelestialBody> body : celestialBodies){
            for(std::shared_ptr<CelestialBody> other : celestialBodies){
                if(other == body) continue;

                Vector2 directionalGravityForce = body->position.unitDirection(other->position) * calcGravityForce(body, other);
                Vector2 directionalGravityAcceleration = directionalGravityForce / body->mass;

                body->velocity += directionalGravityAcceleration* deltaTime;
                
                body->position += body->velocity * deltaTime;  
            }
        }
    }
};

#endif