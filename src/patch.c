#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "types.h"


int patch_wwidth(SRB2Executable* exe, int32 width) {
	
	switch(exe->version) {
		case VER_WEEN132:
			patch_uint32(width, 0x57718, exe->handle);
			patch_uint32(width, 0xCC54, exe->handle);
			patch_uint32(width, 0xCD23, exe->handle);
			break;
		case VER_XMAS096:
			patch_uint32(width, 0xCC54, exe->handle);
			patch_uint32(width, 0xCD23, exe->handle);
			patch_uint32(width, 0x5B718, exe->handle);
			patch_uint32(width, 0x5B720, exe->handle);
			break;
		case VER_DEMO1_00:
			patch_uint32(width, 0x70230, exe->handle);
			patch_uint32(width, 0x70238, exe->handle);
			patch_uint32(width, 0x7D42, exe->handle);
			break;
		case VER_DEMO2_00:
			patch_uint32(width, 0x7D52, exe->handle);
			patch_uint32(width, 0x7E33, exe->handle);
			patch_uint32(width, 0x79278, exe->handle);
			patch_uint32(width, 0x79280, exe->handle);
			break;
	}
	
	return EXIT_SUCCESS;
}

int patch_wheight(SRB2Executable* exe, int32 height) {
	
	switch(exe->version) {
		case VER_WEEN132:
			patch_uint32(height, 0x5771C, exe->handle);
			patch_uint32(height, 0xCC44, exe->handle);
			patch_uint32(height, 0xCC4F, exe->handle);
			patch_uint32(height, 0xCD13, exe->handle);
			patch_uint32(height, 0xCD1E, exe->handle);
			break;
		case VER_XMAS096:
			patch_uint32(height, 0x5B71C, exe->handle);
			patch_uint32(height, 0xCC44, exe->handle);
			patch_uint32(height, 0xCC4F, exe->handle);
			patch_uint32(height, 0xCD13, exe->handle);
			patch_uint32(height, 0xCD1E, exe->handle);
			break;
		case VER_DEMO1_00:
			patch_uint32(height, 0x70234, exe->handle);
			patch_uint32(height, 0x7D32, exe->handle);
			patch_uint32(height, 0x7D3D, exe->handle);
			patch_uint32(height, 0x7E13, exe->handle);
			patch_uint32(height, 0x7E1E, exe->handle);
			break;
		case VER_DEMO2_00:
			patch_uint32(height, 0x7927C, exe->handle);
			patch_uint32(height, 0x7D42, exe->handle);
			patch_uint32(height, 0x7D4D, exe->handle);
			patch_uint32(height, 0x7E23, exe->handle);
			patch_uint32(height, 0x7E2E, exe->handle);
			break;
	}
	
	return EXIT_SUCCESS;
}

int patch_pausedtxt(SRB2Executable* exe, char* string) {
	char pausetxt[0xB] = "\0\0\0\0\0\0\0\0\0\0\0";
	
	if (strlen(string) > 0xB) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(pausetxt, string);
	
	switch(exe->version) {
		case VER_WEEN132:
			memcpy_to_file(0x56570, string, 0xB, exe->handle);
			break;		
		case VER_XMAS096:
			memcpy_to_file(0x5A570, string, 0xB, exe->handle);
			break;		
		case VER_DEMO1_00:
			memcpy_to_file(0x6EF40, string, 0xB, exe->handle);
			break;
		case VER_DEMO2_00:
			memcpy_to_file(0x77FA0, string, 0xB, exe->handle);
			break;
	}
	
	
	
	return EXIT_SUCCESS;
}

int patch_wtitle(SRB2Executable* exe, char* string) {
	
	size_t str_length;
	switch(exe->version) {
		case VER_WEEN132:
		case VER_XMAS096:
			str_length = 0x13;
			break;
		case VER_DEMO1_00:
			str_length = 0x1B;
			break;
		case VER_DEMO2_00:
			str_length = 0x17;
			break;
	}
	
	char wtitle[str_length];
	
	if (strlen(string) > str_length) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(wtitle, string);
	
	switch(exe->version) {
		case VER_WEEN132:
			memcpy_to_file(0x56618, string, str_length, exe->handle);
			break;
		case VER_XMAS096:
			memcpy_to_file(0x5A618, string, str_length, exe->handle);
			break;
		case VER_DEMO1_00:
			memcpy_to_file(0x6EFCC, string, str_length, exe->handle);
			break;
		case VER_DEMO2_00:
			memcpy_to_file(0x7802C, string, str_length, exe->handle);
			break;
	}
	
	return EXIT_SUCCESS;
}