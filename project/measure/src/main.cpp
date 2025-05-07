// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#define WAVE_NO_OPT 
#include <blue/wave.hpp>
#include <blue/error.hpp>
#undef max
#undef min
#include <benchmark/benchmark.h>


static void Castw8r32 (benchmark::State& state) {
    for (auto _ : state) {
        r32 val;
        w8r32 (128, val);

        benchmark::DoNotOptimize (val);
    }
}


static void Castw16r32 (benchmark::State& state) {
    for (auto _ : state) {
        r32 val;
        w16r32 (128, val);

        benchmark::DoNotOptimize (val);
    }
}


static void Castn8r32 (benchmark::State& state) {
    for (auto _ : state) {
        r32 val;
        n8r32 (128, val);

        benchmark::DoNotOptimize (val);
    }
}


static void Castn16r32 (benchmark::State& state) {
    for (auto _ : state) {
        r32 val;
        n16r32 (128, val);

        benchmark::DoNotOptimize (val);
    }
}

BENCHMARK (Castw8r32);  //-> MinTime(0.01);
BENCHMARK (Castw16r32); //-> MinTime(0.01);
BENCHMARK (Castn8r32);  //-> MinTime(0.01);
BENCHMARK (Castn16r32); //-> MinTime(0.01);

BENCHMARK_MAIN ();
