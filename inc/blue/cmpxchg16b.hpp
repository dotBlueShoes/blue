// Created 2025.12.29 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "compilerlog.hpp"
#include "types.hpp"

//  TODO
// Reading the ZF flag is optional. So doing so should also be in a seperate inline function.

//  ABOUT
// Compares 128 volatile memory bits with contents of RDX:RAX, if equal set's said 128 volatile 
//  memory bits to the value of RCX:RBX. And sets ZF flag. Otherwise clears ZF flag and loads 
//  value of 128 volatile memory into RDX:RAX.

// [cycles] CMPXCHG16B is memory dependant 
//  atomic, multithreaded contention, different cores -> Additional ~50 cycles.
//  --------------
//  L1  : ~40–60
//  L2  : ~70–100
//  L3  : ~100–150
//  DRAM: ~300+
//  --------------

#if defined(__clang__) || defined(__GNUC__)

    codeblock bool cmpxchg16b (
        IT volatile u64* CEF ptr,
        IT register u64  REF exp_lo,
        IT register u64  REF exp_hi,
        IN register u64  REF des_lo,
        IN register u64  REF des_hi
    ) {
        register bool isEqual;

        __asm__ volatile (
            "cmpxchg16b %1\n\t"
            "sete %0"
            : "=q"(isEqual),
              "+m"(*ptr),
              "+a"(exp_lo),
              "+d"(exp_hi)
            : "b"(des_lo),
              "c"(des_hi)
            : "cc", "memory"
        );

        return isEqual;
    }

    codeblock bool atomic_cmpxchg16b (
        IT volatile u64* CEF ptr,
        IT register u64  REF exp_lo,
        IT register u64  REF exp_hi,
        IN register u64  REF des_lo,
        IN register u64  REF des_hi
    ) {
        register bool isEqual;

        __asm__ volatile (
            "lock cmpxchg16b %1\n\t"
            "sete %0"
            : "=q"(isEqual),
              "+m"(*ptr),
              "+a"(exp_lo),
              "+d"(exp_hi)
            : "b"(des_lo),
              "c"(des_hi)
            : "cc", "memory"
        );

        return isEqual;
    }

#else

    COMPILERWARN ("missing cmpxchg16b implementation!")

    codeblock bool cmpxchg16b (
        IT volatile u64* CEF ptr,
        IT register u64  REF exp_lo,
        IT register u64  REF exp_hi,
        IN register u64  REF des_lo,
        IN register u64  REF des_hi
    ) {
        return false;
    };

    COMPILERWARN ("missing atomic_cmpxchg16b implementation!")

    codeblock bool atomic_cmpxchg16b (
        IT volatile u64* CEF ptr,
        IT register u64  REF exp_lo,
        IT register u64  REF exp_hi,
        IN register u64  REF des_lo,
        IN register u64  REF des_hi
    ) {
        return false;
    };

#endif
