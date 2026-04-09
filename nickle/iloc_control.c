#include "iloc.h"
#include "cpu.h"
#include "nickle.h"

void iloc_cmp_LT() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] < cpu->regs[r2] ? 1 : 0;
}
void iloc_cmp_LE() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] <= cpu->regs[r2] ? 1 : 0;
}
void iloc_cmp_EQ() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] == cpu->regs[r2] ? 1 : 0;
}
void iloc_cmp_GE() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] >= cpu->regs[r2] ? 1 : 0;
}
void iloc_cmp_GT() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] > cpu->regs[r2] ? 1 : 0;
}
void iloc_cmp_NE() {
    size_t r1 = r() ; size_t r2 = r() ; size_t r3 = r() ; 
    cpu->regs[r3] = cpu->regs[r1] != cpu->regs[r2] ? 1 : 0;
}

void iloc_ret() {
    size_t r1 = r() ; 
    iloc_goto(cpu->regs[r1]) ; 
}

void iloc_jsr() {
    int64_t imm = op() ; 
    cpu->regs[cpu->reg_count+R_RA_OFFSET] = cpu->pc;
    iloc_goto(imm) ; 
}

void iloc_jumpI() {
    int64_t imm = op() ; 
//Z NO MORE    cpu->regs[cpu->reg_count+R_RA_OFFSET] = PC;
    iloc_goto(imm) ; 
}

void iloc_cbr() {
    size_t r1 = r() ; 
    int64_t l2 = op() ; 
    int64_t l3 = op() ; 
    iloc_goto(cpu->regs[r1] ? l2 : l3) ; 
}
