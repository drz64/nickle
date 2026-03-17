#include "iloc.h"
#include "cpu.h"
#include <stdio.h>
#include <inttypes.h>

void iloc_p_int(cpu_t* cpu, int r) {
    if (cpu->halted) return;
    printf("%" PRId64 "\n", (int64_t)cpu->regs[r]);
}

void iloc_p_char(cpu_t* cpu, int r) {
    if (cpu->halted) return;
    putchar((char)(cpu->regs[r] & 0xFFu));
    putchar('\n');
}

void iloc_p_str(cpu_t* cpu, int r) {
    if (cpu->halted) return;
    uint64_t addr = cpu->regs[r];
    while (1) {
        nickle_check_mem(cpu, addr, 1);
        uint8_t c = cpu->mem[addr++];
        if (c == 0) break;
        putchar((char)c);
    }
    putchar('\n');
}

void iloc_d_reg(cpu_t* cpu) {
    if (cpu->halted) return;
    for (size_t i = 0; i < cpu->reg_count /*+EXTRA_REGS*/ ; i++) {
        printf("r%zu = 0x%016" PRIx64 " (%" PRId64 ")\n", i, cpu->regs[i], (int64_t)cpu->regs[i]);
    }
    printf("r_static = 0x%016" PRIx64 "\n", cpu->regs[cpu->reg_count+R_STATIC_OFFSET]);
    printf("r_argc = 0x%016" PRIx64 " (%" PRId64 ")\n", cpu->regs[cpu->reg_count+R_ARGC_OFFSET], (int64_t) cpu->regs[cpu->reg_count+R_ARGC_OFFSET]);
    printf("r_argv = 0x%016" PRIx64 "\n", cpu->regs[cpu->reg_count+R_ARGV_OFFSET]);

}

void iloc_d_mem(cpu_t* cpu, int r1, int r2) {
    if (cpu->halted) return;
    uint64_t a = cpu->regs[r1];
    uint64_t b = cpu->regs[r2];
    if (b < a) nickle_trap(cpu, "d_mem: invalid range");
    uint64_t n = b - a;
    nickle_check_mem(cpu, a, n);

    for (uint64_t i = 0; i < n; i++) {
        if ((i % 16u) == 0) printf("%08" PRIx64 ": ", a + i);
        printf("%02x ", cpu->mem[a + i]);
        if ((i % 16u) == 15u) putchar('\n');
    }
    if ((n % 16u) != 0u) putchar('\n');
}
