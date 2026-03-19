#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;

#define LOAD  0x01
#define STORE 0x02
#define ADD   0x03
#define SUB   0x04
#define MOV   0x05
#define CMP   0x06
#define JMP   0x07
#define JZ    0x08
#define JNZ   0x09
#define HALT  0x0A

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc];
    *a = mem[pc + 1];
    *b = mem[pc + 2];
    pc += 3;
}

void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case LOAD:  reg[a] = mem[b]; break;
        case STORE: mem[b] = reg[a]; break;
        case ADD:   reg[a] = reg[a] + reg[b]; break;
        case SUB:   reg[a] = reg[a] - reg[b]; break;
        case MOV:   reg[a] = b; break;
        case CMP:   zf = (reg[a] == reg[b]) ? 1 : 0; break;
        case JMP:   pc = a; break;
        case JZ:    if (zf) pc = a; break;
        case JNZ:   if (!zf) pc = a; break;
        case HALT:  running = 0; break;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nomes[] = {"", "LOAD", "STORE", "ADD", "SUB", "MOV", "CMP", "JMP", "JZ", "JNZ", "HALT"};
    printf("Ciclo %d: %-5s %d, %d | R0=%3d R1=%3d R2=%3d R3=%3d | PC=%3d ZF=%d\n",
           ciclo, (op <= 10) ? nomes[op] : "???", a, b, reg[0], reg[1], reg[2], reg[3], pc, zf);
}

int main() {
    uint8_t dados[] = {34, 12, 56, 3, 78, 45, 9, 67};
    
    for(int i = 0; i < 8; i++) mem[0x10 + i] = dados[i];

    int p = 0;
    
    mem[p++] = LOAD;  mem[p++] = 0; mem[p++] = 0x10;
    mem[p++] = MOV;   mem[p++] = 2; mem[p++] = 0x11;
    mem[p++] = MOV;   mem[p++] = 3; mem[p++] = 1;

    int loop_start = p;
    mem[p++] = LOAD;  mem[p++] = 1; mem[p++] = 0;
    p = 0;
    mem[p++] = LOAD; mem[p++] = 0; mem[p++] = 0x10;
    mem[p++] = LOAD; mem[p++] = 1; mem[p++] = 0x11;
    mem[p++] = CMP;  mem[p++] = 0; mem[p++] = 1;
    mem[p++] = MOV;  mem[p++] = 0; mem[p++] = 12;

    mem[p++] = MOV;  mem[p++] = 0; mem[p++] = 3;
    mem[p++] = STORE; mem[p++] = 0; mem[p++] = 0x20;
    mem[p++] = HALT; mem[p++] = 0; mem[p++] = 0;

    printf("Iniciando Simulador MiniCPU - Desafio Grupo 5\n");
    while (running && pc < 256) {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }

    printf("\nResultado Final em 0x20: %d\n", mem[0x20]);
    return 0;
}