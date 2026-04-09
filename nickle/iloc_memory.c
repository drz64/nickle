#include "iloc.h"
#include "cpu.h"

#include <string.h>

void iloc_load() {
    size_t r_src = r() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_src];
    nickle_check_mem(addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_loadAI() {
    size_t r_base = r() ; 
    int64_t offset = op() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_base] + offset;
    nickle_check_mem(addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_loadAO() {
    size_t r_base = r() ; 
    int64_t r_off = r() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_base] + cpu->regs[r_off];
    nickle_check_mem(addr, 8);
    memcpy(&cpu->regs[r_dst], cpu->mem + addr, 8);
}

void iloc_cload() {
    size_t r_src = r() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_src];
    nickle_check_mem(addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_cloadAI() {
    size_t r_base = r() ; 
    int64_t offset = r() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_base] + offset;
    nickle_check_mem(addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_cloadAO() {
    size_t r_base = r() ; 
    size_t r_off = r() ; 
    size_t r_dst = r() ; 
    uint64_t addr = cpu->regs[r_base] + cpu->regs[r_off];
    nickle_check_mem(addr, 1);
    cpu->regs[r_dst] = (uint64_t)cpu->mem[addr];
}

void iloc_loadI() {
    int64_t imm = op() ; 
    size_t r_dst = r() ; 
    cpu->regs[r_dst] = imm;
}

void iloc_store() {
    size_t r_src = r() ; 
    size_t r_addr = r() ; 
    int64_t addr = cpu->regs[r_addr];
    nickle_check_mem(addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_storeAI() {
    size_t r_src = r() ; 
    size_t r_base = r() ; 
    int64_t offset = op() ; 
    uint64_t addr = cpu->regs[r_base] + offset;
    nickle_check_mem(addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_storeAO() {
    size_t r_src = r() ; 
    size_t r_base = r() ; 
    size_t r_off = r() ; 
    uint64_t addr = cpu->regs[r_base] + cpu->regs[r_off];
    nickle_check_mem(addr, 8);
    memcpy(cpu->mem + addr, &cpu->regs[r_src], 8);
}

void iloc_cstore() {
    size_t r_src = r() ; 
    size_t r_addr = r() ; 
    uint64_t addr = cpu->regs[r_addr];
    nickle_check_mem(addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}

void iloc_cstoreAI() {
    size_t r_src = r() ; 
    size_t r_base = r() ; 
    int64_t offset = op() ; 
    uint64_t addr = cpu->regs[r_base] + offset;
    nickle_check_mem(addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}

void iloc_cstoreAO() {
    size_t r_src = r() ; 
    size_t r_base = r() ; 
    size_t r_off = r() ; 
    uint64_t addr = cpu->regs[r_base] + cpu->regs[r_off];
    nickle_check_mem(addr, 1);
    cpu->mem[addr] = (uint8_t)(cpu->regs[r_src] & 0xFFu);
}
