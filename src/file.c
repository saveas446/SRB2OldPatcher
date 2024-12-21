#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"


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

int patch_uint32(uint32 value, uint32 address, FILE *file) {
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

	fseek(file, address, SEEK_SET);
	
    if (fwrite(&value, sizeof(uint32), 1, file) != 1) {
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int patch_uint16(uint16 value, uint32 address, FILE *file) {
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

	fseek(file, address, SEEK_SET);
	
    if (fwrite(&value, sizeof(uint16), 1, file) != 1) {
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int patch_byte(uint8 value, uint32 address, FILE *file) {
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

	fseek(file, address, SEEK_SET);
	
    if (fwrite(&value, sizeof(uint8), 1, file) != 1) {
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int replace_string_at_offset(char* string, uint32 address, FILE *file) {

    size_t data_length = strlen(string);

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fseek(file, address, SEEK_SET);
	
    if (fwrite(string, sizeof(char), data_length, file) != data_length) {
        perror("Error writing to file");
        return EXIT_FAILURE;
    }

    char null_terminator = '\0';
    fwrite(&null_terminator, sizeof(char), 1, file);
    return EXIT_SUCCESS;
}