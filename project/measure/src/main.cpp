// Created 2025.05.07 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//

//
#define WAVE_NO_OPT 
#include <blue/wave.hpp>
#include <blue/error.hpp>
//
//#include <string>
#undef max
#undef min
#include <benchmark/benchmark.h>

//static void StringCreation (benchmark::State& state) {
//    for (auto _ : state) {
//        std::string empty ("hello");
//    }
//}

static void Castw8r32 (benchmark::State& state) {

    // This does not work.
    //for (auto it = state.begin(); it != state.end(); ++it) {
    //    auto& i8 = *(u8*)&it;
    //    r32 val;
    //
    //    w16r32 (i8, val);
    //
    //    benchmark::DoNotOptimize (val); // Prevent compiler from optimizing it away
    //}

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

//BENCHMARK (StringCreation);
//BENCHMARK (LoggingInfo) -> Iterations (2000);
BENCHMARK (Castw8r32);  //-> MinTime(0.01);
BENCHMARK (Castw16r32); //-> MinTime(0.01);
BENCHMARK (Castn8r32);  //-> MinTime(0.01);
BENCHMARK (Castn16r32); //-> MinTime(0.01);

BENCHMARK_MAIN ();

//{ // WAVE TYPE TESTING
//		TIMESTAMP::Timestamp before = TIMESTAMP::GetCurrent ();
//		r32 val;
//
//		for (u64 i = 0; i < 65536 * 2; ++i) {
//
//			auto& data = *(u8*)&i;
//			//w8r32 (data, val);
//			n8r32 (data, val);
//
//			//auto& data = *(u16*)&i;
//			//w16r32 (data, val);
//			//n16r32 (data, val);
//
//			// //LOGINFO ("i: %f, %llu\n", val, i);
//
//			//if (val <= 0.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val >= 1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val == 0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//
//			//if (val <= -1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val >=  1.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val == -0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val ==  0.5f) LOGINFO ("i: %f, %llu\n", val, i);
//			//if (val ==  0.0f) LOGINFO ("i: %f, %llu\n", val, i);
//			
//		}
//
//		r32 timePassed = TIMESTAMP::GetElapsed (before);
//		LOGINFO ("val: %f, %f\n", timePassed, val);
//	}

