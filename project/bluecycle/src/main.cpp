// Created 2025.05.08 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#include <blue/error.hpp>
// default (18-20)
//#define WAVE_LUT_OPT // (18-20)
//#define WAVE_BITWISE_SCALING_OPT // (18-20)
//#define WAVE_NO_OPT // (18-20)
#define NEW_WAY_WAVE // 18-20
#include <blue/wave.hpp>

#include <intrin.h>

#include <blue/concepts.hpp>

s32 main () {

    { // BLUE START
        TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
        DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
        LOGINFO ("Application Statred!\n");
    }

    {
        int cpuInfo[4];
        u64 start, end;

        u8 i = rand () % 256; // pseudo-random Input prevents optimalization.
        r32 r;

        __cpuid (cpuInfo, 0);
        start = __rdtsc ();

        //for (u16 i = 0; i < 256; ++i) { // Section
        
            w8r32 (i, r);
            //r = OUT_LUT[i];
        //    LOGINFO ("a");
        //}

        __cpuid (cpuInfo, 0);
        end = __rdtsc();
        u64 cycles = end - start;

        LOGINFO ("clocks: %llu, val: %f\n", cycles, r);
    }

    { // BLUE EXIT
        LOGMEMORY ();
        LOGINFO ("Finalized Execution\n");
        DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
    }

}
