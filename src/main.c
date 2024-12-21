#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"
#include "types.h"

static const char *help_text = 
"\nPatches pre-2.0 versions of SRB2.\n\n"
"Usage: SRB2Patcher filename [options]\n"
"Options:\n\n"
"-w: Changes window width to any value between 1 and 9999.\n"
"-h: Changes window height to any value between 1 and 9999.\n"
"-i: Enables or disables checking the IWAD files for modification. Final Demo 1.01 and up only.\n"
"-d: Enables or disables the DRM functions. August 2008 or September 2008 1.1 betas only.\n"
"-t: Changes the window title.\n"
"-p: Changes the text shown when not focused on the window in windowed mode.\n"
"-?: Displays this text.\n";

int read_file_segment(FILE* file, uint32 start_address, uint32 end_address, char* out) {
    size_t segment_size = end_address - start_address + 1;
	
	if (fseek(file, start_address, SEEK_SET) != 0) {
        perror("Error seeking file");
        return EXIT_FAILURE;
    }

    fread(out, sizeof(char), segment_size, file);
	out[segment_size] = '\0';
    return EXIT_SUCCESS;
}

int init_exe(SRB2Executable* exe, char* filename) {
	exe->handle = fopen(filename, "rb+");
	if (exe->handle == NULL) {
		return EXIT_FAILURE;
	}
	
	bool version_found = FALSE;
	
	char buffer[128];
	
	for (int i = 0; i < NUM_VERSIONS; i++) {
		
		// Final Demo 1.01 and 1.02 are annoying and thus need their own way of comparing.
		
		if (i == VER_FD101_00 || i == VER_FD102_00) { 
			
			//Check if the file has the FD1.01/FD1.02 timestamp
			read_file_segment(exe->handle, 0x9FE38, 0x9FE4B, buffer);
			if(!strcmp(buffer, "19:23:11 Jun 18 2003")) {
				
				//spaghetiiiiii
				fseek(exe->handle, 0x91942, SEEK_SET);
				uint8 byte;
				fread(&byte, sizeof(uint8), 1, exe->handle);
				if (byte == 70 && i == VER_FD101_00) {
					printf("EXE version identified as %s", ver_names[i]);
					version_found = TRUE;
					break;
				} else if (byte == 73 && i == VER_FD102_00) {
					printf("EXE version identified as %s", ver_names[i]);
					version_found = TRUE;	
					break;
				}
				
			}

			
		} else {
			read_file_segment(exe->handle, ver_addresses[i][0], ver_addresses[i][1], buffer);
			if(!strcmp(buffer, ver_strings[i])) {
				printf("EXE version identified as %s", ver_names[i]);
				version_found = TRUE;
				break;
			}			
		}
	}
	
	if (!version_found) {
		perror("Unable to find version\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

int patch_byte_in_file(FILE* file, uint32 index, uint8 byte) {
	if (fseek(file, index, SEEK_SET) != 0) { 
		perror("Error seeking file"); 
		return EXIT_FAILURE; 
	}
	fwrite(&byte, sizeof(uint8), 1, file);
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	
	SRB2Executable exe;
	
	if (argc < 2) {
		printf(help_text);
		return EXIT_SUCCESS;		
	} 
	
	if (init_exe(&exe, argv[1])) {
		perror("init_exe failed");
		return EXIT_FAILURE;
	}
	
	int i = 2;
	while (i < argc) {
		if (!strcmp(argv[i], "-w")) {
			printf("Set window width to %s\n", argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-h")) {
			printf("Set window height to %s\n", argv[i+1]);
			i++;			
		} else if (!strcmp(argv[i], "-i")) {
			printf("Set IWAD checksums to %s\n", argv[i+1]);
			i++;			
		} else if (!strcmp(argv[i], "-d")) {
			printf("Set DRM to %s\n", argv[i+1]);
			i++;			
		} else if (!strcmp(argv[i], "-t")) {
			printf("Set window title to %s\n", argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-p")) {
			printf("Set text shown when game is paused to %s\n", argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-?")) {
			printf(help_text);
		} else {
			printf("Unknown option: %s", argv[i]);
			return EXIT_SUCCESS;
		}
		i++;
	}
	
	return EXIT_SUCCESS;
}