//
// Created by kosmas on 12/6/21.
//

#include "ppu.h"

PPU::PPU(SDL_Window *window) {
    this->windowSurface = SDL_GetWindowSurface(window);

    uint32_t RMask, GMask, BMask, AMask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    RMask = 0xff000000;
    GMask = 0x00ff0000;
    BMask = 0x0000ff00;
    AMask = 0x000000ff;
#else
    RMask = 0x000000ff;
    GMask = 0x0000ff00;
    BMask = 0x00ff0000;
    AMask = 0xff000000;
#endif

    this->screenSurface = SDL_CreateRGBSurface(0, 160, 144, 8, RMask, GMask, BMask, AMask);
    SDL_FillRect(this->screenSurface, nullptr, 0);
    SDL_BlitScaled(this->screenSurface, nullptr, this->windowSurface, nullptr);
    SDL_UpdateWindowSurface(window);
}

void PPU::renderGraphics(int cycles, Memory *memory) {

}
