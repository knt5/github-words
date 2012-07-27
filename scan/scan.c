#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_LEN 4096
#define ITEM_MAX 100000000

struct ITEM {
	char *word;
	unsigned int num;
};

int length = 0;

void add(char *buf, struct ITEM **list) {
	int min=0, max=length-1, found=0, mid=0, l;
	struct ITEM *item;
	
	// binary search
	while(max >= min) {
		mid = (min + max) / 2;
		if( strcmp(list[mid]->word, buf) < 0 ) {
			min = mid + 1;
		} else if(strcmp(list[mid]->word, buf) > 0) {
			max = mid - 1;
		} else {
			found = 1;
			break;
		}
	}
	
	// found
	if(found) {
		list[mid]->num ++;
		return;
	}
	
	// check length
	if(length >= ITEM_MAX) {
		fprintf(stderr, "No more memory, cannot add: %s\n", buf);
		return;
	}
	
	// shift
	memmove(list+min+1, list+min, (length-min) * sizeof(struct ITEM*));
	
	// copy
	item = (struct ITEM*)malloc(sizeof(struct ITEM));
	l = strlen(buf) + 1;
	item->word = (char*)malloc(l);
	item->num = 1;
	memcpy(item->word, buf, l);
	
	// add
	list[min] = item;
	length++;
	
	return;
}

int main(int ac, char *av[]) {
	FILE *fp;
	char buf[BUF_LEN+64], *s;
	int c, l, b, i;
	int isfile = 0;
	struct ITEM** list;
	
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
	
	// memory alloc
	l = sizeof(struct ITEM*) * ITEM_MAX;
	list = (struct ITEM**)malloc(l);
	memset(list, 0, l);
	
	// scan
	s = buf;
	b = 0;
	l = 0;
	while(1) {
		c = fgetc(fp);
		if(c == EOF) {
			if(ferror(fp)) fprintf(stderr, "Read error: %s\n", av[1]);
			break;
		}
		if( ('a' <= c && c <= 'z')
		 || ('A' <= c && c <= 'Z')
		 || ('0' <= c && c <= '9')
		) {
			if(b == 0) b = 1;
			*s = c;
			s++;
			l++;
			if(l > BUF_LEN) {  // search cancel
				s = buf;
				b = 0;
				l = 0;
			}
		} else {
			if(b) {  // break point
				*s = 0;
				if(l) add(buf, list);
				s = buf;
				b = 0;
				l = 0;
			}
		}
	}
	
	// close file
	if(isfile) fclose(fp);
	
	// print
	for(i=0; i<ITEM_MAX && list[i]; i++) {
		printf("%d %s\n", list[i]->num, list[i]->word);
	}
	
	// free : not required
	//free(list);
	
	return 0;
}
