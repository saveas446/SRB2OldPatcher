#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "patch.h"
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
			patch_wwidth(&exe, atoi(argv[i+1]));
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
	
	fclose(exe.handle);
	
	return EXIT_SUCCESS;
}