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

void CPU::executeCBPrefixedInstruction(Memory *memory) {
    uint8_t instruction = memory->fetchByte(this->PC++);

    switch (instruction) {
        // 0x11 (CB Prefixed): RL C (Duration: 8 t cycles)
        case 0x11:
            this->rl(&this->regC);
            this->curFrameCycleCount += 8;
            break;

        // 0x7C (CB Prefixed): Test bit 7 of register H (Duration: 8 t cycles)
        case 0x7C:
            if(!this->getBit(this->regH, 7)) {
                this->setFlag(ZERO_FLAG, true);
            }
            else {
                this->setFlag(ZERO_FLAG, false);
            }
            this->setFlag(SUBTRACTION_FLAG, false);
            this->setFlag(HALF_CARRY_FLAG, true);

            this->curFrameCycleCount += 8;
            break;
        default:
            printf("Unimplemented CB-prefixed opcode 0x%02X", instruction);
            exit(2);
            break;
    }
}

