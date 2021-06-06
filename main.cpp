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

int main(int argc, char *argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_GameController *controller;
    bool exitted = false;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER) < 0) {
        std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Stardust", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    // TODO: Make memory size user-selectable
    Memory memory(8192, argv[1]);
    CPU cpu;

    if(argc == 1) {
        std::cout << "No ROM was provided!" << std::endl;
        return 0;
    }

    while (!exitted) {
        cpu.run(&memory, &exitted, window, renderer, event, controller);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
