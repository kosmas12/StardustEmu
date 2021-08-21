# StardustEmu
A FOSS emulator for the Game Boy. Written in C++

To compile:

```
mkdir build
cd build
cmake ..
make
```

A Game Boy boot ROM is not required, but it is planned to be able to provide it if you want to. Launch the emulator like so:

```./StardustEmu path/to/rom.gb path/to/optional/bootrom.gb```
