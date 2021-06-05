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

#ifndef STARDUSTEMU_CPU_H
#define STARDUSTEMU_CPU_H

#include <cstdint>
#include <SDL2/SDL.h>
#include "../memory/memory.h"

class CPU {
public:
    CPU();
    void run (Memory *memory, bool *exit, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, SDL_GameController *controller);

private:
    void writeAF(uint16_t value);
    void writeBC(uint16_t value);
    void writeDE(uint16_t value);
    void writeHL(uint16_t value);
    uint16_t readAF();
    uint16_t readBC();
    uint16_t readDE();
    uint16_t readHL();
    void executeNextOP(Memory *memory);

    uint8_t regA {};
    uint8_t regB {};
    uint8_t regC {};
    uint8_t regD {};
    uint8_t regE {};
    uint8_t regF {};
    uint8_t regH {};
    uint8_t regL {};
    uint16_t SP;
    uint16_t PC;
    int curFrameCycleCount;

};

#endif //STARDUSTEMU_CPU_H
