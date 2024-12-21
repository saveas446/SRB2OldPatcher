#pragma once

// define different int types
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;

// define boolean stuff
typedef uint8 bool;

#define TRUE 1
#define FALSE 0

typedef enum exe_version {
	VER_WEEN132,
	VER_XMAS096,
	VER_DEMO1_00,
	VER_DEMO2_00,
	VER_DEMO3_00,
	VER_DEMO4_00,
	VER_DEMO4_10,
	VER_DEMO4_32,
	VER_DEMO4_35,
	VER_FD101_00,
	VER_FD102_00,
	VER_FD103_00,
	VER_FD104_00,
	VER_FD108_00,
	VER_FD109_00,
	VER_FD109_02,
	VER_FD109_04,
	VER_FD109_04A,
	VER_SRB2FUN,
	VER_AUG2008,
	VER_SEP2008,
	NUM_VERSIONS
} exe_version;

typedef struct SRB2Executable {
	FILE * handle;
	uint32 size;
	uint8 checksum[16];
	exe_version version;
} SRB2Executable;