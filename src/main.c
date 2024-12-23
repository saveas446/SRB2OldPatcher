#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "init.h"
#include "patch.h"
#include "types.h"

const char* help_text = "Usage: srb2patcher [file] [options]\n"
                        "Options:\n"
                        "  -w, --window-width <width>          Set window width to any value between 1 and 9999\n"
                        "  -h, --window-height <height>         Set window height to any value between 1 and 9999\n"
                        "  -i, --iwad-checking <on/off>         Enable or disable IWAD checking (Final Demo 1.01 and up only)\n"
                        "  -d, --drm <on/off>            Enable or disable DRM (August 2008 or September 2008 1.1 betas only) \n"
                        "  -t, --window-title <title>          Set window title\n"
                        "  -p, --pause-text <text>           Set paused text\n"
                        "  -?, --help                  Display this help message\n";

int main(int argc, char** argv) {
	
	SRB2Executable exe;
	
	if (argc < 2) {
		puts(help_text);
		return EXIT_SUCCESS;		
	} 
	
	if (init_exe(&exe, argv[1])) {
		if (!file_not_found) {
			perror("init_exe failed");
			return EXIT_FAILURE;
		} else {
			puts(help_text);
			return EXIT_SUCCESS;	
		}
	}
	
	int i = 2;
	while (i < argc) {
		if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--window-width")) {
			patch_wwidth(&exe, atoi(argv[i+1]));
			i++;
		} else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--window-height")) {
			patch_wheight(&exe, atoi(argv[i+1]));
			i++;			
		} else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--iwad-checking")) {
			if (exe.version > VER_FD108_00 && exe.version < VER_AUG2008) {
				if (!strcmp(argv[i+1], "on")) {
					enable_iwad_chk(&exe);
				} else if (!strcmp(argv[i+1], "off")) {
					disable_iwad_chk(&exe);
				}				
			} else {
				puts("Version has no IWAD checking implemented\n");
			}				
			i++;			
		} else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--drm")) {
			if (exe.version == VER_AUG2008 || exe.version == VER_SEP2008) {
				if (!strcmp(argv[i+1], "on")) {
					enable_drm(&exe);
				} else if (!strcmp(argv[i+1], "off")) {
					disable_drm(&exe);
				}
			} else {
				puts("Version has no DRM implemented\n");
			}
			i++;			
		} else if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--window-title")) {
			patch_wtitle(&exe, argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--pause-text")) {
			patch_pausedtxt(&exe, argv[i+1]);
			i++;
		} else if (!strcmp(argv[i], "-?") || !strcmp(argv[i], "--help")) {
			puts(help_text);
		} else {
			printf("Unknown option: %s", argv[i]);
			return EXIT_SUCCESS;
		}
		i++;
	}
	
	fclose(exe.handle);
	
	return EXIT_SUCCESS;
}