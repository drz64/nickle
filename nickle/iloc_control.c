#include "iloc.h"
#include "cpu.h"

void iloc_cmp_LT(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = ((int64_t)cpu->regs[r1] < (int64_t)cpu->regs[r2]) ? 1 : 0;
}
void iloc_cmp_LE(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = ((int64_t)cpu->regs[r1] <= (int64_t)cpu->regs[r2]) ? 1 : 0;
}
void iloc_cmp_EQ(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = (cpu->regs[r1] == cpu->regs[r2]) ? 1 : 0;
}
void iloc_cmp_GE(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = ((int64_t)cpu->regs[r1] >= (int64_t)cpu->regs[r2]) ? 1 : 0;
}
void iloc_cmp_GT(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = ((int64_t)cpu->regs[r1] > (int64_t)cpu->regs[r2]) ? 1 : 0;
}
void iloc_cmp_NE(cpu_t* cpu, int r1, int r2, int r3) {
    if (cpu->halted) return;
    cpu->regs[r3] = (cpu->regs[r1] != cpu->regs[r2]) ? 1 : 0;
}
