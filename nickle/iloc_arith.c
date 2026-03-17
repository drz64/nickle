#include "iloc.h"
#include "cpu.h"
#include <inttypes.h>

static inline uint64_t shamt64(uint64_t x) { return x & 63u; }

void iloc_nop(cpu_t* cpu) { (void)cpu; }

void iloc_add(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] + cpu->regs[r2];
}

void iloc_sub(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] - cpu->regs[r2];
}

void iloc_mult(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] * cpu->regs[r2];
}

void iloc_div(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    uint64_t d = cpu->regs[r2];
    if (d == 0) nickle_trap(cpu, "division by zero");
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] / (int64_t)d);
}

void iloc_addI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] + imm;
}

void iloc_subI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] - imm;
}

void iloc_rsubI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = imm - cpu->regs[r1];
}

void iloc_multI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] * imm;
}

void iloc_divI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    if (imm == 0) nickle_trap(cpu, "division by zero");
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] / (int64_t)imm);
}

void iloc_rdivI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    uint64_t d = cpu->regs[r1];
    if (d == 0) nickle_trap(cpu, "division by zero");
    cpu->regs[r3] = (uint64_t)((int64_t)imm / (int64_t)d);
}

void iloc_lshift(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] << shamt64(cpu->regs[r2]);
}

void iloc_lshiftI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] << shamt64(imm);
}

void iloc_rshift(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] >> shamt64(cpu->regs[r2]));
}

void iloc_rshiftI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] >> shamt64(imm));
}

void iloc_and(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] & cpu->regs[r2];
}

void iloc_andI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] & imm;
}

void iloc_or(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] | cpu->regs[r2];
}

void iloc_orI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] | imm;
}

void iloc_xor(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] ^ cpu->regs[r2];
}

void iloc_xorI(cpu_t* cpu, int r1, uint64_t imm, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] ^ imm;
}
