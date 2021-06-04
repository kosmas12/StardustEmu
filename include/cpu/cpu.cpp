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
#include "../core/core.h"
#include <SDL2/SDL.h>

// CPU constructor. Initializes in state the boot ROM leaves the CPU in
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
    /* NOTE: The program counter is set to 0x100 once the boot ROM has ran, however,
    while on an actual Game Boy the cartridge does start at 0x100 of the main system bus,
    it's not the case with this emulator as it's not part of the main system bus and is instead its own
    thing (like all memory), so 0x100 will be subtracted from the cartridge fetch addresses (not
    changing the init value itself to 0 as things *might* depend on it (untested)) */

    uint8_t curByte = memory->fetchByte(this->PC - 0x100, 2);

    if (curByte != 0xCB) {
        // Execute regular instruction
    }
    else {
        // Execute CB-prefixed instruction
    }

}

void CPU::update(Memory *memory, bool *exit) {
    const int cyclesPerFrame = 69905;
    curFrameCycleCount = 0;
    while (curFrameCycleCount < cyclesPerFrame) {
        this->executeNextOP(memory);
        /*
        this->UpdateTimers(curFrameCycleCount);
        this->UpdateGraphics(curFrameCycleCount);
        this->DoInterupts();
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