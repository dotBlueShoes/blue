// Created 2024.11.25 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
//
#include <stdint.h>
#include <wchar.h>
#include <array>
#include <ctype.h>
//
#include "sal.hpp"

using c8  = char;
using c16 = wchar_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8  = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using r32 = float;
using r64 = double;

template<class T, class S, S length>
using array_t = std::array<T, length>;

template<class T, u8 length>
using arr8  = array_t<T, u8, length>;

template<class T, u16 length>
using arr16 = array_t<T, u16, length>;

template<class T, u32 length>
using arr32 = array_t<T, u32, length>;

template<class T, u64 length>
using arr64 = array_t<T, u64, length>;

template<class T>
struct pair {
    T x, y;
};

// ---

//  ABOUT
// A forced inline should (in most cases) produce a warning/error if it faild to inline.
//
#if defined(_MSC_VER)
    #define codeblock static __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define codeblock static inline __attribute__((always_inline))
#else
    #define codeblock static inline
#endif

// --- 

//  ABOUT
// Makes the way an argument is being passed into a function more visible.
//
#define REF &
#define PTR *
#define CTR *const // cannot change the address in the function body, only value.
#define CPY

// OUTDATED - for_pointer_use this makes double pointers in asm code...
// ------------------------------------------------------------------------------
// u64* const& is not just stylistically redundant 
// it's actually worse than u64* in terms of codegen, since it 
// forces the pointer through memory instead of staying in a register. 
// There's genuinely no reason to use it over plain u64* for a pointer argument.
// just use 
#define CEF const& 
// ------------------------------------------------------------------------------

// --- 

//  ABOUT
// Use of an memory of which we do not control. Such memory should is marked by me inside 
//  structs and as function argument.
//
//#ifndef interface
//#define interface
//#endif

#define register

// low/high --- value-operator ---------
#define v64h(x) ((u16)(x >> 32))
#define v64l(x) ((u16)(x))
#define v32h(x) ((u16)(x >> 16))
#define v32l(x) ((u16)(x))
#define v16h(x)  ((u8)(x >> 8))
#define v16l(x)  ((u8)(x))
// -------------------------------------

// low/high --- address-operator -------
#define a64h(x) *((u32*)(void*)(&x) + 1)
#define a64l(x) *((u32*)(void*)(&x))
#define a32h(x) *((u16*)(void*)(&x) + 1)
#define a32l(x) *((u16*)(void*)(&x))
#define a16h(x) *((u8*)(void*)(&x) + 1)
#define a16l(x) *((u8*)(void*)(&x))
// -------------------------------------
