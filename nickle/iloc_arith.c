#include "iloc.h"
#include "cpu.h"
#include <inttypes.h>

static inline uint64_t shamt64(uint64_t x) { return x & 63u; }

void iloc_nop() { /* no-op */}

void iloc_add() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] + cpu->regs[r2];
}

void iloc_sub() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] - cpu->regs[r2];
}

void iloc_mult() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] * cpu->regs[r2];
}

void iloc_div() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    int64_t d = cpu->regs[r2];
    if (d == 0) nickle_trap("division by zero");
    cpu->regs[r3] = cpu->regs[r1] / d ;
}

void iloc_addI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] + imm;
}

void iloc_subI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] - imm;
}

void iloc_rsubI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = imm - cpu->regs[r1];
}

void iloc_multI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] * imm;
}

void iloc_divI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    if (imm == 0) nickle_trap("division by zero");
    cpu->regs[r3] = cpu->regs[r1] / imm;
}

void iloc_rdivI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    int64_t d = cpu->regs[r1];
    if (d == 0) nickle_trap("division by zero");
    cpu->regs[r3] = imm / d ;
}

void iloc_lshift() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] << shamt64(cpu->regs[r2]);
}

void iloc_lshiftI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    if (cpu->halted) return;
    cpu->regs[r3] = cpu->regs[r1] << shamt64(imm);
}

void iloc_rshift() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] >> shamt64(cpu->regs[r2]));
}

void iloc_rshiftI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = (uint64_t)((int64_t)cpu->regs[r1] >> shamt64(imm));
}

void iloc_and() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] & cpu->regs[r2];
}

void iloc_andI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] & imm;
}

void iloc_or() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] | cpu->regs[r2];
}

void iloc_orI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] | imm;
}

void iloc_xor() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] ^ cpu->regs[r2];
}

void iloc_xorI() {
    size_t r1 = r() ; int64_t imm = op() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] ^ imm;
}
