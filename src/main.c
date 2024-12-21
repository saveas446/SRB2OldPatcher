#include <stdio.h>
#include "types.h"


int main() {
	FILE * filehandle;
	
	filehandle = fopen("./SRB2WEEN.EXE", "rb+");
	if (filehandle == NULL) {
		perror("Error opening file");
		return 1;
	}
	
	fseek(filehandle, 0L, SEEK_END);
	printf("File size of exe is 0x%X",ftell(filehandle));
	return 0;
}