//
// Created by kosmas on 12/6/21.
//

#include "ppu.h"
#include <iostream>
#define LCDC_ADDRESS 0xFF40

PPU::PPU(SDL_Window *window) {
    this->window = window;
    this->windowSurface = SDL_GetWindowSurface(this->window);

    uint32_t RMask, GMask, BMask, AMask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    RMask = 0xFF000000;
    GMask = 0x00FF0000;
    BMask = 0x0000FF00;
    AMask = 0x000000FF;
#else
    RMask = 0x000000FF;
    GMask = 0x0000FF00;
    BMask = 0x00FF0000;
    AMask = 0xFF000000;
#endif

    // DMG Green color palette
    this->colors[0] = {0x0F, 0x38, 0x0F, 0xFF};
    this->colors[1] = {0x30, 0x62, 0x30, 0xFF};
    this->colors[2] = {0x8B, 0xAC, 0x0F, 0xFF};
    this->colors[3] = {0x9B, 0xBC, 0x0F, 0xFF};
    this->screenSurface = SDL_CreateRGBSurface(0, 160, 144, 32, RMask, GMask, BMask, AMask);
    if (!screenSurface) {
        std::cout << "Couldn't create screen surface! Reason: " << SDL_GetError() << std::endl;
    }
    clearScreen();
}

void PPU::clearScreen() {
    SDL_Color colorToUse = this->colors[3];
    SDL_FillRect(this->screenSurface, nullptr, SDL_MapRGB(this->screenSurface->format, colorToUse.r, colorToUse.g, colorToUse.b));
    SDL_BlitScaled(this->screenSurface, nullptr, this->windowSurface, nullptr);
    SDL_UpdateWindowSurface(window);
}

void PPU::updateScreen() {
    SDL_BlitScaled(this->screenSurface, nullptr, this->windowSurface, nullptr);
    SDL_UpdateWindowSurface(this->window);
}

void PPU::setBit(uint8_t *value, uint8_t bitToSet, bool set) {
    if (set) {
        *value |= 1UL << bitToSet;
    }
    else {
        *value &= ~(1UL << bitToSet);
    }
}

bool PPU::getBit(uint8_t value, uint8_t bitToGet) {
    return (value >> bitToGet) & 1U;
}

SDL_Color PPU::makeColor(const uint8_t byte1, const uint8_t byte2, int bit) {
    uint8_t color = byte1 >> bit & 0x1 | byte2 >> bit & 0x1 << 1;

    return this->colors[color];
}

void PPU::renderGraphics(int cycles, Memory *memory) {
    const int cyclesPerFrame = 69905;
    static int lastCycleCount;
    int cyclesToRun;

    if (cycles < lastCycleCount) {
        cyclesToRun = cyclesPerFrame - lastCycleCount + cycles;
    }
    else {
        cyclesToRun = cycles - lastCycleCount;
    }
    lastCycleCount = cycles;

}
