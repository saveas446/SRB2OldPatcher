#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "types.h"


int patch_wwidth(SRB2Executable* exe, int32 width) {
	printf("Patching window width to %d...\n", width);
	
	uint8 temp;
	
	// holy optimization
	patch_uint32(width, wwidth_table[exe.version][0], exe->handle);
	patch_uint32(width, wwidth_table[exe.version][1], exe->handle);
	patch_uint32(width, wwidth_table[exe.version][2], exe->handle);	
	patch_uint32(width, wwidth_table[exe.version][3], exe->handle);
	
	// vmode_t has fallen
	// billions must write custom asm routines
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
		
	// holy optimization 2
	patch_uint32(height, wheight_table[exe.version][0], exe->handle);
	patch_uint32(height, wheight_table[exe.version][1], exe->handle);
	patch_uint32(height, wheight_table[exe.version][2], exe->handle);	
	patch_uint32(height, wheight_table[exe.version][3], exe->handle);
	
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
	printf("Patching pause text to %s...\n", string);
	char pausetxt[0xB];
	
	if (strlen(string) > 0xB) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(pausetxt, string);
	
	switch(exe->version) {
		case VER_WEEN132:
			memcpy_to_file(0x056570, string, 0xB, exe->handle);
			break;		
		case VER_XMAS096:
			memcpy_to_file(0x05A570, string, 0xB, exe->handle);
			break;		
		case VER_DEMO1_00:
			memcpy_to_file(0x06EF40, string, 0xB, exe->handle);
			break;
		case VER_DEMO2_00:
			memcpy_to_file(0x077FA0, string, 0xB, exe->handle);
			break;
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			memcpy_to_file(0x075F80, string, 0xB, exe->handle);
			break;			
		case VER_DEMO4_32:
			memcpy_to_file(0x08B1A8, string, 0xB, exe->handle);
			break;		
		case VER_DEMO4_35:
			memcpy_to_file(0x08A1A8, string, 0xB, exe->handle);
			break;			
		case VER_TRN2K3:
			memcpy_to_file(0x0901A8, string, 0xB, exe->handle);
			break;			
		case VER_FD101_00:
		case VER_FD102_00:
		case VER_FD103_00:
		case VER_FD104_00:
			memcpy_to_file(0x09A200, string, 0xB, exe->handle);
			break;			
		case VER_FD108_00:
			memcpy_to_file(0x0A4200, string, 0xB, exe->handle);
			break;		
		case VER_FD109_00:
			memcpy_to_file(0x09F12C, string, 0xB, exe->handle);
			break;	
		case VER_FD109_02:
			memcpy_to_file(0x0A1168, string, 0xB, exe->handle);
			break;	
		case VER_FD109_04:
			memcpy_to_file(0x0C0188, string, 0xB, exe->handle);
			break;			
		case VER_FD109_04A:
			memcpy_to_file(0x0C4118, string, 0xB, exe->handle);
			break;
		case VER_SRB2FUN:
			memcpy_to_file(0x865292, string, 0xB, exe->handle);
			break;			
	}
	
	
	
	return EXIT_SUCCESS;
}

int patch_wtitle(SRB2Executable* exe, char* string) {
	
	printf("Patching window title to %s...\n", string);
	
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
	}
	
	char wtitle[str_length];
	
	if (strlen(string) > str_length) {
		perror("String too long");
		return EXIT_FAILURE;
	}
	
	strcpy(wtitle, string);
	
	switch(exe->version) {
		case VER_WEEN132:
			memcpy_to_file(0x056618, string, str_length, exe->handle);
			break;
		case VER_XMAS096:
			memcpy_to_file(0x05A618, string, str_length, exe->handle);
			break;
		case VER_DEMO1_00:
			memcpy_to_file(0x06EFCC, string, str_length, exe->handle);
			break;
		case VER_DEMO2_00:
			memcpy_to_file(0x07802C, string, str_length, exe->handle);
			break;
		case VER_DEMO3_00:
		case VER_DEMO4_00:
		case VER_DEMO4_10:
			memcpy_to_file(0x07600C, string, str_length, exe->handle);
			break;		
		case VER_DEMO4_32:
			memcpy_to_file(0x08B260, string, str_length, exe->handle);
			break;				
		case VER_DEMO4_35:
			memcpy_to_file(0x08A260, string, str_length, exe->handle);
			break;					
		case VER_TRN2K3:
			memcpy_to_file(0x090260, string, str_length, exe->handle);
			break;	
		case VER_FD101_00:
		case VER_FD102_00:
		case VER_FD103_00:
		case VER_FD104_00:
			memcpy_to_file(0x09A2B8, string, str_length, exe->handle);
			break;			
		case VER_FD108_00:
			memcpy_to_file(0x0A42B8, string, str_length, exe->handle);
			break;			
		case VER_FD109_00:
			memcpy_to_file(0x09F0C8, string, str_length, exe->handle);
			break;		
		case VER_FD109_02:
			memcpy_to_file(0x0A10E8, string, str_length, exe->handle);
			break;	
		case VER_FD109_04:
			memcpy_to_file(0x0C00F8, string, str_length, exe->handle);
			break;			
		case VER_FD109_04A:
			memcpy_to_file(0x0C4088, string, str_length, exe->handle);
			break;			
		case VER_SRB2FUN:
			memcpy_to_file(0x864504, string, str_length, exe->handle);
			break;						
	}
	
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