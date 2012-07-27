all: scan strip strip_sh strip_php chkbin

scan: scan.c
	gcc -Wall -O9 -lm -o scan scan.c

strip: strip.c
	gcc -Wall -O9 -lm -o strip strip.c

strip_php: strip_php.c
	gcc -Wall -O9 -lm -o strip_php strip_php.c

chkbin: chkbin.c
	gcc -Wall -O9 -lm -o chkbin chkbin.c
