// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//

//
#define WAVE_NO_OPT // this is the fastest on debug build
//#define WAVE_LUT_OPT
//#define WAVE_BITWISE_SCALING_OPT
//
#include <blue/wave.hpp>
#include <blue/error.hpp>
//
#undef max
#undef min
#include <string>
#include <benchmark/benchmark.h>

static void BM_StringCreation (benchmark::State& state) {
    for (auto _ : state) {
        std::string empty ("hello");
    }
}

BENCHMARK (BM_StringCreation);

BENCHMARK_MAIN ();

