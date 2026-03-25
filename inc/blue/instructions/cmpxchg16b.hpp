// Created 2025.12.29 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "../compilerlog.hpp"
#include "../types.hpp"

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

//  IMPORTANT
// This is more of an academic research and less actuall fast code because we're hitting a very 
//  important wall which is in the MSVC the calling convention. Whenever we're executing asm 
//  on Microsoft x64 we're calling a function using general convention. On CLANG/GCC however 
//  we're constrained by "cc" and "memory" flags.

#if defined(__clang__) || defined(__GNUC__)

    codeblock bool x_cmpxchg16b_zf (
        IN register u64 PTR b, // b 
        IT volatile u64 PTR a, // a 
        IT volatile u64 CTR R8 // value
    ) {
        
        register u64 RBX = b[0];
        register u64 RCX = b[1];
        register u64 RAX = a[0];
        register u64 RDX = a[1];
        register bool isEqual;

        __asm__ volatile (
            "cmpxchg16b %1\n\t"
            "sete %0"
            : "=q"(isEqual),
              "+m"(*R8),
              "+a"(RAX),
              "+d"(RDX)
            : "b"(RBX),
              "c"(RCX)
            : "cc", "memory"
        );

        a[0] = RAX;
        a[1] = RDX;

        return isEqual;
    }

    codeblock bool atomic_cmpxchg16b_zf (
        IN register u64 PTR b, // b 
        IT register u64 PTR a, // a 
        IT volatile u64 CTR R8 // value
    ) {
        register u64 RBX = b[0];
        register u64 RCX = b[1];
        register u64 RAX = a[0];
        register u64 RDX = a[1];
        register bool isEqual;

        __asm__ volatile (
            "lock cmpxchg16b %1\n\t"
            "sete %0"
            : "=q"(isEqual),
              "+m"(*R8),
              "+a"(RAX),
              "+d"(RDX)
            : "b"(RBX),
              "c"(RCX)
            : "cc", "memory"
        );

        a[0] = RAX;
        a[1] = RDX;

        return isEqual;
    }

    codeblock void x_cmpxchg16b (
        IN register u64 PTR b, // b 
        IT volatile u64 PTR a, // a 
        IT volatile u64 CTR R8 // value
    ) {
        register u64 RBX = b[0];
        register u64 RCX = b[1];
        register u64 RAX = a[0];
        register u64 RDX = a[1];

        __asm__ volatile (
            "cmpxchg16b %0"
            : "+m"(*R8),
              "+a"(RAX),
              "+d"(RDX)
            : "b"(RBX),
              "c"(RCX)
            : "cc", "memory"
        );

        a[0] = RAX;
        a[1] = RDX;
    }

    codeblock void atomic_cmpxchg16b (
        IN register u64 PTR b, // b 
        IT register u64 PTR a, // a 
        IT volatile u64 CTR R8 // value
    ) {
        register u64 RBX = b[0];
        register u64 RCX = b[1];
        register u64 RAX = a[0];
        register u64 RDX = a[1];

        __asm__ volatile (
            "lock cmpxchg16b %0"
            : "+m"(*R8),
              "+a"(RAX),
              "+d"(RDX)
            : "b"(RBX),
              "c"(RCX)
            : "cc", "memory"
        );

        a[0] = RAX;
        a[1] = RDX;
    }

#else

    COMPILERWARN ("missing cmpxchg16b_zf implementation!")

    extern "C" bool x_cmpxchg16b_zf (
        IN register u64 PTR RCX, // b 
        IT volatile u64 PTR RDX, // a 
        IT volatile u64 CTR R8   // value
    );

    COMPILERWARN ("missing atomic_cmpxchg16b_zf implementation!")

    extern "C" bool atomic_cmpxchg16b_zf (
        IN register u64 PTR RCX, // b 
        IN register u64 PTR RDX, // a 
        IT volatile u64 CTR R8   // value
    );

    COMPILERWARN ("missing cmpxchg16b implementation!")

    extern "C" void x_cmpxchg16b (
        IN register u64 PTR RCX, // b 
        IT volatile u64 PTR RDX, // a 
        IT volatile u64 CTR R8   // value
    );

    COMPILERWARN ("missing atomic_cmpxchg16b implementation!")


    extern "C" void atomic_cmpxchg16b (
        IN register u64 PTR RCX, // b 
        IN register u64 PTR RDX, // a 
        IT volatile u64 CTR R8   // value
    );

#endif
