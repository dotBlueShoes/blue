// Created 2024.05.06 by Matthew Strumiłło (dotBlueShoes)
//  LICENSE: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
//
#pragma once
#include "types.hpp"
#include "lut.hpp"


//  ABOUT
// Wave types are defined in 4 different ways. Each can be accessed via preprocessor definition.
//  - (default) (avoids bitfields and braches)
//  - WAVE_LUT_OPT (uses lut)
//  - WAVE_BITWISE_SCALING_OPT (might outperform normal multiply in some embedded cases)
//  - WAVE_NO_OPT (uses the easy to understand solution without much opts)
// We distiguish between signed and unsigned wave type. Where unsigned wave is called a 
//  `normal` and signed variant simply a `wave`


//  TODO
// This code could be further optimized via SIMD use.


union w8 {
	u8 value;
	struct {
		u8 wave 	: 7;
		u8 phase 	: 1;
	} bitmask;
};


union n8 {
	u8 value;
	struct {
		u8 wave 	: 6;
		u8 phase 	: 1;
		u8 sign 	: 1;
	} bitmask;
};


union w16 {
	u16 value;
	struct {
		u16 wave 	: 15;
		u16 phase 	: 1;
	} bitmask;
};


union n16 {
	u16 value;
	struct {
		u16 wave 	: 14;
		u16 phase 	: 1;
		u16 sign 	: 1;
	} bitmask;
};


union u32r32 {
	r32 value;
	union {
		u32 value;
		struct {
			u32 mantissa 	: 23;
			u32 exponent	: 8;
			u32 sign 		: 1;
		} bitmask;
	} base;
};


//  ABOUT
// 8bit Wave to 32bit Real
void w8r32 (
	IN 		const u8& 	wave_in,
	OUT 	r32& 		wave_out
) {

	const r32 STEP7 = 1.0f / 128.0f;

	auto& real = *(u32r32*)&wave_out;
	const auto& base = *(const w8*)&wave_in;

	#ifdef WAVE_NO_OPT
		if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 128 + 1) * STEP7; } // 129 -> 255
		else { real.value = base.bitmask.wave * STEP7; } // for 0 -> 127
	#else
		const auto& value = base.value;			// Don't use bitfields.
		u8 wave 	= value & 0x7F;				// Extract wave 	(bits 0-6)
		u8 phase 	= (value >> 7);				// Extract sign 	(bit  7  )

		#ifdef WAVE_LUT_OPT
			u8 phasedWave = phase ? (128 - wave) : wave;	// Brachless
			real.value = DIV128LUT[phasedWave];				// LUT
		#else
			u8 phasedWave = phase ? (~wave - (0x7F)) : wave; 	// Brachless
			#ifdef WAVE_BITWISE_SCALING_OPT
				// Weird. Might be faster.
				real.value = (r32)(phasedWave << 17) * 0x1p-24f;
			#else
				real.value = (r32)phasedWave * STEP7;		// u8 to r32 cast.
			#endif
		#endif
	#endif
}


//  ABOUT
// 8bit Normal to 32bit Real
void n8r32 (
	IN 		const u8& 	wave_in,
	OUT 	r32& 		wave_out
) {

	const r32 STEP6 = 1.0f / 64.0f;

	auto& real = *(u32r32*)&wave_out;
	const auto& base = *(const n8*)&wave_in;

	#ifdef WAVE_NO_OPT
		if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 64 + 1) * STEP6; } // 65 -> 127
		else { real.value = base.bitmask.wave * STEP6; } // for 0 -> 63
		real.base.bitmask.sign = base.bitmask.sign;
	#else
		const auto& value = base.value;			// Don't use bitfields.
		u8 wave 	= value & 0x3F;				// Extract wave 	(bits 0-5)
		u8 phase 	= (value >> 6) & 1;			// Extract phase 	(bit  6  )
		u8 sign 	= (value >> 7);				// Extract sign 	(bit  7  )

		#ifdef WAVE_LUT_OPT
			u8 phasedWave = phase ? (64 - wave) : wave;		// Brachless
			real.value = DIV64LUT[phasedWave];				// LUT
		#else
			u8 phasedWave = phase ? (~wave - (128 + 64 - 1)) : wave; 	// Brachless
			#ifdef WAVE_BITWISE_SCALING_OPT
				// Weird. Might be faster.
				real.value = (r32)(phasedWave << 18) * 0x1p-24f;
			#else
				real.value = (r32)phasedWave * STEP6;		// u8 to r32 cast.
			#endif
		#endif

		// Set sign bit directly without the use of bitfields.
		((u32*)&real.value)[0] = (((u32*)&real.value)[0] & 0x7FFFFFFF) | (sign << 31);
	#endif
}


//  ABOUT
// 16bit Wave to 32bit Real
void w16r32 (
	IN 		const u16& 	wave_in,
	OUT 	r32& 		wave_out
) {

	const r32 STEP15 = 1.0f / 32768.0f;

	auto& real = *(u32r32*)&wave_out;
	const auto& base = *(w16*)&wave_in;

	#ifdef WAVE_NO_OPT
		if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 32768 + 1) * STEP15; } // 32769 -> 65 535
		else { real.value = base.bitmask.wave * STEP15; } // for 0 -> 32767
	#else
		const auto& value = base.value;			// Don't use bitfields.
		u16 wave 	= value & 0x7FFF;			// Extract wave 	(bits 0-14)
		u16 phase 	= (value >> 15);			// Extract sign 	(bit  15  )

		u16 phasedWave = phase ? (~wave - (0x7FFF)) : wave; 	// Brachless
		#ifdef WAVE_BITWISE_SCALING_OPT
			// Weird. Might be faster.
			real.value = (r32)(phasedWave << 9) * 0x1p-24f;
		#else
			real.value = (r32)phasedWave * STEP15;		// u8 to r32 cast.
		#endif
	#endif
}


//  ABOUT
// 16bit Normal to 32bit Real
void n16r32 (
	IN 		const u16& 	wave_in,
	OUT 	r32& 		wave_out
) {

	const r32 STEP14 = 1.0f / 16384.0f;

	auto& real = *(u32r32*)&wave_out;
	const auto& base = *(n16*)&wave_in;

	#ifdef WAVE_NO_OPT
		if (base.bitmask.phase) { real.value = (~base.bitmask.wave + 16384 + 1) * STEP14; } // 16385 -> 32767
		else { real.value = base.bitmask.wave * STEP14; } // for 0 -> 16383
		real.base.bitmask.sign = base.bitmask.sign;
	#else
		const auto& value = base.value;			// Don't use bitfields.
		u16 wave 	= value & 0x3FFF;			// Extract wave 	(bits 0-13)
		u16 phase 	= (value >> 14) & 1;		// Extract phase 	(bit  14  )
		u16 sign 	= (value >> 15);			// Extract sign 	(bit  15  )

		u16 phasedWave = phase ? (~wave - (0x8000 + 0x4000 - 1)) : wave; 	// Brachless
		#ifdef WAVE_BITWISE_SCALING_OPT
			// Weird. Might be faster.
			real.value = (r32)(phasedWave << 10) * 0x1p-24f;
		#else
			real.value = (r32)phasedWave * STEP14;		// u8 to r32 cast.
		#endif

		// Set sign bit directly without the use of bitfields.
		((u32*)&real.value)[0] = (((u32*)&real.value)[0] & 0x7FFFFFFF) | (sign << 31);
	#endif
}
