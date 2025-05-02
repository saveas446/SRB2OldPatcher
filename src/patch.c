#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "types.h"
#include "patch.h"

// lesson learned: do not declare variables in header files
// that are used in multiple places

uint32 wwidth_table [NUM_VERSIONS] [4] = {
	{0xCC54, 0xCD23, 0x57718, 0x57720},	
	{0xCC54, 0xCD23, 0x5B718, 0x5B720},	
	{0x7D42, 0x7E23, 0x70230, 0x70238},	
	{0x7D52, 0x7E33, 0x79278, 0x79280},	
	{0x7D62, 0x7E43, 0x77258, 0x77260},	
	{0x7D62, 0x7E43, 0x77258, 0x77260},	
	{0x7D62, 0x7E43, 0x77258, 0x77260},	
	{0x8632, 0x8713, 0x8C500, 0x8C508},	
	{0x8632, 0x8713, 0x8B500, 0x8B508},	
	{0x89B2, 0x8A93, 0x91930, 0x91938},	
	{0x8881, 0x8963, 0x9B9A8, 0x9B9B0},	
	{0x8881, 0x8963, 0x9B9A8, 0x9B9B0},
	{0x8881, 0x8963, 0x9B9A8, 0x9B9B0},
	{0x8881, 0x8963, 0x9B9A8, 0x9B9B0},
	{0x8A11, 0x8AF3, 0xA59CC, 0xA59D4},	
	{0xAD21, 0xAE03, 0xB6350, 0xB6358},	
	{0xB1FF, 0xB2E3, 0xBA350, 0xBA358},	
	{0xB3DF, 0xB4C3, 0xDF350, 0xDF358},	// fd 1.09.4 '06
	{0xB62E, 0xB713, 0xE3350, 0xE3358},	
	{0xBB7A, 0xBF03, 0xF23A0, 0xF23A8},	
	{0, 0, 0, 0},	
	{0xBE9A, 0xC223, 0xF43A0, 0xF43A8}
};

uint32 wheight_table [NUM_VERSIONS] [5] = {
	{0xCC44, 0xCC4F, 0xCD13, 0xCD1E, 0x5771C},	
	{0xCC44, 0xCC4F, 0xCD13, 0xCD1E, 0x5B71C},	// xmas 96
	{0x7D32, 0x7D3D, 0x7E13, 0x7E1E, 0x70234},	// demo 1
	{0x7D42, 0x7D4D, 0x7E23, 0x7E2E, 0x7927C},	// demo 2
	{0x7D52, 0x7D5D, 0x7E33, 0x7E3E, 0x7725C},  // demo 3
	{0x7D52, 0x7D5D, 0x7E33, 0x7E3E, 0x7725C},  // demo 4
	{0x7D52, 0x7D5D, 0x7E33, 0x7E3E, 0x7725C},  // demo 4.1
	{0x8622, 0x862D, 0x8703, 0x870E, 0x8C504},  // demo 4.32
	{0x8622, 0x862D, 0x8703, 0x870E, 0x8B504},  // demo 4.35
	{0x89A2, 0x89AD, 0x8A83, 0x8A8E, 0x91934},
	{0x8871, 0x887C, 0x8953, 0x895E, 0x9B9AC}, // fd 1.01
	{0x8871, 0x887C, 0x8953, 0x895E, 0x9B9AC}, // fd 1.02
	{0x8871, 0x887C, 0x8953, 0x895E, 0x9B9AC}, // fd 1.03
	{0x8871, 0x887C, 0x8953, 0x895E, 0x9B9AC}, // fd 1.04
	{0x8A01, 0x8A0C, 0x8AE3, 0x8AEE, 0xA59D0},
	{0xAD11, 0xAD1C, 0xADF3, 0xADFE, 0xB6354}, // fd 1.09
	{0xB1EF, 0xB1FA, 0xB2D3, 0xB2DE, 0xBA354},
	{0xB3CF, 0xB3DA, 0xB4B3, 0xB4BE, 0xDF354},
	{0xB61E, 0xB629, 0xB703, 0xB70E, 0xE3354}, // fd 1.09.4a
	{0xBB6A, 0xBB75, 0xBEF3, 0xBEFE, 0xF23A4},
	{0, 0, 0, 0, 0},
	{0xBE8A, 0xBE95, 0xC213, 0xC21E, 0xF43A4},
};

uint32 pausedtxt_table [NUM_VERSIONS] = {
0x056570,
0x05A570,
0x06EF40,
0x077FA0,
0x075F80, 
0x075F80, 
0x075F80, 
0x08B1A8,
0x08A1A8,
0x0901A8,
0x09A200,
0x09A200,
0x09A200,
0x09A200,
0x0A4200,
0x09F12C,
0x0A1168,
0x0C0188,
0x0C4118,
0x865292,
0x0,
0x0D55B0
};

uint32 wtitle_table [NUM_VERSIONS] = {
0x056618,
0x05A618,
0x06EFCC,
0x07802C,
0x07600C, 
0x07600C, 
0x07600C, 
0x08B260,
0x08A260,
0x090260,
0x09A2B8,
0x09A2B8,
0x09A2B8,
0x09A2B8,
0x0A42B8,
0x09F0C8,
0x0A10E8,
0x0C00F8,
0x0C4088,
0x864504,
0x0,
0x0D5190
};

int patch_wwidth(SRB2Executable* exe, int32 width) {
	printf("Patching window width to %d...\n", width);
	
	uint8 temp = 0;
	
	while (temp < 4) {
		printf("Patching value 0x%X at address 0x%X\n", width, wwidth_table[exe->version][temp]);
		patch_uint32(width, wwidth_table[exe->version][temp], exe->handle);
		temp++;
	}
	
	// there MUST be a way to optimize this...
	if (exe->version == VER_SRB2FUN) {

		read_byte(0x4A58, exe->handle, &temp);
			
		if (temp == 0xF7) {
			printf("Injecting new ASM routine into OpenMainWindow()...\n");
			// Could this be done better? Yes.
			// Do I care enough to make it better? No.
			patch_byte(0xB8, 0x4A58, exe->handle); // mov eax,
			patch_uint32(200, 0x4A59, exe->handle); // 200
			patch_byte(0x50, 0x4A5D, exe->handle); // push eax
			patch_byte(0xB8, 0x4A5E, exe->handle); // mov eax,
			patch_uint32(width, 0x4A5F, exe->handle); // (new width)
			patch_byte(0x50, 0x4A63, exe->handle); // push eax
				
			patch_byte(0xEB, 0x4A64, exe->handle); // jmp 0x04A68
			patch_byte(0x02, 0x4A65, exe->handle);
			patch_byte(0xF2, 0x4A66, exe->handle); // nop (2 bytes)
			patch_byte(0x90, 0x4A67, exe->handle);
		} else {
			patch_uint32(width, 0x4A5F, exe->handle);
		}
	} else if (exe->version == VER_SEP2008) {
		read_byte(0x4D88, exe->handle, &temp);
			
		if (temp == 0xF7) {
			printf("Injecting new ASM routine into OpenMainWindow()...\n");
			// Could this be done better? Yes.
			// Do I care enough to make it better? No.
			patch_byte(0xB8, 0x4D88, exe->handle); // mov eax,
			patch_uint32(200, 0x4D89, exe->handle); // 200
			patch_byte(0x50, 0x4D8D, exe->handle); // push eax
			patch_byte(0xB8, 0x4D8E, exe->handle); // mov eax,
			patch_uint32(width, 0x4D8F, exe->handle); // (new width)
			patch_byte(0x50, 0x4D93, exe->handle); // push eax
			
			patch_byte(0xEB, 0x4D94, exe->handle); // jmp 0x04DCA
			patch_byte(0x02, 0x4D95, exe->handle);
			patch_byte(0xF2, 0x4D96, exe->handle); // nop (2 bytes)
			patch_byte(0x90, 0x4D97, exe->handle);
		} else {
			patch_uint32(width, 0x4D8F, exe->handle);
		}
	}
	
	return EXIT_SUCCESS;
}

int patch_wheight(SRB2Executable* exe, int32 height) {
	printf("Patching window height to %d...\n", height);

			
	uint8 temp;
		

	while (temp < 5) {
		printf("Patching value 0x%X at address 0x%X\n", height, wheight_table[exe->version][temp]);
		patch_uint32(height, wheight_table[exe->version][temp], exe->handle);
		temp++;
	}
	
	// there MUST be a way to optimize this...
	if (exe->version == VER_SRB2FUN) {
		read_byte(0x4A58, exe->handle, &temp);
			
		if (temp == 0xF7) {
			printf("Injecting new ASM routine into OpenMainWindow()...\n");
			patch_byte(0xB8, 0x4A58, exe->handle); // mov eax,
			patch_uint32(height, 0x4A59, exe->handle); // (new height)
			patch_byte(0x50, 0x4A5D, exe->handle); // push eax
			patch_byte(0xB8, 0x4A5E, exe->handle); // mov eax,
			patch_uint32(320, 0x4A5F, exe->handle); // 320
			patch_byte(0x50, 0x4A63, exe->handle); // push eax
				
			patch_byte(0xEB, 0x4A64, exe->handle); // jmp 0x04A68
			patch_byte(0x02, 0x4A65, exe->handle);
			patch_byte(0xF2, 0x4A66, exe->handle); // nop (2 bytes)
			patch_byte(0x90, 0x4A67, exe->handle);
		} else {
			patch_uint32(height, 0x4A59, exe->handle);
		}
	} else if (exe->version == VER_SEP2008) {
		read_byte(0x4D88, exe->handle, &temp);
			
		if (temp == 0xF7) {
			printf("Injecting new ASM routine into OpenMainWindow()...\n");
			patch_byte(0xB8, 0x4D88, exe->handle); // mov eax,
			patch_uint32(height, 0x4D89, exe->handle); // 200
			patch_byte(0x50, 0x4D8D, exe->handle); // push eax
			patch_byte(0xB8, 0x4D8E, exe->handle); // mov eax,
			patch_uint32(320, 0x4D8F, exe->handle); // (new width)
			patch_byte(0x50, 0x4D93, exe->handle); // push eax
				
			patch_byte(0xEB, 0x4D94, exe->handle); // jmp 0x04DCA
			patch_byte(0x02, 0x4D95, exe->handle);
			patch_byte(0xF2, 0x4D96, exe->handle); // nop (2 bytes)
			patch_byte(0x90, 0x4D97, exe->handle);
		} else {
			patch_uint32(height, 0x4D89, exe->handle);
		}
	}
	
	return EXIT_SUCCESS;
}

int patch_pausedtxt(SRB2Executable* exe, char* string) {
	printf("Patching pause text to \"%s\"...\n", string);
	char pausetxt[0xB];
	
	if (strlen(string) > 0xB) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(pausetxt, string);
	
	memcpy_to_file(pausedtxt_table[exe->version], string, 0xB, exe->handle);

	return EXIT_SUCCESS;
}

int patch_wtitle(SRB2Executable* exe, char* string) {
	
	printf("Patching window title to \"%s\"...\n", string);
	
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
		case VER_TRN2K3:
		case VER_FD101_00:
		case VER_FD102_00:
		case VER_FD103_00:
		case VER_FD104_00:
		case VER_FD108_00:
		case VER_FD109_00:
			str_length = 0x0A;
			break;
		case VER_FD109_02:
		case VER_FD109_04:
		case VER_FD109_04A:
			str_length = 0x0F;
			break;	
		case VER_SRB2FUN:
			str_length = 0x38;
			break;
		case VER_SEP2008:
			str_length = 0x23;
			break;	
	}
	
	char wtitle[str_length];
	
	if (strlen(string) > str_length) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(wtitle, string);
	
	memcpy_to_file(wtitle_table[exe->version], string, str_length, exe->handle);
	
	return EXIT_SUCCESS;
}

void enable_drm(SRB2Executable* exe) {
	printf("Enabling DRM...\n");
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
		default:
		puts("How?\n");
		break;
	}
	return;
}

void disable_drm(SRB2Executable* exe) {
	printf("Disabling DRM...\n");
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
		default:
		puts("How?\n");
		break;
	}
	return;
}

void enable_iwad_chk(SRB2Executable* exe) {
	printf("Enabling IWAD checking...\n");
	switch (exe->version) {
		case VER_FD109_00:
		patch_byte(0x74, 0x8BFB3, exe->handle);
		break;
		case VER_FD109_02:
		patch_byte(0x74, 0x8EA93, exe->handle);
		break;
		case VER_FD109_04:
		patch_byte(0x74, 0x94E44, exe->handle);
		break;
		case VER_FD109_04A:
		patch_byte(0x74, 0x98AC2, exe->handle);
		break;
		case VER_SRB2FUN:
		patch_byte(0x74, 0xA862F, exe->handle);
		break;
		default:
		puts("How?\n");
		break;
	}
	return;
}

void disable_iwad_chk(SRB2Executable* exe) {
	printf("Disabling IWAD checking...\n");
	switch (exe->version) {
		case VER_FD109_00:
		patch_byte(0xEB, 0x8BFB3, exe->handle);
		break;
		case VER_FD109_02:
		patch_byte(0xEB, 0x8EA93, exe->handle);
		break;
		case VER_FD109_04:
		patch_byte(0xEB, 0x94E44, exe->handle);
		break;
		case VER_FD109_04A:
		patch_byte(0xEB, 0x98AC2, exe->handle);
		break;
		case VER_SRB2FUN:
		patch_byte(0xEB, 0xA862F, exe->handle);
		break;
		default:
		puts("How?\n");
		break;
	}
	return;
}