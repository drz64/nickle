#include "nickle.h"
#include "iloc.h"
#include "cpu.h"
#include <stdio.h>
#include <inttypes.h>

void iloc_p_int() {
    size_t r1 = r() ;
    printf("%" PRId64 "\n", (int64_t)cpu->regs[r1]);
}

void iloc_p_char() {
    size_t r1 = r() ;
    putchar((char)(cpu->regs[r1] & 0xFFu));
    putchar('\n');
}

void iloc_p_str() {
    size_t r1 = r() ;
    size_t addr = cpu->regs[r1];
    while (1) {
        nickle_check_mem(addr, 1);
        uint8_t c = cpu->mem[addr++];
        if (c == 0) break;
        putchar((char)c);
    }
    putchar('\n');
}

void iloc_p_prompt() {
    size_t p = r() ; 
    fputs(PROMPTS[p],stdout) ; 
}

void iloc_d_reg() {
    for (int i = 0; i < cpu->reg_count /*+EXTRA_REGS*/ ; i++) {
        printf("r%-2d = 0x%016" PRIx64 " (%" PRId64 ")\n", i, cpu->regs[i], (int64_t)cpu->regs[i]);
    }
    printf("pc  = 0x%04lx\n", cpu->pc);
    printf("r_static = 0x%016" PRIx64 "\n", cpu->regs[cpu->reg_count+R_STATIC_OFFSET]);
    printf("r_argc   = 0x%016" PRIx64 " (%" PRId64 ")\n", cpu->regs[cpu->reg_count+R_ARGC_OFFSET], (int64_t) cpu->regs[cpu->reg_count+R_ARGC_OFFSET]);
    printf("r_argv   = 0x%016" PRIx64 "\n", cpu->regs[cpu->reg_count+R_ARGV_OFFSET]);
    printf("r_ra     = 0x%016" PRIx64 "\n", cpu->regs[cpu->reg_count+R_RA_OFFSET]);
}


void _iloc_d_mem(int64_t a, int64_t b) {
    if (b < a) nickle_trap("d_mem: invalid range");
    int64_t n = b - a;
    nickle_check_mem(a, n);

    for (uint64_t i = 0; i < n; i++) {
        if ((i % 16u) == 0) printf("%08" PRIx64 ": ", a + i);
        printf("%02x ", cpu->mem[a + i]);
        if ((i % 16u) == 15u) putchar('\n');
        else if (i % 8 == 7) printf("| ") ; 
    }
    if ((n % 16u) != 0u) putchar('\n');
}

void iloc_d_mem() {
    size_t r1 = r() ;
    size_t r2 = r() ;
    int64_t a = cpu->regs[r1];
    int64_t b = cpu->regs[r2];
    _iloc_d_mem(a,b) ; 
}
