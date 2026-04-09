#include "nickle.h"
#include "cpu.h"
#include "iloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <execinfo.h>
#include <stdarg.h>

cpu_t *cpu ; // global. singleton.

void die(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fputc('\n',stderr);
    va_end(args);
    exit(1);
}


void nickle_trap(const char* msg) {
    fprintf(stderr, "Nickle trap: %s\n", msg);
    void *buffer[50];
    int n = backtrace(buffer, 50);
    backtrace_symbols_fd(buffer, n, 2);  // 2 = stderr
    exit(1);
}

void nickle_check_mem(uint64_t addr, uint64_t size) {
    if (addr < 0 || size < 0 || addr + size > cpu->mem_size) nickle_trap("memory access out of range");
}

cpu_t *nickle_init() {

    size_t user_regs = PROGRAM_USER_REGS ; 
    size_t mem_size = PROGRAM_MEM_SIZE ; 

    cpu = (cpu_t *) malloc(sizeof(cpu_t)) ; 
    if (!cpu) die("allocation failed");

    int total_regs = user_regs+R_EXTRA_SIZE ; 
    cpu->regs = calloc(total_regs, sizeof(int64_t));
    cpu->mem  = calloc(mem_size, 1);
    if (!cpu->regs || !cpu->mem) die("allocation failed");

    cpu->reg_count  = user_regs;
    cpu->mem_size = mem_size;

    cpu->halted = true; // we're off by default. see run() 
    cpu->pc = 0 ; 
    cpu->limit = PROGRAM_RUN_LIMIT ;
    return cpu ; 
}

void nickle_free() {
    free(cpu->regs);
    free(cpu->mem);
    free(cpu) ; 
}

void nickle_build_static() {
    uint64_t inline_size = 0;
    uint64_t string_size = 0;

    for (int i = 0; i < STATIC_COUNT; i++) {
        switch (STATIC_DATA[i].kind) {
            case D_INT:
                inline_size += 8 ; 
                break ; 

            case D_CHAR:
                inline_size += 1 ; 
                break ; 

            case D_STRING:
                string_size += (uint64_t)strlen(STATIC_DATA[i].v.s) + 1;
                inline_size += 8 ;
                break ; 
        }
    }

    uint64_t total = inline_size + string_size;
    if (total > cpu->mem_size) nickle_trap("static preload does not fit in memory");

    uint64_t base  = (uint64_t)cpu->mem_size - total;

    cpu->regs[cpu->reg_count+R_STATIC_OFFSET] = base;

    uint64_t inline_ptr = base;
    uint64_t string_ptr = base + inline_size;

    for (int i = 0; i < STATIC_COUNT; i++) {
        switch (STATIC_DATA[i].kind) {

            case D_INT:
                memcpy(cpu->mem + inline_ptr, &STATIC_DATA[i].v.i, 8);
                inline_ptr += 8;
                break;

            case D_CHAR: 
                cpu->mem[inline_ptr] = STATIC_DATA[i].v.c ;
                inline_ptr++ ;
                break;
            
            case D_STRING: {
                const char* s = STATIC_DATA[i].v.s;
                size_t n = strlen(s) + 1;
                memcpy(cpu->mem + inline_ptr, &string_ptr, 8);
                memcpy(cpu->mem + string_ptr, s, n);
                string_ptr += (uint64_t)n;
                inline_ptr += 8;
                break;
            }
        }
    }
}

void nickle_build_args(int argc, char** argv) {
    int count = argc > 1 ? argc - 1 : 0; // same, but stresses a point. 
    cpu->regs[cpu->reg_count+R_ARGC_OFFSET] = count;

    if (count == 0) {
        cpu->regs[cpu->reg_count+R_ARGV_OFFSET] = 0;
        return;
    }

    uint64_t inline_size = (uint64_t)count * 8;
    uint64_t string_size = 0;

    for (int i = 1; i < argc; i++)
        string_size += (uint64_t)strlen(argv[i]) + 1;

    uint64_t total = inline_size + string_size;

    uint64_t static_base = cpu->regs[cpu->reg_count+R_STATIC_OFFSET];
    if (total > static_base) nickle_trap("CLI preload does not fit below static block");

    uint64_t cli_base = static_base - total;
    cpu->regs[cpu->reg_count+R_ARGV_OFFSET] = cli_base;

    uint64_t inline_ptr = cli_base;
    uint64_t string_ptr = cli_base + inline_size;

    for (int i = 1; i < argc; i++) {
        size_t n = strlen(argv[i]) + 1;
        memcpy(cpu->mem + inline_ptr, &string_ptr, 8);
        memcpy(cpu->mem + string_ptr, argv[i], n);
        string_ptr += n;
        inline_ptr += 8;
    }
}


int main(int argc, char** argv) {
    operators_registration() ;
    cpu = nickle_init();
    nickle_build_static();
    nickle_build_args(argc, argv);
    cpu->regs[cpu->reg_count+R_RA_OFFSET] = PROGRAM_COUNT - 1 ; 
    run() ; 
#ifdef DUMPREGS
    iloc_d_reg() ; 
#endif
    nickle_free();
    return 0;
}
