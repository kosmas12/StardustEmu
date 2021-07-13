/*
This file is part of StardustEmu - A FOSS Game Boy emulator
Copyright (C) 2021  Kosmas Raptis

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <iostream>
#include <SDL2/SDL.h>
#include "include/memory/memory.h"
#include "include/cpu/cpu.h"
#include "include/ppu/ppu.h"

int main(int argc, char *argv[]) {

    if(argc == 1) {
        std::cout << "No ROM was provided!" << std::endl;
        return 0;
    }

    bool bootRomGiven = false;
    std::string bootRomName = "";

    if (argc > 2) {
        bootRomGiven = true;
        bootRomName = argv[2];
    }
    Memory memory(argv[1], bootRomGiven, bootRomName);
    CPU cpu(bootRomGiven);

    SDL_Window *window;
    SDL_Event event;
    SDL_GameController *controller;
    bool exited = false;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Stardust Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    PPU ppu(window);

    while (!exited) {
        cpu.run(&memory, &exited, &ppu, event, controller);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
