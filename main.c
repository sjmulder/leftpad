/* main.c - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

#include <stdio.h>
#include <stdlib.h>

#ifdef __OpenBSD__
# include <unistd.h>
#endif

#include "leftpad.h"

int
main(int argc, char **argv)
{
	long min_len;
	const char *padding = " ";
	char *end;
	char *buf;
	size_t buf_len;

#ifdef __OpenBSD__
	if (pledge("stdio", NULL) == -1) {
		fputs("leftpad: pledge() failed\n", stderr);
		return 0;
	}
#endif

	if (argc == 4)
		padding = argv[3];
	else if (argc != 3) {
		fputs("usage: leftpad string length [padding]\n", stderr);
		return 1;
	}

	min_len = strtol(argv[2], &end, 10);
	if (!argv[2][0] || end[0] || min_len < 0) {
		fputs("leftpad: invalid length", stderr);
		return 1;
	}

	buf_len = leftpad(argv[1], padding, min_len, NULL, 0);
	if (!(buf = malloc(buf_len))) {
		fputs("leftpad: out of memory", stderr);
		return 1;
	}

	leftpad(argv[1], padding, min_len, buf, buf_len+1);
	puts(buf);
	return 0;
}
