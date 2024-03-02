#ifndef CELESTIALBODIES
#define CELESTIALBODIES

#include <array>
#include <SDL2/SDL.h>
#include <random>
#include "Vector2.hh"


class CelestialBody{
public:
    const double mass; //kg
    Vector2 position; //1 unit is 1m
    Vector2 velocity;

    CelestialBody(double mass, Vector2 position, Vector2 velocity) 
    : mass(mass), position(position), velocity(velocity) {}

    virtual void drawShape(SDL_Renderer* renderPtr) = 0;
};

class Planet : public CelestialBody{
private:
    const SDL_Color color;
    const int radius;
    
public:
    Planet(double mass, Vector2 position, Vector2 velocity, SDL_Color color, int radius) 
    : CelestialBody(mass, position, velocity), color(color), radius(radius) {}

    virtual void drawShape(SDL_Renderer* renderPtr){ //Planets are basic circles
        SDL_SetRenderDrawColor(renderPtr, color.r, color.g, color.b, color.a);

        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    SDL_RenderDrawPoint(renderPtr, position.x() + x, position.y() + y);
                }
            }
        }
    }
};

class Sun : public CelestialBody{
private:
    const int radius;
    
    int getRandomOffset() {
        return rand() % 146; // Generates a random number between 0 and 146
    }
public:
    Sun(double mass, Vector2 position, Vector2 velocity, int radius) 
    : CelestialBody(mass, position, velocity), radius(radius) {}
    
    virtual void drawShape(SDL_Renderer* renderPtr){ //Sun colors flicker between yellow and orange
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    if(getRandomOffset() < 60) SDL_SetRenderDrawColor(renderPtr, 255, 110 + getRandomOffset(), 0, 255);
                    SDL_RenderDrawPoint(renderPtr, position.x() + x, position.y() + y);
                }
            }
        }
    }
};

#endif