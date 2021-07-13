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

#ifndef STARDUSTEMU_MEMORY_H
#define STARDUSTEMU_MEMORY_H

#include <vector>
#include <cstdint>
#include <string>

class Memory {
public:
    Memory(char *filename, bool bootRom, std::string bootRomName);
    uint8_t fetchByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t byte);
    bool bootRomGiven = false;

private:
    std::vector <unsigned char> cartridge {};
    std::vector <unsigned char> memoryBus {};
};


#endif //STARDUSTEMU_MEMORY_H
