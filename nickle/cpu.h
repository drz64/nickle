#pragma once
#include <stdbool.h>

extern const int EXTRA_REGS ; 
extern const int R_STATIC_OFFSET ; 
extern const int R_ARGC_OFFSET ; 
extern const int R_ARGV_OFFSET ; 


typedef struct __cpu_t {
    size_t    reg_count;   // user regs (N)
    size_t    mem_size;

    uint64_t* regs;
    uint8_t*  mem;

    bool      halted;
} cpu_t;

/* program-provided configuration (emitted by compiler in program.c) */
extern const size_t PROGRAM_USER_REGS;
extern const size_t PROGRAM_MEM_SIZE;

extern const data_desc_t STATIC_DATA[];
extern const size_t STATIC_COUNT;
void iloc_main(cpu_t* cpu);

/* runtime lifecycle */
void nickle_init(cpu_t* cpu, size_t user_regs, size_t mem_size);
void nickle_free(cpu_t* cpu);
void nickle_build_static(cpu_t* cpu);
void nickle_build_args(cpu_t* cpu, int argc, char** argv);

/* deterministic termination + checks */
void nickle_trap(cpu_t* cpu, const char* msg);
void nickle_check_mem(cpu_t* cpu, uint64_t addr, uint64_t size);
