#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// skip comment
int skip(FILE *fp) {
	int c = fgetc(fp);
	
	if(c == '/') {
		// single line comment
		while( c != EOF && (c=fgetc(fp)) != '\n') {
			if(c == '\\') {
				c = fgetc(fp);  // \\\n = void
			}
		}
		if(c!=EOF) return '\n';
		
	} else if(c == '*') {
		// multi line comment
		do {
			while( c != EOF && (c=fgetc(fp)) != '*') {
				// none
			}
		} while(c != EOF &&  (c=fgetc(fp)) != '/');
		if(c!=EOF) return 0;
	} else {
		if(c != EOF) c = c | ('/' << 8);
	}
	return c;
}

// main
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
			fprintf(stderr, "Cannot open file\n");
			return 2;
		}
		isfile = 1;
	} else {
		fp = stdin;
	}
	
	// scan
	while(1) {
		c = fgetc(fp);
		if(c == EOF) break;
		
		// skip comment
		if(c == '/') {
			c = skip(fp);
			if(c == EOF) break;
			if(c == 0) continue;
			if(c > 0x0FF) {
				putchar('/');
				c = c & 0x0FF;
			}
		}
		
		// output
		putchar(c);
	}
	
	// check error
	if(ferror(fp)) fprintf(stderr, "Read error\n");
	
	// close file
	if(isfile) fclose(fp);
	
	return 0;
}
