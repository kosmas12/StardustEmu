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

void CPU::executeRegularInstruction(uint8_t byte, Memory *memory) {
    switch (byte) {
        // 0x00: NOP (Duration: 4 t cycles)
        case 0x00:
            this->curFrameCycleCount += 4;
            break;

        // 0x01: LD BC, u16 (Duration: 12 t cycles)
        case 0x01:
            this->ld16(REG_BC, memory);
            this->curFrameCycleCount += 12;
            break;

        // 0x02: LD memory[BC], A (Duration: 8 t cycles)
        case 0x02:
            memory->writeByte(readBC(), this->regA);
            this->curFrameCycleCount += 8;
            break;

        // 0x03: INC BC (Duration: 8 t cycles)
        case 0x03:
            this->writeBC(this->readBC() + 1);

            if (this->readBC() == 0) {
                this->setFlag(ZERO_FLAG, true);
            }
            this->setFlag(SUBTRACTION_FLAG, false);
            if ((this->readBC() & 0xF) == 0xF) {
                this->setFlag(HALF_CARRY_FLAG, true);
            }

            this->curFrameCycleCount += 8;
            break;

        // 0x04: INC B (Duration: 4 t cycles)
        case 0x04:
            this->regB++;

            if (this->regB == 0) {
                this->setFlag(ZERO_FLAG, true);
            }
            this->setFlag(SUBTRACTION_FLAG, false);
            if ((this->regB & 0xF) == 0xF) {
                this->setFlag(HALF_CARRY_FLAG, true);
            }

            this->curFrameCycleCount += 4;
            break;

        // 0x05: DEC B (Duration: 4 t cycles)
        case 0x05:
            this->regB--;

            if (this->regB == 0) {
                this->setFlag(ZERO_FLAG, true);
            }
            this->setFlag(SUBTRACTION_FLAG, true);
            if ((this->regB & 0xF) == 0x0) {
                this->setFlag(HALF_CARRY_FLAG, true);
            }

            this->curFrameCycleCount += 4;
            break;

        // 0x06: LD B, u8 (Duration: 8 t cycles)
        case 0x06:
            this->regB = memory->fetchByte(this->PC++);
            this->curFrameCycleCount += 8;
            break;

        // 0x07: RLC A (Duration: 4 t cycles)
        case 0x07:
            this->rlc(&this->regA);
            this->curFrameCycleCount += 4;
            break;

        // INC C (Duration: 4 t cycles)
        case 0x0C:
            this->regC++;

            if (this->regC == 0) {
                this->setFlag(ZERO_FLAG, true);
            }
            this->setFlag(SUBTRACTION_FLAG, false);
            if ((this->regC & 0xF) == 0xF) {
                this->setFlag(HALF_CARRY_FLAG, true);
            }

            this->curFrameCycleCount += 4;
            break;

        // 0x0E: LD C, u8 (Duration: 8 t cycles)
        case 0x0E:
            this->regC = memory->fetchByte(this->PC++);
            this->curFrameCycleCount += 8;
            break;

        // 0x11: LD DE, u16 (Duration: 12 t cycles)
        case 0x11:
            this->ld16(REG_DE, memory);
            this->curFrameCycleCount += 12;
            break;

        // 0x1A: LD A, (DE) (Duration: 8 t cycles)
        case 0x1A:
            this->regA = memory->fetchByte(this->readDE());
            this->curFrameCycleCount += 8;
            break;

        // 0x20: JR NZ, i8 (Duration: 12 t cycles if jump, 8 if not)
        case 0x20:
            // Need to move 1 more byte either way
            this->PC++;

            if (!this->getFlag(ZERO_FLAG)) {
                this->PC = memory->fetchByte(this->PC);
                this->curFrameCycleCount += 12;
            }
            else {
                this->curFrameCycleCount += 8;
            }
            break;

        // 0x21: LD HL, u16 (Duration: 12 t cycles)
        case 0x21:
            this->ld16(REG_HL, memory);
            this->curFrameCycleCount += 12;
            break;

        // 0x22: LD memory[HL], A and then increment HL (Duration: 8 t cycles)
        case 0x22:
            memory->writeByte(this->readHL(), this->regA);
            this->writeHL(this->readHL() + 1);
            this->curFrameCycleCount += 8;
            break;

        // 0x23: INC HL (Duration: 8 t cycles)
        case 0x23:
            this->writeHL(this->readHL() + 1);
            this->curFrameCycleCount += 8;
            break;

        // 0x31: LD SP, u16 (Duration: 12 t cycles)
        case 0x31:
            ld16(REG_SP, memory);
            this->curFrameCycleCount += 12;
            break;

        // 0x32: LD (HL), A and then decrement HL (Duration: 8 t cycles)
        case 0x32:
            memory->writeByte(this->readHL(), this->regA);
            this->writeHL(this->readHL() - 1);
            curFrameCycleCount += 8;
            break;

        // 0x0E: LD Α, u8 (Duration: 8 t cycles)
        case 0x3E:
            this->regA = memory->fetchByte(this->PC++);
            this->curFrameCycleCount += 8;
            break;

        // 0x4F: LD C, A (Duration: 4 t cycles)
        case 0x4F:
            this->regC = this->regA;
            this->curFrameCycleCount += 4;
            break;

        // 0x77: LD memory[HL], A (Duration: 8 t cycles)
        case 0x77:
            memory->writeByte(this->readHL(), this->regA);
            this->curFrameCycleCount += 8;
            break;

        // 0x7C: LD A, H (Duration: 4 t cycles)
        case 0x7C:
            this->regA = this->regH;
            curFrameCycleCount += 4;
            break;

        // 0xAF: XOR A, A (Duration: 4 t cycles)
        case 0xAF:
            this->regA ^= this->regA;

            if (this->regA == 0) {
                this->setFlag(ZERO_FLAG, true);
            }
            this->setFlag(SUBTRACTION_FLAG, false);
            this->setFlag(HALF_CARRY_FLAG, false);
            this->setFlag(CARRY_FLAG, false);

            this->curFrameCycleCount += 4;
            break;

        // 0xC5: PUSH BC (Duration: 16 t cycles)
        case 0xC5:
            this->pushToStack(memory, this->readBC());
            this->curFrameCycleCount += 16;
            break;

        // 0xC9: RET (Duration: 16 t cycles)
        case 0xC9:
            this->PC = popFromStack(memory);
            this->curFrameCycleCount += 16;
            break;

        // 0xCD: CALL u16 (Duration: 24 t cycles)
        case 0xCD:
            this->pushToStack(memory, this->PC + 2);
            this->ld16(REG_PC, memory);
            this->curFrameCycleCount += 24;
            break;

        // 0xE0: LD (FF00 + u8), A (Duration: 12 t cycles)
        case 0xE0:
            memory->writeByte((0xFF00 + memory->fetchByte(this->PC++)), this->regA);
            this->curFrameCycleCount += 12;
            break;

        // 0xE2: LD memory[0xFF00 + C], A (Duration: 8 t cycles)
        case 0xE2:
            memory->writeByte((0xFF00 + this->regC), this->regA);
            this->curFrameCycleCount += 8;
            break;
        default:
            printf("Unimplemented opcode 0x%02X at PC 0x%02X", byte, --this->PC);
            exit(2);
            break;
    }

}
