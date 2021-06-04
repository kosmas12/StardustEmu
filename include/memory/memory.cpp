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

#include "memory.h"
#include <fstream>

Memory::Memory(int systemSize) {
    // Video RAM is always 8KiB, system RAM can be extended up to 32KiB

    // Apply sizes
    this->systemRAM.resize(systemSize);
    this->videoRAM.resize(8192);

    // Initialize every byte to 0
    for (int i = 0; i < systemSize; ++i) {
        this->systemRAM[i] = 0;
    }

    for (int i = 0; i < 8192; ++i) {
        this->videoRAM[i] = 0;
    }
}

void Memory::loadRom(char *filename) {
    std::ifstream rom(filename, std::ios::binary);

    // Resize cartridge RAM to fit the ROM, then load ROM
    this->cartridge.resize(rom.tellg());
    this->cartridge = std::vector <unsigned char>(std::istreambuf_iterator<char>(rom), {});
}

/* Fetch a byte from memory.
 * No memoryType - System RAM
 * memoryType is 1 - Video RAM
 * memoryType is 2 - Cartridge memory
*/
uint8_t Memory::fetchByte(uint16_t address, uint8_t memoryType) {
    if (memoryType == 1) {
        return this->videoRAM[address];
    }
    else if (memoryType == 2) {
        return this->cartridge[address];
    }
    return this->systemRAM[address];
}

/* Write a byte to memory.
 * No memoryType - System RAM
 * memoryType is 1 - Video RAM
*/
void Memory::writeByte(uint16_t address, uint8_t byte, uint8_t memoryType) {
    if (memoryType == 1) {
        this->videoRAM[address] = byte;
        return;
    }
    this->systemRAM[address] = byte;
}
