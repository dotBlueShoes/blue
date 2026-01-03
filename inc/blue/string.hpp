// Created 2026.01.02 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "types.hpp"

//  ABOUT
// Equality String Test Called `3` with its u8 and u16 version.
//  ... TODO.
//

template <typename uN = u32>
void Is3StrEqu8 ( IT u8 REF condition, IN u8* CEF a, IN u8* CEF b );

template <typename uN = u32>
void Is3StrEqu16 ( IT u8 REF condition, IN u16* CEF a, IN u16* CEF b );


#ifdef BLUELIB_IMPLEMENTATION

template <typename uN>
void Is3StrEqu8 (
    IT u8  REF condition,
    IN u8* CEF a,
    IN u8* CEF b
) {
    for (uN i = 0; condition == 0; ++i) {
        condition += (a[i]	!= b[i]) << 2;  // 4
        condition += a[i]	== '\0';		// 1
        condition += b[i]	== '\0';		// 1
    }
}


template <typename uN>
void Is3StrEqu16 (
    IT u8   REF condition,
    IN u16* CEF a,
    IN u16* CEF b
) {
    for (uN i = 0; condition == 0; ++i) {
        condition += (a[i]	!= b[i]) << 2;  // 4
        condition += a[i]	== '\0';		// 1
        condition += b[i]	== '\0';		// 1
    }
}

#endif
