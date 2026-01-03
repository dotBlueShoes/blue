// Created 2025.12.01 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once 
#include "types.hpp"

namespace STRINGCASE {

    void ToLower ( IN u32 REF length, ITN (length) c8* CEF data );
    void ToUpper ( IN u32 REF length, ITN (length) c8* CEF data );

}

#ifdef BLUELIB_IMPLEMENTATION
namespace STRINGCASE {

    void ToLower (
        IN           u32 REF length,
        ITN (length) c8* CEF data
    ) {
        for (u32 i = 0; i < length; ++i) {
            data[i] = tolower (data[i]);
        }
    }

    void ToUpper (
        IN           u32 REF length,
        ITN (length) c8* CEF data
    ) {
        // TODO
    }

}
#endif
