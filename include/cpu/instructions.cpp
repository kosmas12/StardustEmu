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

    uint8_t lowByte, highByte;

    lowByte = memory->fetchByte(this->PC++);
    highByte = memory->fetchByte(this->PC++);

    uint16_t value = (highByte << 8) | lowByte;

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
            break;
        case REG_PC:
            this->PC = value;
            break;
        default:
            break;
    }
}

void CPU::rl(uint8_t *byte) {
    bool prevCarry = this->getFlag(CARRY_FLAG);
    bool carry = (*byte & 0x80) >> 7;
    this->setFlag(CARRY_FLAG, carry);
    *byte = (*byte << 1) | prevCarry;
}

void CPU::rlc(uint8_t *byte) {
    bool carry = (*byte & 0x80) >> 7;
    this->setFlag(CARRY_FLAG, carry);
    *byte = (*byte << 1) | carry;
}

void CPU::cp(uint8_t operand1, uint8_t operand2) {
    if (operand1 == operand2) {
        this->setFlag(ZERO_FLAG, true);
    }

    this->setFlag(SUBTRACTION_FLAG, true);

    if ((operand1 & 0xF) < (operand2 & 0xF)) {
        this->setFlag(HALF_CARRY_FLAG, true);
    }

    if (operand1 < operand2) {
        this->setFlag(CARRY_FLAG, true);
    }

}
