//
// Created by kosmas on 12/6/21.
//

#ifndef STARDUSTEMU_PPU_H
#define STARDUSTEMU_PPU_H

#include <SDL2/SDL.h>
#include "../memory/memory.h"

class PPU {
public:
    PPU(SDL_Window *window);
    void renderGraphics(int cycles, Memory *memory);
    void updateScreen();

private:
    SDL_Window *window;
    SDL_Surface *windowSurface;
    SDL_Surface *screenSurface;
    SDL_Color colors[4]; // The Game Boy (DMG) screen supports 4 shades of green
    void clearScreen();
    SDL_Color makeColor(const uint8_t byte1, const uint8_t byte2, int bit);
    bool getBit(uint8_t value, uint8_t bitToGet);
    void setBit(uint8_t *value, uint8_t bitToSet, bool set);
};


#endif //STARDUSTEMU_PPU_H
