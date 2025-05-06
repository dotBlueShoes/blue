// Created 2025.05.06 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#include <blue/error.hpp>
//
#define WAVE_NO_OPT // this is the fastest on debug build
//#define WAVE_LUT_OPT
//#define WAVE_BITWISE_SCALING_OPT
//
#include <blue/wave.hpp>


s32 main (s32 argumentsCount, c8** arguments) {

	{ // BLUE START
		TIMESTAMP_BEGIN = TIMESTAMP::GetCurrent ();
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align fututre debug-logs
		LOGINFO ("Application Statred!\n");
	}

	{ // WAVE TYPE TESTING
		TIMESTAMP::Timestamp before = TIMESTAMP::GetCurrent ();
		static r32 val;

		for (u64 i = 0; i < 256 * 32; ++i) {
			auto& data = *(w8*)(u8*)&i;
			val = data.real32 ();
		}

		r32 timePassed = TIMESTAMP::GetElapsed (before);
		LOGINFO ("val: %f, %f\n", timePassed, val);
	}

	LOGINFO  ("Hello World\n");
	LOGWARN  ("Hello World\n");
	LOGERROR ("Hello World\n");

	{ // BLUE EXIT
		LOGMEMORY ();
		LOGINFO ("Finalized Execution\n");
		DEBUG (DEBUG_FLAG_LOGGING) putc ('\n', stdout); // Align debug-logs
	}

	return 0;
}
