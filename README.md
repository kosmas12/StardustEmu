# The Stardust Emulator
The Stardust Emulator (StardustEmu or Stardust 
for short) is a FOSS Game Boy emulator written in C++
as a learning exercise. It tries to be as accurate
as possible while also keeping the code itself as
simple as possible.

# Building
Stardust only needs a C++ standard library which
comes with all C++ installations and additionally
needs just SDL2. After you install SDL2, you can use
the following commands to compile:

```
cmake -B build
cmake --build build
```

# Using the emulator

A Game Boy boot ROM is not required, however you 
can provide it if you want to. 
Launch the emulator like so:

```./StardustEmu path/to/gamerom.gb```

In case you can provide a boot ROM, launch like this:

```./StardustEmu path/to/gamerom.gb path/to/bootrom.gb```

# Project status

No proper PPU implementation is provided as 
of yet and the screen is just filled with bright 
green, however the CPU in its current state can 
succesfully make it past the boot ROM and into 
the provided game ROM :)