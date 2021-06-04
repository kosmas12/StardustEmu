//
// Created by kosmas on 20/5/21.
//

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