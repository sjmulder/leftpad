/* tests.c - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

#include <string.h>
#include <assert.h>
#include "leftpad.h"

int
main()
{
	char buf[10];

	/* no padding needed */
	assert(leftpad("test", "*", 4, buf, 10) == 4);
	assert(strcmp("test", buf) == 0);

	/* padding is applied */
	assert(leftpad("test", "*", 9, buf, 10) == 9);
	assert(strcmp("*****test", buf) == 0);

	/* string is not truncated for lower target length */
	assert(leftpad("test", "*", 2, buf, 10) == 4);
	assert(strcmp("test", buf) == 0);

	/* padding is repeated */
	assert(leftpad("test", " .", 9, buf, 10) == 9);
	assert(strcmp(" . . test", buf) == 0);

	/* default padding is spaces */
	assert(leftpad("test", NULL, 9, buf, 10) == 9);
	assert(strcmp("     test", buf) == 0);

	/* default string is an empty string */
	assert(leftpad(NULL, "*", 9, buf, 10) == 9);
	assert(strcmp("*********", buf) == 0);

	/* doesn't write beyond buffer */
	assert(leftpad("test", "*", 11, buf, 10) == 9);
	assert(strcmp("*******te", buf) == 0);

	/* calucates required size if no buf or buf_sz given */
	assert(leftpad("test", " ", 2, NULL, 10) == 4);
	assert(leftpad("test", " ", 4, NULL, 10) == 4);
	assert(leftpad("test", " ", 6, NULL, 10) == 6);
	assert(leftpad("test", " ", 2, buf, 0) == 4);
	assert(leftpad("test", " ", 4, buf, 0) == 4);
	assert(leftpad("test", " ", 6, buf, 0) == 6);

	return 0;
}
