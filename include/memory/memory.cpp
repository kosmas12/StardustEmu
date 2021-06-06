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

Memory::Memory(char *filename) {

    std::ifstream rom(filename, std::ios::binary);

    /* The Game Boy supports addresses from 0x0000 to 0xFFFF so 65535 bytes (64KiB) */

    // Apply sizes
    this->memoryBus.resize(65535);

    // Initialize every byte to 0
    for (int i = 0; i < memoryBus.size(); ++i) {
        this->memoryBus[i] = 0;
    }

    auto cartridge = std::vector <unsigned char>(std::istreambuf_iterator<char>(rom), {});

    // No need to init the rest of the bytes to zero, this was done before
    int i = 0;
    while (cartridge[i]) {
        this->memoryBus[0x100 + i] = cartridge[i];
        ++i;
    }
}

uint8_t Memory::fetchByte(uint16_t address) {
    return this->memoryBus[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte) {
    this->memoryBus[address] = byte;
}
