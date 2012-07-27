// 2012.07.20  6:32 -
// 2012.07.20  6:39 /
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_LEN 4096

int main(int ac, char *av[]) {
	FILE *fp;
	char buf[BUF_LEN+64], *s, *word=NULL, *num;
	int i, isfile;
	double bias;
	
	// check args
	if(ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s [filename] bias\n", av[0]);
		return 1;
	}
	
	// open stream
	if(ac >= 2) {
		fp = fopen(av[1], "rb");
		if(fp == NULL) {
			fprintf(stderr, "Cannot open file: %s\n", av[1]);
			return 2;
		}
		isfile = 1;
		if(ac >= 3) {
			bias = atof(av[2]);
		}
	} else {
		fp = stdin;
	}
	
	for(i=1;;i++) {
		if(fgets(buf, BUF_LEN, fp) == NULL) break;
		for(s=buf,word=num=NULL; *s; s++) {
			if(*s == '\t' || *s == ' ') {
				*s = 0;
				num = buf;
				word = s+1;
				break;
			}
		}
		if(word && num) {
			printf("%.10f %s", atof(num) * bias, word);
		}
	}
	
	// close file
	if(isfile) fclose(fp);
	
	return 0;
}
