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

void CPU::writeAF(uint16_t value) {
    this->regA = (uint8_t)((value & 0xFF00) >> 8);
    this->regF = (uint8_t)(value & 0xFF);
}

void CPU::writeBC(uint16_t value) {
    this->regB = (uint8_t)((value & 0xFF00) >> 8);
    this->regC = (uint8_t)(value & 0xFF);
}

void CPU::writeDE(uint16_t value) {
    this->regD = (uint8_t)((value & 0xFF00) >> 8);
    this->regE = (uint8_t)(value & 0xFF);
}

void CPU::writeHL(uint16_t value) {
    this->regH = (uint8_t)((value & 0xFF00) >> 8);
    this->regL = (uint8_t)(value & 0xFF);
}

uint16_t CPU::readAF() {
    return (uint16_t)((this->regA << 8) | this->regF);
}

uint16_t CPU::readBC() {
    return (uint16_t)((this->regB << 8) | this->regC);
}

uint16_t CPU::readDE() {
    return (uint16_t)((this->regD << 8) | this->regE);
}

uint16_t CPU::readHL() {
    return (uint16_t)((this->regH << 8) | this->regL);
}