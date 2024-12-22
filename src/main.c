#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "patch.h"
#include "types.h"


const char* help_text = "Usage: program [options]\n"
                        "Options:\n"
                        "  -w <width>          Set window width to any value between 1 and 9999\n"
                        "  -h <height>         Set window height to any value between 1 and 9999\n"
                        "  -i <on/off>         Enable or disable IWAD checksums (Final Demo 1.01 and up only)\n"
                        "  -d <drm>            Enable or disable DRM (August 2008 or September 2008 1.1 betas only) \n"
                        "  -t <title>          Set window title\n"
                        "  -p <text>           Set paused text\n"
                        "  -?                  Display this help message\n";

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
			patch_wwidth(&exe, atoi(argv[i+1]));
			i++;
		} else if (!strcmp(argv[i], "-h")) {
			patch_wheight(&exe, atoi(argv[i+1]));
			i++;			
		} else if (!strcmp(argv[i], "-i")) {
			printf("Set IWAD checksums to %s\n", argv[i+1]);
			i++;			
		} else if (!strcmp(argv[i], "-d")) {
			printf("Set DRM to %s\n", argv[i+1]);
			i++;			
		} else if (!strcmp(argv[i], "-t")) {
			patch_wtitle(&exe, argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-p")) {
			patch_pausedtxt(&exe, argv[i+1]);
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