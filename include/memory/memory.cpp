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

Memory::Memory(char *filename, bool bootRom, std::string bootRomName) {

    std::ifstream rom(filename, std::ios::binary);
    std::ifstream bootCode(bootRomName, std::ios::binary);

    /* The Game Boy supports addresses from 0x0000 to 0xFFFF so 65536 bytes (64KiB) */

    // Apply sizes
    this->memoryBus.resize(65536);
    this->cartridge.resize(32768);

    // Initialize every byte to 0
    for (int i = 0; i < memoryBus.size(); ++i) {
        this->memoryBus[i] = 0;
    }

    int i;

    if (bootRom) {
        this->bootRomGiven = true;
        // Boot ROM is 256 bytes
        auto bootCodeBytes = std::vector <unsigned char>(std::istreambuf_iterator<char>(bootCode), {});
        for (i = 0; i < 256; ++i) {
            this->memoryBus[i] = bootCodeBytes[i];
        }
    }

    // Reset byte counter to load cartridge
    i = 0;

    auto cartridgeBytes = std::vector <unsigned char>(std::istreambuf_iterator<char>(rom), {});

    while (i < 32 * 1024) {
        if (cartridgeBytes[i]) {
            this->cartridge[i] = cartridgeBytes[i];
        }
        else {
            this->memoryBus[0x100 + i] = 0;
        }
        ++i;
    }
}

uint8_t Memory::fetchByte(uint16_t address) {
    if (address == 0xFF44) {
        return 0x90;
    }

    if (address < 0x100) {
        return memoryBus[address];
    }

    if (address < 0x4000) {
        return cartridge[address];
    }

    return this->memoryBus[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte) {
    this->memoryBus[address] = byte;
}
