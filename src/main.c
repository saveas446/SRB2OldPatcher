#include <stdio.h>
#include "md5.h"
#include "tables.h"
#include "types.h"

static const char *help_text = 
"\nUsage: SRB2Patcher filename [options]\n"
"Options:\n\n"
"-w: Changes window width to any value between 1 and 9999.\n"
"-h: Changes window height to any value between 1 and 9999.\n"
"-i: Enables or disables checking the IWAD files for modification. Final Demo 1.01 and up only.\n"
"-d: Enables or disables the DRM functions. August 2008 or September 2008 1.1 betas only.\n"
"-t: Changes the window title.\n"
"-p: Changes the text shown when not focused on the window in windowed mode.\n"
"-?: Displays this text.\n";

int init_exe(SRB2Executable* exe, char* filename) {
	exe->handle = fopen(filename, "rb+");
	if (exe->handle == NULL) {
		return EXIT_FAILURE;
	}
	
	// Get file checksum
	md5File(exe->handle, exe->checksum);
	
    size_t num_checksums = sizeof(baked_in_checksums) / sizeof(baked_in_checksums[0]);

    // Compare the computed checksum with each baked-in checksum
    int checksum_found = 0;
    for (size_t i = 0; i < num_checksums; i++) {
        if (memcmp(exe->checksum, baked_in_checksums[i], MD5_DIGEST_LENGTH) == 0) {
			exe->version = i;
            break;
        }
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

SRB2Executable exe;

int main(int argc, char** argv) {
	
	if (argc < 2) {
		perror("No file specified");
		return EXIT_FAILURE;		
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