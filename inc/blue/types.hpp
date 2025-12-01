// Created 2024.11.25 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//

#pragma once
#include <stdint.h>
#include <wchar.h>
#include <array>
#include <ctype.h>

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

template<class T, u32 length>
using arr64 = array_t<T, u32, length>;

template<class T>
struct pair {
    T x, y;
};

// --- 

#define REF &
#define CEF const&
#define CPY

// --- 

//  ABOUT
// Use of an memory of which we do not control. Such memory should is marked by me 
//  inside structs and as function argument.
//
#define interface

// volatile 
// register

// ---

//  TODO
// REDO Equality String Test
//
//
// Equality String Test Called `3` with its u8 and u16 version.
//  ...
//

void IsEqualS3_8 (
    IO u8  REF condition,
    IN u8* CEF a,
    IN u8* CEF b
) {
    for (u32 i = 0; condition == 0; ++i) {
        condition += (a[i]	!= b[i]) << 2;  // 4
        condition += a[i]	== '\0';		// 1
        condition += b[i]	== '\0';		// 1
    }
}

void IsEqualS3_16 (
    IO u8   REF condition,
    IN u16* CEF a,
    IN u16* CEF b
) {
    for (u32 i = 0; condition == 0; ++i) {
        condition += (a[i]	!= b[i]) << 2;  // 4
        condition += a[i]	== '\0';		// 1
        condition += b[i]	== '\0';		// 1
    }
}

// ---
