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
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			patch_uint32(width, 0x7D62, exe->handle);
			patch_uint32(width, 0x7E43, exe->handle);
			patch_uint32(width, 0x77258, exe->handle);
			patch_uint32(width, 0x77260, exe->handle);
			break;
		case VER_DEMO4_32:
			patch_uint32(width, 0x8632, exe->handle);
			patch_uint32(width, 0x8713, exe->handle);
			patch_uint32(width, 0x8C500, exe->handle);
			patch_uint32(width, 0x8C508, exe->handle);
			break;
		case VER_DEMO4_35:
			patch_uint32(width, 0x8632, exe->handle);
			patch_uint32(width, 0x8713, exe->handle);
			patch_uint32(width, 0x8B500, exe->handle);
			patch_uint32(width, 0x8B508, exe->handle);
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
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			patch_uint32(height, 0x7D52, exe->handle);
			patch_uint32(height, 0x7D5D, exe->handle);	
			patch_uint32(height, 0x7E33, exe->handle);	
			patch_uint32(height, 0x7E3E, exe->handle);	
			patch_uint32(height, 0x7725C, exe->handle);
			break;
		case VER_DEMO4_32:
			patch_uint32(height, 0x8622, exe->handle);
			patch_uint32(height, 0x862D, exe->handle);	
			patch_uint32(height, 0x8703, exe->handle);	
			patch_uint32(height, 0x870E, exe->handle);	
			patch_uint32(height, 0x8C504, exe->handle);	
			break;
		case VER_DEMO4_35:
			patch_uint32(height, 0x8622, exe->handle);
			patch_uint32(height, 0x862D, exe->handle);	
			patch_uint32(height, 0x8703, exe->handle);	
			patch_uint32(height, 0x870E, exe->handle);	
			patch_uint32(height, 0x8B504, exe->handle);	
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
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			memcpy_to_file(0x75F80, string, 0xB, exe->handle);
			break;			
		case VER_DEMO4_32:
			memcpy_to_file(0x8B1A8, string, 0xB, exe->handle);
			break;		
		case VER_DEMO4_35:
			memcpy_to_file(0x8A1A8, string, 0xB, exe->handle);
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
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			str_length = 0x17;
			break;
		case VER_DEMO4_32:
		case VER_DEMO4_35:
			str_length = 0x0A;
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
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			memcpy_to_file(0x7600C, string, str_length, exe->handle);
			break;		
		case VER_DEMO4_32:
			memcpy_to_file(0x8B260, string, str_length, exe->handle);
			break;				
		case VER_DEMO4_35:
			memcpy_to_file(0x8A260, string, str_length, exe->handle);
			break;						
	}
	
	return EXIT_SUCCESS;
}

void enable_drm(SRB2Executable* exe) {
	switch (exe->version) {
		case VER_AUG2008:
		patch_byte(0x8D, 0x576E, exe->handle);
		patch_byte(0x85, 0x576F, exe->handle);
		patch_byte(0x68, 0x5770, exe->handle);
		patch_byte(0xFE, 0x5771, exe->handle);
		patch_byte(0xFF, 0x5772, exe->handle);
		break;		
		case VER_SEP2008:
		patch_byte(0xA3, 0x4789, exe->handle);
		patch_byte(0xC4, 0x478A, exe->handle);
		patch_byte(0x41, 0x478B, exe->handle);
		patch_byte(0x4F, 0x478C, exe->handle);
		patch_byte(0x00, 0x478D, exe->handle);
		break;
	}
	return;
}

void disable_drm(SRB2Executable* exe) {
	switch (exe->version) {
		case VER_AUG2008:
		patch_byte(0xE9, 0x576E, exe->handle);
		patch_byte(0x1F, 0x576F, exe->handle);
		patch_byte(0x02, 0x5770, exe->handle);
		patch_byte(0x00, 0x5771, exe->handle);
		patch_byte(0x00, 0x5772, exe->handle);			
		break;
		case VER_SEP2008:
		patch_byte(0xE9, 0x4789, exe->handle);
		patch_byte(0x1F, 0x478A, exe->handle);
		patch_byte(0x02, 0x478B, exe->handle);
		patch_byte(0x00, 0x478C, exe->handle);
		patch_byte(0x00, 0x478D, exe->handle);	
		break;
	}
	return;
}