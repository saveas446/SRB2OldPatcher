#include <stdio.h>
#include "md5.h"
#include "types.h"

typedef enum exe_version {
	VER_WEEN132,
	VER_XMAS096,
	VER_DEMO1_00,
	VER_DEMO2_00,
	VER_DEMO3_00,
	VER_DEMO4_00,
	VER_DEMO4_10,
	VER_DEMO4_32,
	VER_DEMO4_35,
	VER_FD101_00,
	VER_FD102_00,
	VER_FD103_00,
	VER_FD104_00,
	VER_FD108_00,
	VER_FD109_00,
	VER_FD109_02,
	VER_FD109_04,
	VER_FD109_04A,
	VER_SRB2FUN,
	VER_AUG2008,
	VER_SEP2008
} exe_version;

typedef struct SRB2Executable {
	FILE * handle;
	uint32 size;
	uint8 checksum[16];
	exe_version version;
} SRB2Executable;

int main(int argc, char** argv) {
	
	SRB2Executable exe;
	
	if (argc < 2) {
		perror("No file specified\n");
		return 1;			
	} else if (argc > 2) {
		perror("Too many arguments\n");
		return 1;			
	}
	
	exe.handle = fopen(argv[1], "rb+");
	if (exe.handle == NULL) {
		perror("Error opening file");
		return 1;
	}
	
	// Get file checksum
	md5File(exe.handle, exe.checksum);
	
    /*uint8_t baked_in_checksums[][MD5_DIGEST_LENGTH] = {
        {0xB7, 0x20, 0x7E, 0x9F, 0x02, 0xB4, 0x9C, 0xB6, 0xD6, 0x10, 0x27, 0x0B, 0x26, 0x7C, 0x95, 0x07},
        {0x2a, 0x3b, 0x4c, 0x5d, 0x6e, 0x7f, 0x8g, 0x9h, 0x10, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27},
    };
	
    size_t num_checksums = sizeof(baked_in_checksums) / sizeof(baked_in_checksums[0]);

    // Compare the computed checksum with each baked-in checksum
    int checksum_found = 0;
    for (size_t i = 0; i < num_checksums; i++) {
        if (memcmp(exe.checksum, baked_in_checksums[i], MD5_DIGEST_LENGTH) == 0) {
            checksum_found = 1;
            break;
        }
    }*/
		
	
	return 0;
}