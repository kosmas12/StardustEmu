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

private:
    SDL_Surface *windowSurface;
    SDL_Surface *screenSurface;

};


#endif //STARDUSTEMU_PPU_H
