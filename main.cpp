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

#include <iostream>
#include "include/memory.h"

int main(int argc, char *argv[]) {

    // TODO: Make memory size user-selectable
    Memory memory(8192);

    if(argc == 1) {
        std::cout << "No ROM was provided!" << std::endl;
        return 0;
    }
    else {
        memory.loadRom(argv[1]);
    }

    return 0;
}
