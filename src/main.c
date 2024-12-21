#include <stdio.h>
#include "types.h"

static const char *help_text = 
"\nPatches pre-2.0 versions of SRB2.\n"
"Usage: SRB2Patcher filename [options]\n"
"Options:\n\n"
"-w: Changes window width to any value between 1 and 9999.\n"
"-h: Changes window height to any value between 1 and 9999.\n"
"-i: Enables or disables checking the IWAD files for modification. Final Demo 1.01 and up only.\n"
"-d: Enables or disables the DRM functions. August 2008 or September 2008 1.1 betas only.\n"
"-t: Changes the window title.\n"
"-p: Changes the text shown when not focused on the window in windowed mode.\n"
"-?: Displays this text.\n";

char* read_file_segment(FILE* file, uint32 start_address, uint32 end_address) {
    size_t segment_size = end_address - start_address + 1;

    char *buffer = (char *)malloc(segment_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        return NULL;
    }


    if (fseek(file, start_address, SEEK_SET) != 0) {
        perror("Error seeking file");
        fclose(file);
        free(buffer);
        return NULL;
    }

    if (fread(buffer, sizeof(char), segment_size, file) != segment_size) {
        perror("Error reading file");
        fclose(file);
        free(buffer);
        return NULL;
    }
    buffer[segment_size] = '\0';
    return buffer;
}

int init_exe(SRB2Executable* exe, char* filename) {
	exe->handle = fopen(filename, "rb+");
	if (exe->handle == NULL) {
		return EXIT_FAILURE;
	}
	
	char* ver_strings [NUM_VERSIONS] {
		"21:44:29 Sep 23 2000",
		"18:03:05 Mar 19 2003", // All the copies of Xmas 0.96 I could find have this. Weird.
		"14:46:55 Nov  8 2000",
		"13:19:30 Mar  1 2001",
		"18:46:34 Jun 20 2001",
		"10:18:27 Dec 25 2001",
		"13:59:06 Jan  6 2002",
		"20:59:16 Mar  8 2002",
		"19:31:11 Mar 18 2002",
		"16:45:04 Mar 10 2003",
		"Ò÷ð", // fd 1.01
		"™áñ", // fd 1.02
		"13:58:48 Jun 19 2003", // fd 1.03
		"20:10:23 Jun 21 2003", // fd 1.04
		"10:38:20 Jan  2 2004",
		"21:50:26 Sep 11 2005",
		"13:30:06 Jan  7 2006",
		"Aug 22 2006",
		"Feb 17 2008",
		"srb2fun Beta Mar  2 2008",
		"v1.1 Private Beta Aug 22 2008",
		"v1.1 Private Beta Sep 24 2008"
	}
	
	uint32 ver_addresses [NUM_VERSIONS] [2] {
		{0x06DB5F, 0x06DB72},
		{0x071917, 0x07192A},
		{0x073D33, 0x073D46},
		{0x07CBE7, 0x07CBFA},
		{0x06DB5F, 0x06DB72},
		{0x07ACCF, 0x07ACE2},
		{0x07AEEF, 0x07AF02},
		{0x07AEEF, 0x07AF02},
		{0x090264, 0x090277}, // jump from legacy 1.30 to 1.32
		{0x08F268, 0x08F27B},
		{0x095CC8, 0x095CDB},
		{0x092364, 0x092366}, // fd 1.01
		{0x092364, 0x092366}, // fd 1.02
		{0x09FE38, 0x09FE4B},
		{0x09FE40, 0x09FE53},
		{0x0AA3F0, 0x0AA403},
		{0x0A6798, 0x0A67AB}, // fd 1.09.2
		{0x0C25D8, 0x0C25E2}, 
		{0x0C6558, 0x0C6562}, 
		{0x0E6040, 0x0E6057}, 
		{0x14AD27, 0x14AD43}, // debuggggg aug 2008
		{0x0E830A, 0x0E6327}, // sep 2008
	}
	
	// TODO improve this
	
	
	
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