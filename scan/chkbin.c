#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_LEN 4096

int main(int ac, char *av[]) {
	FILE *fp;
	int c;
	int isfile = 0;
	
	// check args
	if(ac != 1 && ac != 2) {
		fprintf(stderr, "Usage: %s filename\n", av[0]);
		return 1;
	}
	
	// open stream
	if(ac == 2) {
		fp = fopen(av[1], "rb");
		if(fp == NULL) {
			fprintf(stderr, "Cannot open file: %s\n", av[1]);
			return 2;
		}
		isfile = 1;
	} else {
		fp = stdin;
	}
	
	// scan
	while(1) {
		c = fgetc(fp);
		if(c == EOF) {
			if(ferror(fp)) fprintf(stderr, "Read error: %s\n", av[1]);
			break;
		}
		if( c >= 0 && c < 0x20 && c != 0x9  && c != 0xA && c != 0xD ) {
			if(isfile) fprintf(stderr, "found binary(0x%02X):%s\n", c, av[1]);
			else       fprintf(stderr, "found binary(0x%02X)\n", c);
			break;
		}
	}
	
	// close file
	if(isfile) fclose(fp);
	
	return 0;
}
