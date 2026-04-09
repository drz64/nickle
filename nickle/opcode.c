#include "nickle.h"
#include "cpu.h"
#include "iloc.h"
#include "stdio.h"

typedef void (*op_handler)();


const char* op_mnemonic[] = { 
    "op_halt", 
    "op_nop", 

    "op_add", 
    "op_sub", 
    "op_mult", 
    "op_div", 

    "op_addI", 
    "op_subI", 
    "op_rsubI", 
    "op_multI", 
    "op_divI", 
    "op_rdivI", 

    "op_lshift", 
    "op_lshiftI", 
    "op_rshift", 
    "op_rshiftI", 

    "op_and", 
    "op_andI", 
    "op_or", 
    "op_orI", 
    "op_xor", 
    "op_xorI", 

    "op_loadI",
    "op_load", 
    "op_loadAI", 
    "op_loadAO", 
 
    "op_cload", 
    "op_cloadAI", 
    "op_cloadAO", 
 
    "op_store", 
    "op_storeAI", 
    "op_storeAO", 
 
    "op_cstore", 
    "op_cstoreAI", 
    "op_cstoreAO", 

    "op_i2i", 
    "op_c2c", 
    "op_c2i", 
    "op_i2c", 

    "op_jsr",
    "op_ret",
    "op_jumpI", 

    "op_cmp_LT", 
    "op_cmp_LE", 
    "op_cmp_EQ", 
    "op_cmp_GE", 
    "op_cmp_GT", 
    "op_cmp_NE", 
    "op_cbr", 
 
    "op_p_int", 
    "op_p_char", 
    "op_p_str", 
    "op_p_prompt", 
    
    "op_d_reg", 
    "op_d_mem", 

    "op_atoi", 
    "op_is_i"
}  ; 

op_handler dispatch[op_COUNT] ; 

void register_operator(opcode code, op_handler handler) {
    if (code < 0 || code >= op_COUNT) {
        die("registering invalid opcode %d\n",code) ; 
    } else if (dispatch[code]) {
        die("multiple registration for opcode %d\n",code) ; 
    }
    dispatch[code] = handler ; 
}

void validate_registration() {
    for (int k=0; k<op_COUNT; k++) {
        if (!dispatch[k]) {
            die("no dispatcher for %d\n",k) ; 
        }
    }
}

void operators_registration() {
    register_operator(op_halt,iloc_halt); 
    register_operator(op_nop,iloc_nop); 

    register_operator(op_add,iloc_add); 
    register_operator(op_sub,iloc_sub); 
    register_operator(op_mult,iloc_mult); 
    register_operator(op_div,iloc_div); 

    register_operator(op_addI,iloc_addI); 
    register_operator(op_subI,iloc_subI); 
    register_operator(op_rsubI,iloc_rsubI); 
    register_operator(op_multI,iloc_multI); 
    register_operator(op_divI,iloc_divI); 
    register_operator(op_rdivI,iloc_rdivI); 

    register_operator(op_lshift,iloc_lshift); 
    register_operator(op_lshiftI,iloc_lshiftI); 
    register_operator(op_rshift,iloc_rshift); 
    register_operator(op_rshiftI,iloc_rshiftI); 

    register_operator(op_and,iloc_and); 
    register_operator(op_andI,iloc_andI); 
    register_operator(op_or,iloc_or); 
    register_operator(op_orI,iloc_orI); 
    register_operator(op_xor,iloc_xor); 
    register_operator(op_xorI,iloc_xorI); 

    register_operator(op_loadI,iloc_loadI);
    register_operator(op_load,iloc_load); 
    register_operator(op_loadAI,iloc_loadAI); 
    register_operator(op_loadAO,iloc_loadAO); 
 
    register_operator(op_cload,iloc_cload); 
    register_operator(op_cloadAI,iloc_cloadAI); 
    register_operator(op_cloadAO,iloc_cloadAO); 
 
    register_operator(op_store,iloc_store); 
    register_operator(op_storeAI,iloc_storeAI); 
    register_operator(op_storeAO,iloc_storeAO); 
 
    register_operator(op_cstore,iloc_cstore); 
    register_operator(op_cstoreAI,iloc_cstoreAI); 
    register_operator(op_cstoreAO,iloc_cstoreAO); 

    register_operator(op_i2i,iloc_i2i); 
    register_operator(op_c2c,iloc_c2c); 
    register_operator(op_c2i,iloc_c2i); 
    register_operator(op_i2c,iloc_i2c); 

    register_operator(op_jsr,iloc_jsr);
    register_operator(op_ret,iloc_ret);
    register_operator(op_jumpI,iloc_jumpI); 

    register_operator(op_cmp_LT,iloc_cmp_LT); 
    register_operator(op_cmp_LE,iloc_cmp_LE); 
    register_operator(op_cmp_EQ,iloc_cmp_EQ); 
    register_operator(op_cmp_GE,iloc_cmp_GE); 
    register_operator(op_cmp_GT,iloc_cmp_GT); 
    register_operator(op_cmp_NE,iloc_cmp_NE); 
    register_operator(op_cbr,iloc_cbr); 
 
    register_operator(op_p_int,iloc_p_int); 
    register_operator(op_p_char,iloc_p_char); 
    register_operator(op_p_str,iloc_p_str); 
    register_operator(op_p_prompt,iloc_p_prompt); 
    
    register_operator(op_d_reg,iloc_d_reg); 
    register_operator(op_d_mem,iloc_d_mem); 

    register_operator(op_atoi,iloc_atoi); 
    register_operator(op_is_i,iloc_is_i); 

    validate_registration() ; 
}



int64_t op() {
    return PROGRAM[cpu->pc++] ; 
}

size_t r() {
    return (size_t) op() ; 
}

void run() {
    cpu->pc = 0 ; 
    cpu->halted = false ; 
    while (!cpu->halted) {
        int64_t mn = op() ; 
#ifdef TRACE
        fprintf(stdout,"[%04lx::%s]\n",cpu->pc-1,op_mnemonic[mn]) ; 
#endif
        (*dispatch[mn])() ; 
        if (PROGRAM_RUN_LIMIT && --cpu->limit == 0) cpu->halted = true;
    }
}

void iloc_goto(int64_t adrs) {
    cpu->pc = adrs ; 
}
