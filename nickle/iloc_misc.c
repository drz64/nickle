#include "iloc.h"
#include "cpu.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void iloc_i2i() {
    size_t r1 = r() ; size_t r2 = r() ; 
    cpu->regs[r2] = cpu->regs[r1];
}

void iloc_c2c() {
    size_t r1 = r() ; size_t r2 = r() ; 
    cpu->regs[r2] = cpu->regs[r1] & 0xFFu;
}

void iloc_c2i() {
    size_t r1 = r() ; size_t r2 = r() ; 
    cpu->regs[r2] = cpu->regs[r1] & 0xFFu;
}

void iloc_i2c() {
    size_t r1 = r() ; size_t r2 = r() ; 
    cpu->regs[r2] = cpu->regs[r1] & 0xFFu;
}

static int is_bin_digit(char c){ return c=='0' || c=='1'; }
static int is_oct_digit(char c){ return c>='0' && c<='7'; }
static int is_dec_digit(char c){ return c>='0' && c<='9'; }
static int is_hex_digit(char c){ return (c>='0'&&c<='9') || (c>='a'&&c<='f') || (c>='A'&&c<='F'); }


static char* parse_u64(const char* s, int64_t* out) {
    if (*s == '\0') return "atoi: empty string";

    int neg = 0;
    if (*s == '-') {
        neg = 1;
        s++;
        if (*s == '\0') return "atoi: invalid decimal";
    }

    int base = 10;
    if (!neg && s[0]=='0' && (s[1]=='x' || s[1]=='X')) { base = 16; s += 2; if (*s=='\0') return "atoi: invalid hex"; }
    else if (!neg && s[0]=='0' && (s[1]=='b' || s[1]=='B')) { base = 2; s += 2; if (*s=='\0') return "atoi: invalid binary"; }
    else if (!neg && s[0]=='0' && s[1] != '\0') { base = 8; s += 1; }

    int64_t v = 0;
    for (; *s; s++) {
        char c = *s;
        int digit;
        if (base == 2)  { if (!is_bin_digit(c)) return "atoi: invalid binary"; digit = c - '0'; }
        else if (base == 8) { if (!is_oct_digit(c)) return "atoi: invalid octal"; digit = c - '0'; }
        else if (base == 10) { if (!is_dec_digit(c)) return "atoi: invalid decimal"; digit = c - '0'; }
        else {
            if (!is_hex_digit(c)) return "atoi: invalid hex";
            if (c>='0'&&c<='9') digit = c-'0';
            else if (c>='a'&&c<='f') digit = 10 + (c-'a');
            else digit = 10 + (c-'A');
        }
        v = v * base + digit;
    }

    *out = neg ? -v : v;
    return NULL;
}

void unified_parse_u64(int justChecking) {
    size_t r_src = r() ; size_t r_dst = r() ; 

    uint64_t addr = cpu->regs[r_src];

    // read null-terminated string within bounds
    uint64_t i = addr;
    while (1) {
        nickle_check_mem(i, 1);
        if (cpu->mem[i] == 0) break;
        i++;
    }
    size_t len = (size_t)(i - addr);
    // copy to local buffer
    char* tmp = (char*)malloc(len + 1);
    if (!tmp) nickle_trap("atoi: allocation failed");
    memcpy(tmp, cpu->mem + addr, len);
    tmp[len] = 0;

    int64_t v ; 
    char * error = parse_u64(tmp, &v);
    free(tmp);

    if (justChecking) {
        cpu->regs[r_dst] = error == 0 ;
    } else {
        if (error) {
            nickle_trap(error) ; 
        } else {
            cpu->regs[r_dst] = v;
        }
    }
}

void iloc_atoi() {
    unified_parse_u64(0) ; 
}

void iloc_is_i() {
    unified_parse_u64(1) ; 
}

void iloc_halt() {
    cpu->halted = true;
}
