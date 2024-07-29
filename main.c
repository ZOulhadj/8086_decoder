//
// This program is for learning assembly and is intended to read an ASM
// instruction stream for the Intel 8086 instruction set and decode it.
//
//
// Intel 8086 Manual:
// https://edge.edx.org/c4x/BITSPilani/EEE231/asset/8086_family_Users_Manual_1_.pdf
//
// ax, bx
// x means entire register
// h means high part
// l means low part
//
// al means low part of a register
// ah means high part of a register
// ax means whole part of register
//
// 6 bits   Opcode (Instruction code)
// 1 bit    D - if 1 REG is destination, if 0 then REG is source
// 1 bit    W - if 0 then 8 bit registers or 1 if 16 registers

// 2 bits   MOD (Register mode) register to register or register to memory
// 3 bits   REG (Register operand) a register
// 3 bits   R/M a register or memory address
//

// MOD encodings
//
// 00    Memory mode
// 01    Memory mode 8 bit
// 10    Memory mode 16 bit
// 11    Register mode


// REG encodings
//       W = 0     W = 1
// 000     AL       AX
// 001     CL       CX
// 010     DL       DX
// 011     BL       BX
// 100     AH       SP
// 101     CH       BP
// 110     DH       SI
// 111     BH       DI

// mov    D W       cx bx
// 100010 1 1 | 11 001 011



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef int32_t s32;
typedef uint8_t u8;
typedef size_t usize;

// Register look up tables

const char* byte_registers[] = {
    "al", "cl", "dl", "bl",
    "ah", "ch", "dh", "bh"
};

const char* word_registers[] = {
    "ax", "cx", "dx", "bx",
    "sp", "bp", "si", "di"
};

int main(int argc, char** argv)
{
    // @TODO: Use argv to get path to asm stream instead of hard coding it.

    FILE* file = fopen("listing_0037_single_register_mov", "rb");
    if (!file) {
        fprintf(stderr, "Failed to open assembly ASM.\n");
        return -1;
    }

    u8* buffer = NULL;
    usize buffer_size = 0;

    fseek(file, 0, SEEK_END);
    usize file_size = ftell(file);

    buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Failed to malloc ASM buffer.\n");
        fclose(file);

        return -1;
    }
    buffer_size = file_size;

    fseek(file, 0, SEEK_SET);
    fread(buffer, 1, buffer_size, file);

    printf("ASM (%d bytes): \n", buffer_size);
    for (s32 i = 0; i < buffer_size; i += 2) {
        u8 byte1 = buffer[i];
        u8 byte2 = buffer[i + 1];

        // @TODO: Do bit stuff to get the data we want.
        u8 op = 0;
        u8 d = 0;
        u8 word = byte1 & (1 << 7);
        u8 reg = (byte2 >> 3) & 0x07;
        u8 rm = byte2 & 0x07;

        const char* op_name = "mov";
        const char* operand1;
        const char* operand2;
        if (word == 0) {
            operand1 = byte_registers[reg];
            operand2 = byte_registers[rm];
        } else {
            operand1 = word_registers[reg];
            operand2 = word_registers[rm];
        }

        printf("%s %s, %s\n", op_name, operand1, operand2);
    }




    free(buffer);
    fclose(file);

    return 0;
}
