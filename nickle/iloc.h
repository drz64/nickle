#pragma once
#include <stdint.h>
#include <stddef.h>

typedef enum { D_INT, D_CHAR, D_STRING } data_kind_t;

typedef struct {
    data_kind_t kind;
    union {
        uint64_t    i;
        uint8_t     c;
        const char* s;
    } v;
} data_desc_t;

typedef struct __cpu_t cpu_t ; 

/* ================= Arithmetic ================= */
void iloc_nop(cpu_t* cpu);

void iloc_add(cpu_t* cpu, int r1, int r2, int r3);
void iloc_sub(cpu_t* cpu, int r1, int r2, int r3);
void iloc_mult(cpu_t* cpu, int r1, int r2, int r3);
void iloc_div(cpu_t* cpu, int r1, int r2, int r3);

void iloc_addI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_subI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_rsubI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_multI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_divI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_rdivI(cpu_t* cpu, int r1, uint64_t imm, int r3);

void iloc_lshift(cpu_t* cpu, int r1, int r2, int r3);
void iloc_lshiftI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_rshift(cpu_t* cpu, int r1, int r2, int r3);
void iloc_rshiftI(cpu_t* cpu, int r1, uint64_t imm, int r3);

void iloc_and(cpu_t* cpu, int r1, int r2, int r3);
void iloc_andI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_or(cpu_t* cpu, int r1, int r2, int r3);
void iloc_orI(cpu_t* cpu, int r1, uint64_t imm, int r3);
void iloc_xor(cpu_t* cpu, int r1, int r2, int r3);
void iloc_xorI(cpu_t* cpu, int r1, uint64_t imm, int r3);

/* ================= Memory ================= */
void iloc_load(cpu_t* cpu, int r_src, int r_dst);
void iloc_loadAI(cpu_t* cpu, int r_base, uint64_t offset, int r_dst);
void iloc_loadAO(cpu_t* cpu, int r_base, int r_off, int r_dst);

void iloc_cload(cpu_t* cpu, int r_src, int r_dst);
void iloc_cloadAI(cpu_t* cpu, int r_base, uint64_t offset, int r_dst);
void iloc_cloadAO(cpu_t* cpu, int r_base, int r_off, int r_dst);

void iloc_loadI(cpu_t* cpu, uint64_t imm, int r_dst);

void iloc_store(cpu_t* cpu, int r_src, int r_addr);
void iloc_storeAI(cpu_t* cpu, int r_src, int r_base, uint64_t offset);
void iloc_storeAO(cpu_t* cpu, int r_src, int r_base, int r_off);

void iloc_cstore(cpu_t* cpu, int r_src, int r_addr);
void iloc_cstoreAI(cpu_t* cpu, int r_src, int r_base, uint64_t offset);
void iloc_cstoreAO(cpu_t* cpu, int r_src, int r_base, int r_off);

/* ================= Copies / conversions ================= */
void iloc_i2i(cpu_t* cpu, int r1, int r2);
void iloc_c2c(cpu_t* cpu, int r1, int r2);
void iloc_c2i(cpu_t* cpu, int r1, int r2);
void iloc_i2c(cpu_t* cpu, int r1, int r2);

void iloc_c_i2i(cpu_t* cpu, int rb, int r1, int r2, int r3);
void iloc_c_c2c(cpu_t* cpu, int rb, int r1, int r2, int r3);

/* ================= Control ================= */
void iloc_cmp_LT(cpu_t* cpu, int r1, int r2, int r3);
void iloc_cmp_LE(cpu_t* cpu, int r1, int r2, int r3);
void iloc_cmp_EQ(cpu_t* cpu, int r1, int r2, int r3);
void iloc_cmp_GE(cpu_t* cpu, int r1, int r2, int r3);
void iloc_cmp_GT(cpu_t* cpu, int r1, int r2, int r3);
void iloc_cmp_NE(cpu_t* cpu, int r1, int r2, int r3);

/* ================= Debug / IO ================= */
void iloc_p_int(cpu_t* cpu, int r);
void iloc_p_char(cpu_t* cpu, int r);
void iloc_p_str(cpu_t* cpu, int r);
void iloc_d_reg(cpu_t* cpu);
void iloc_d_mem(cpu_t* cpu, int r1, int r2);

/* ================= Misc ================= */
void iloc_atoi(cpu_t* cpu, int r_src, int r_dst);
void iloc_is_i(cpu_t* cpu, int r_src, int r_dst);
void iloc_halt(cpu_t* cpu);

/* ================= read-only registers ================= */
int get_r_static_idx(cpu_t *cpu) ;
int get_r_argc_idx(cpu_t *cpu) ;
int get_r_argv_idx(cpu_t *cpu) ;
int get_reg(cpu_t *cpu, int idx) ;
