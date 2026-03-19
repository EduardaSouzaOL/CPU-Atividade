#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;
int array[8] = {34, 12, 56, 3, 78, 45, 9, 67};


void fetch(uint8_t *op, uint8_t *a, uint8_t *b)
{
    *op = mem[pc];
    *a = mem[pc + 1];
    *b = mem[pc + 2];
    pc += 3;
}
void decode_execute(uint8_t op, uint8_t a, uint8_t b)
{
    switch (op)
    {
    case 0x01:
        reg[a] = mem[b];
        break;
    case 0x02:
        mem[b] = reg[a];
        break;
    case 0x03:
        reg[a] = reg[a] + reg[b];
        break;
    case 0x04:
        reg[a] = reg[a] - reg[b];
        break;
    case 0x05:
        reg[a] = b;
        break;
    case 0x06:
        zf = (reg[a] == reg[b]) ? 1 : 0;
        break;
    case 0x07:
        pc = a;
        break;
    case 0x08:
        if (zf)
            pc = a;
        break;
    case 0x09:
        if (!zf)
            pc = a;
        break;
    case 0x0A:
        running = 0;
        break;
    case 0x0B:
        zf = (reg[a] < reg[b]) ? 1 : 0;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b)
{
    const char *nomes[] = {"", "LOAD", "STORE", "ADD",
                           "SUB", "MOV", "CMP", "JMP", "JZ", "JNZ", "HALT"};
    printf("Ciclo %d: %-5s %d,%d | R0=%3d R1=%3d"
           " R2=%3d R3=%3d | PC=%3d ZF=%d\n",
           ciclo, nomes[op], a, b,
           reg[0], reg[1], reg[2], reg[3], pc, zf);
}

void func_min() {
    // for (int i = 0; i < 24; i + 3) {
    //     mem[i] = 0x02; mem[] = 0x10; mem[0x02] = array[0];
    // }
    mem[0x00] = 0x02; mem[0x01] = 0x10; mem[0x02] = array[0]; /* STORE R0, array[0] */
    mem[0x03] = 0x02; mem[0x04] = 0x11; mem[0x05] = array[1]; /* STORE R0, array[1] */
    mem[0x06] = 0x02; mem[0x07] = 0x12; mem[0x08] = array[2]; /* STORE R0, array[2] */
    mem[0x09] = 0x02; mem[0x0A] = 0x13; mem[0x0B] = array[3]; /* STORE R0, array[3] */
    mem[0x0C] = 0x02; mem[0x0D] = 0x14; mem[0x0E] = array[4]; /* STORE R0, array[4] */
    mem[0x0F] = 0x02; mem[0x10] = 0x15; mem[0x11] = array[5]; /* STORE R0, array[5] */
    mem[0x12] = 0x02; mem[0x13] = 0x16; mem[0x14] = array[6]; /* STORE R0, array[6] */
    mem[0x15] = 0x02; mem[0x16] = 0x17; mem[0x18] = array[7]; /* STORE R0, array[7] */

    mem[0x19] = 0x01; mem[0x1A] = 0x10; mem[0x1B] = array[0];
    mem[0x1C] = 0x01; mem[0x1D] = 0x10; mem[0x1E] = array[1];


    mem[0x00] = 0x05; mem[0x01] = 0x00; mem[0x02] = 0x0A; /* MOV R0, 10 */
    mem[0x03] = 0x05; mem[0x04] = 0x01; mem[0x05] = 0x01; /* MOV R1, 1 */
    mem[0x06] = 0x03; mem[0x07] = 0x00; mem[0x08] = 0x01; /* ADD R0, R1 */
    mem[0x09] = 0x0A; mem[0x0A] = 0x00; mem[0x0B] = 0x00; /* HALT */
}

int main()
{
    while (running && pc < 256)
    {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        for (int i = 0; i < 8; i++) {
            decode_execute(0x02, 0x10 + i, array[i]);
        }
        for (int i = 0; i < 2; i++) {
            decode_execute(0x01, 0x10 + i, array[i]);
        }
        decode_execute(0x04, 0x10, 0x11);
        if (0x10 < 0)
        trace(op, a, b);
    }
    return 0;
}