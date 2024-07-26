#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef int32_t s32;
typedef uint8_t u8;
typedef size_t usize;

int main(int argc, char** argv)
{
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
    for (s32 i = 0; i < buffer_size; ++i) {

        // @TODO: Decode opcodes
        // 6 bits   Opcode (Instruction code)
        // 1 bit    D (Direction is to register/from register)
        // 1 bit    W (Word (1) / Byte(0) operation)

        // 2 bits   MOD (Register mode)
        // 3 bits   REG (Register operand)
        // 3 bits   R/M


        printf("%b ", buffer[i]);
    }
    printf("\n");



    free(buffer);
    fclose(file);

    return 0;
}
