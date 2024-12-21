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
			printf("xmas 0.96\n");
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
	}
	
	return EXIT_SUCCESS;
}

int patch_pausedtxt(SRB2Executable* exe, char* string) {
	return EXIT_SUCCESS;
}