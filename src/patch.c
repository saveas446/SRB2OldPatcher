#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "types.h"


int patch_wwidth(SRB2Executable* exe, int32 width) {
	printf("Patching window width to %d...\n", width);
	switch(exe->version) {
		case VER_WEEN132:
			patch_uint32(width, 0xCC54, exe->handle);
			patch_uint32(width, 0xCD23, exe->handle);
			patch_uint32(width, 0x57718, exe->handle);
			break;
		case VER_XMAS096:
			patch_uint32(width, 0xCC54, exe->handle);
			patch_uint32(width, 0xCD23, exe->handle);
			patch_uint32(width, 0x5B718, exe->handle);
			patch_uint32(width, 0x5B720, exe->handle);
			break;
		case VER_DEMO1_00:
			patch_uint32(width, 0x7D42, exe->handle);
			patch_uint32(width, 0x7E23, exe->handle);
			patch_uint32(width, 0x70230, exe->handle);
			patch_uint32(width, 0x70238, exe->handle);
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
		case VER_TRN2K3:
			patch_uint32(width, 0x89B2, exe->handle);
			patch_uint32(width, 0x8A93, exe->handle);
			patch_uint32(width, 0x91930, exe->handle);	
			patch_uint32(width, 0x91938, exe->handle);	
			break;
		case VER_FD101_00:
		case VER_FD102_00:
		case VER_FD103_00:
		case VER_FD104_00:
			patch_uint32(width, 0x8881, exe->handle);
			patch_uint32(width, 0x8963, exe->handle);
			patch_uint32(width, 0x9B9A8, exe->handle);	
			patch_uint32(width, 0x9B9B0, exe->handle);
			break;
		case VER_FD108_00:
			patch_uint32(width, 0x8A11, exe->handle);
			patch_uint32(width, 0x8AF3, exe->handle);
			patch_uint32(width, 0xA59CC, exe->handle);	
			patch_uint32(width, 0xA59D4, exe->handle);
			break;
		case VER_FD109_00:
			patch_uint32(width, 0xAD21, exe->handle);
			patch_uint32(width, 0xAE03, exe->handle);
			patch_uint32(width, 0xB6350, exe->handle);	
			patch_uint32(width, 0xB6358, exe->handle);
			break;		
		case VER_FD109_02:
			patch_uint32(width, 0xB1FF, exe->handle);
			patch_uint32(width, 0xB2E3, exe->handle);
			patch_uint32(width, 0xBA350, exe->handle);	
			patch_uint32(width, 0xBA358, exe->handle);
			break;	
		case VER_FD109_04:
			patch_uint32(width, 0xB3DF, exe->handle);
			patch_uint32(width, 0xB4C3, exe->handle);
			patch_uint32(width, 0xDF350, exe->handle);	
			patch_uint32(width, 0xDF358, exe->handle);
			break;	
		case VER_FD109_04A:
			patch_uint32(width, 0xB62E, exe->handle);
			patch_uint32(width, 0xB713, exe->handle);
			patch_uint32(width, 0xE3350, exe->handle);	
			patch_uint32(width, 0xE3358, exe->handle);
			break;	
		case VER_SRB2FUN:
			patch_uint32(width, 0xBB7A, exe->handle);
			patch_uint32(width, 0xBF03, exe->handle);
			patch_uint32(width, 0xF23A0, exe->handle);	
			patch_uint32(width, 0xF23A8, exe->handle);
			
			uint8 temp;
			// vmode_t has fallen
			// billions must write custom asm routines
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

			break;	
	}
	
	return EXIT_SUCCESS;
}

int patch_wheight(SRB2Executable* exe, int32 height) {
	printf("Patching window height to %d...\n", height);
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
		case VER_TRN2K3:
			patch_uint32(height, 0x89A2, exe->handle);
			patch_uint32(height, 0x89AD, exe->handle);
			patch_uint32(height, 0x8A83, exe->handle);
			patch_uint32(height, 0x8A8E, exe->handle);
			patch_uint32(height, 0x91934, exe->handle);
			break;
		case VER_FD101_00:
		case VER_FD102_00:
		case VER_FD103_00:
		case VER_FD104_00:
			patch_uint32(height, 0x8871, exe->handle);
			patch_uint32(height, 0x887C, exe->handle);
			patch_uint32(height, 0x8953, exe->handle);
			patch_uint32(height, 0x895E, exe->handle);
			patch_uint32(height, 0x9B9AC, exe->handle);
			break;
		case VER_FD108_00:
			patch_uint32(height, 0x8A01, exe->handle);
			patch_uint32(height, 0x8A0C, exe->handle);
			patch_uint32(height, 0x8AE3, exe->handle);
			patch_uint32(height, 0x8AEE, exe->handle);
			patch_uint32(height, 0xA59D0, exe->handle);
			break;
		case VER_FD109_00:
			patch_uint32(height, 0xAD11, exe->handle);
			patch_uint32(height, 0xAD1C, exe->handle);
			patch_uint32(height, 0xADF3, exe->handle);
			patch_uint32(height, 0xADFE, exe->handle);
			patch_uint32(height, 0xB6354, exe->handle);
			break;
		case VER_FD109_02:
			patch_uint32(height, 0xB1EF, exe->handle);
			patch_uint32(height, 0xB1FA, exe->handle);
			patch_uint32(height, 0xB2D3, exe->handle);
			patch_uint32(height, 0xB2DE, exe->handle);
			patch_uint32(height, 0xBA354, exe->handle);
			break;
		case VER_FD109_04:
			patch_uint32(height, 0xB3CF, exe->handle);
			patch_uint32(height, 0xB3DA, exe->handle);
			patch_uint32(height, 0xB4B3, exe->handle);
			patch_uint32(height, 0xB4BE, exe->handle);
			patch_uint32(height, 0xDF354, exe->handle);
			break;
		case VER_FD109_04A:
			patch_uint32(height, 0xB61E, exe->handle);
			patch_uint32(height, 0xB629, exe->handle);
			patch_uint32(height, 0xB703, exe->handle);
			patch_uint32(height, 0xB70E, exe->handle);
			patch_uint32(height, 0xE3354, exe->handle);
			break;
		case VER_SRB2FUN:
			patch_uint32(height, 0xBB6A, exe->handle);
			patch_uint32(height, 0xBB75, exe->handle);
			patch_uint32(height, 0xBEF3, exe->handle);
			patch_uint32(height, 0xBEFE, exe->handle);
			patch_uint32(height, 0xF23A4, exe->handle);
			
			uint8 temp;
			
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
			break;
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