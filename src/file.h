#pragma once

#include "types.h"

int read_file_segment(FILE* file, uint32 start_address, uint32 end_address, char* out);
int read_byte(uint32 address, FILE *file, uint8 *out);

int patch_uint32(uint32 value, uint32 address, FILE *file);
int patch_uint16(uint16 value, uint32 address, FILE *file);
int patch_byte(uint8 byte, uint32 address, FILE *file);
int memcpy_to_file(uint32 address, void *src, size_t n, FILE *file);