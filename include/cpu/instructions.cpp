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

void CPU::ld16(uint16_t destination, Memory *memory) {

    uint8_t byte1, byte2;

    byte1 = memory->fetchByte(this->PC++);
    byte2 = memory->fetchByte(this->PC++);

    uint16_t value = (byte1 << 8) | byte2;

    switch (destination) {
        case REG_AF:
            this->writeAF(value);
            break;
        case REG_BC:
            this->writeBC(value);
            break;
        case REG_DE:
            this->writeDE(value);
            break;
        case REG_HL:
            this->writeHL(value);
            break;
        case REG_SP:
            this->SP = value;
        default:
            break;
    }
}

void CPU::rlc(uint8_t *byte) {
    bool temp = (*byte & 0x80) >> 7;
    this->setFlag(CARRY_FLAG, temp);
    *byte = (*byte << 1) | temp;
}
