#pragma once
#include <stdint.h>
#include <stddef.h>



void iloc_halt();
void iloc_nop();

/* ================= Arithmetic ================= */

void iloc_add();
void iloc_sub();
void iloc_mult();
void iloc_div();

void iloc_addI();
void iloc_subI();
void iloc_rsubI();
void iloc_multI();
void iloc_divI();
void iloc_rdivI();

void iloc_lshift();
void iloc_lshiftI();
void iloc_rshift();
void iloc_rshiftI();

void iloc_and();
void iloc_andI();
void iloc_or();
void iloc_orI();
void iloc_xor();
void iloc_xorI();

/* ================= Memory ================= */
void iloc_load();
void iloc_loadAI();
void iloc_loadAO();

void iloc_cload();
void iloc_cloadAI();
void iloc_cloadAO();

void iloc_loadI();

void iloc_store();
void iloc_storeAI();
void iloc_storeAO();

void iloc_cstore();
void iloc_cstoreAI();
void iloc_cstoreAO();

/* ================= Copies / conversions ================= */
void iloc_i2i();
void iloc_c2c();
void iloc_c2i();
void iloc_i2c();

/* ================= Control ================= */
void iloc_cmp_LT();
void iloc_cmp_LE();
void iloc_cmp_EQ();
void iloc_cmp_GE();
void iloc_cmp_GT();
void iloc_cmp_NE();

void iloc_jsr() ; 
void iloc_ret() ; 
void iloc_jumpI() ; 
void iloc_cbr() ; 

/* ================= Debug / IO ================= */
void iloc_p_int();
void iloc_p_char();
void iloc_p_str();
void iloc_p_prompt() ; 
void iloc_d_reg();
void iloc_d_mem();
void _iloc_d_mem(int64_t a, int64_t b) ;

/* ================= Misc ================= */
void iloc_atoi();
void iloc_is_i();
