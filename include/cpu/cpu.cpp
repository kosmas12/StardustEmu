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
#include "cpu.h"
#include <SDL2/SDL.h>

// CPU constructor. Initializes in the state the boot ROM leaves the CPU in
CPU::CPU() {
    this->writeAF(0x01B0);
    this->writeBC(0x0013);
    this->writeDE(0x00D8);
    this->writeHL(0x014D);
    this->SP = 0xFFFE;
    this->PC = 0x100;
    this->curFrameCycleCount = 0;
}

void CPU::executeNextOP(Memory *memory) {

    uint8_t curByte = memory->fetchByte(this->PC);

    if (curByte != 0xCB) {
        // Execute regular instruction
    }
    else {
        // Execute CB-prefixed instruction
    }

}

void CPU::run(Memory *memory, bool *exit, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, SDL_GameController *controller) {
    const int cyclesPerFrame = 69905;
    curFrameCycleCount = 0;
    while (curFrameCycleCount < cyclesPerFrame) {
        this->executeNextOP(memory);
        /*
        this->UpdateTimers(curFrameCycleCount);
        this->UpdateGraphics(curFrameCycleCount);
        this->DoInterrupts();
        */
        ++curFrameCycleCount;
    }
    // RenderScreen();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *exit = true;
                return;
        }
    }
}
