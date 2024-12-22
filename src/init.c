#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "tables.h"
#include "types.h"

bool file_not_found;

int init_exe(SRB2Executable* exe, char* filename) {
	exe->handle = fopen(filename, "rb+");
	if (exe->handle == NULL) {
		file_not_found = TRUE;
		return EXIT_FAILURE;
	}
	
	file_not_found = FALSE;
	
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
					printf("EXE version identified as %s\n", ver_names[i]);
					version_found = TRUE;
					exe->version = i;
					break;
				} else if (byte == 73 && i == VER_FD102_00) {
					printf("EXE version identified as %s\n", ver_names[i]);
					version_found = TRUE;	
					exe->version = i;
					break;
				}
				
			}

			
		} else {
			read_file_segment(exe->handle, ver_addresses[i][0], ver_addresses[i][1], buffer);
			if(!strcmp(buffer, ver_strings[i])) {
				printf("EXE version identified as %s\n", ver_names[i]);
				version_found = TRUE;
				exe->version = i;
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