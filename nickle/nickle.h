#include <stdint.h>
#include <stddef.h>

#define R_RA_OFFSET 0
#define R_STATIC_OFFSET 1
#define R_ARGC_OFFSET 2
#define R_ARGV_OFFSET 3 
#define R_EXTRA_SIZE 4

typedef enum { D_INT, D_CHAR, D_STRING } data_kind_t;

typedef struct {
    data_kind_t kind;
    union {
        uint64_t    i;
        uint8_t     c;
        const char* s;
    } v;
} data_desc_t;


typedef enum { 
    op_halt, 
    op_nop, 

    op_add, 
    op_sub, 
    op_mult, 
    op_div, 

    op_addI, 
    op_subI, 
    op_rsubI, 
    op_multI, 
    op_divI, 
    op_rdivI, 

    op_lshift, 
    op_lshiftI, 
    op_rshift, 
    op_rshiftI, 

    op_and, 
    op_andI, 
    op_or, 
    op_orI, 
    op_xor, 
    op_xorI, 

    op_loadI,
    op_load, 
    op_loadAI, 
    op_loadAO, 
 
    op_cload, 
    op_cloadAI, 
    op_cloadAO, 
 
    op_store, 
    op_storeAI, 
    op_storeAO, 
 
    op_cstore, 
    op_cstoreAI, 
    op_cstoreAO, 

    op_i2i, 
    op_c2c, 
    op_c2i, 
    op_i2c, 

    op_jsr,
    op_ret,
    op_jumpI, 

    op_cmp_LT, 
    op_cmp_LE, 
    op_cmp_EQ, 
    op_cmp_GE, 
    op_cmp_GT, 
    op_cmp_NE, 
    op_cbr, 
 
    op_p_int, 
    op_p_char, 
    op_p_str, 
    op_p_prompt, 
    
    op_d_reg, 
    op_d_mem, 

    op_atoi, 
    op_is_i, 

    op_COUNT
} opcode ; 

extern const char* op_mnemonic[] ;


/* program-provided configuration (emitted by compiler in program.c) */
extern const size_t PROGRAM_USER_REGS;
extern const size_t PROGRAM_MEM_SIZE;
extern const size_t PROGRAM_RUN_LIMIT;
extern const data_desc_t STATIC_DATA[];
extern const size_t STATIC_COUNT;
extern const int64_t PROGRAM[];
extern const size_t PROGRAM_COUNT;
extern const char* PROMPTS[] ;