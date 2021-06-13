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
#include "../ppu/ppu.h"

#define REG_AF 0
#define REG_BC 1
#define REG_DE 2
#define REG_HL 3
#define REG_SP 4
#define REG_PC 5

#define CARRY_FLAG 4
#define HALF_CARRY_FLAG 5
#define SUBTRACTION_FLAG 6
#define ZERO_FLAG 7


class CPU {
public:
    CPU(bool bootRomGiven);
    void run(Memory *memory, bool *exit, PPU *ppu, SDL_Event event, SDL_GameController *controller);

private:

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

    uint8_t tempByte1;
    uint8_t tempByte2;
    uint16_t tempWord;

    void writeAF(uint16_t value);
    void writeBC(uint16_t value);
    void writeDE(uint16_t value);
    void writeHL(uint16_t value);
    uint16_t readAF();
    uint16_t readBC();
    uint16_t readDE();
    uint16_t readHL();
    void executeNext(Memory *memory);

    void executeRegularInstruction(uint8_t byte, Memory *memory);
    void ld16(uint16_t destination, Memory *memory);
    void rlc(uint8_t *byte);
    void setFlag(uint8_t flag, bool set);
    bool getFlag(uint8_t flag);
    void pushToStack(Memory *memory, uint16_t value);
    uint16_t popFromStack(Memory *memory);
    void executeCBPrefixedInstruction(Memory *memory);
    bool getBit(uint8_t value, uint8_t bitToGet);
    void setBit(uint8_t *value, uint8_t bitToSet, bool set);
    void rl(uint8_t *byte);
    void cp(uint8_t operand1, uint8_t operand2);
};

#endif //STARDUSTEMU_CPU_H
