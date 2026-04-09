#pragma once
#include <stdbool.h>


typedef struct __cpu_t {
    size_t    reg_count;   // user regs (N)
    size_t    mem_size;

    int64_t* regs;
    uint8_t* mem;

    bool halted;
    int64_t pc; 
    size_t limit;

} cpu_t;

extern cpu_t *cpu ; // global. now singleton.
extern int64_t PC ; // global.


/* runtime lifecycle */
cpu_t *nickle_init();
void nickle_free();
void nickle_build_static();
void nickle_build_args(int argc, char** argv);

/* deterministic termination + checks */
void die(const char *fmt, ...) ;
void nickle_trap(const char* msg);
void nickle_check_mem(uint64_t addr, uint64_t size);


/* von-neumann implementation */

void operators_registration() ;
void run() ;
int64_t op() ; 
size_t r() ; 
void iloc_goto() ; 
