// 2012.07.20  6:55 -
// 2012.07.20  6:55 /
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_LEN 4096

int main(int ac, char *av[]) {
	FILE *fp;
	char buf[BUF_LEN+64], _word[BUF_LEN+64], *s, *word=NULL, *num;
	int i, isfile;
	double total;
	
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
	
	total = 0;
	for(i=1;;i++) {
		if(word) strcpy(_word, word);
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
			if(strcmp(_word, word) == 0) {
				total += atof(num);
			} else {
				// break point
				if(total) printf("%.10f %s", total, _word);
				total = atof(num);
			}
		}
	}
	
	// close file
	if(isfile) fclose(fp);
	
	return 0;
}
