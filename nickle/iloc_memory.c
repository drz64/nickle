#include "iloc.h"
#include "cpu.h"

#include <string.h>

static inline uint64_t addr_reg(cpu_t* cpu, int r) { return cpu->regs[r]; }

void iloc_load(cpu_t* cpu, int r_src, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_src);
    nickle_check_mem(cpu, addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_loadAI(cpu_t* cpu, int r_base, uint64_t offset, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + offset;
    nickle_check_mem(cpu, addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_loadAO(cpu_t* cpu, int r_base, int r_off, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + addr_reg(cpu, r_off);
    nickle_check_mem(cpu, addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_cload(cpu_t* cpu, int r_src, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_src);
    nickle_check_mem(cpu, addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_cloadAI(cpu_t* cpu, int r_base, uint64_t offset, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + offset;
    nickle_check_mem(cpu, addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_cloadAO(cpu_t* cpu, int r_base, int r_off, int r_dst) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + addr_reg(cpu, r_off);
    nickle_check_mem(cpu, addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_loadI(cpu_t* cpu, uint64_t imm, int r_dst) {
    if (cpu->halted) return;
    cpu->regs[r_dst] = imm;
}

void iloc_store(cpu_t* cpu, int r_src, int r_addr) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_addr);
    nickle_check_mem(cpu, addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_storeAI(cpu_t* cpu, int r_src, int r_base, uint64_t offset) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + offset;
    nickle_check_mem(cpu, addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_storeAO(cpu_t* cpu, int r_src, int r_base, int r_off) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + addr_reg(cpu, r_off);
    nickle_check_mem(cpu, addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_cstore(cpu_t* cpu, int r_src, int r_addr) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_addr);
    nickle_check_mem(cpu, addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}

void iloc_cstoreAI(cpu_t* cpu, int r_src, int r_base, uint64_t offset) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + offset;
    nickle_check_mem(cpu, addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}

void iloc_cstoreAO(cpu_t* cpu, int r_src, int r_base, int r_off) {
    if (cpu->halted) return;
    uint64_t addr = addr_reg(cpu, r_base) + addr_reg(cpu, r_off);
    nickle_check_mem(cpu, addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}
