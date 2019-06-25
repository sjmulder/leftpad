/* leftpad.c - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

#include <stddef.h>
#include "leftpad.h"

size_t
leftpad(const char *str, const char *padding, size_t min_len, char *dest,
    size_t dest_sz)
{
	size_t i = 0;
	size_t str_len = 0;
	size_t dest_len = 0;
	size_t npad = 0;

	while (str && str[str_len])
		str_len++;
	if (!padding || !padding[0])
		padding = " ";
	if (str_len < min_len)
		npad = min_len - str_len;
	if (!dest || !dest_sz)
		return str_len + npad;
	while (dest_len < npad && dest_len < dest_sz - 1)
		if (!(dest[dest_len++] = padding[i++])) {
			dest[dest_len-1] = padding[0];
			i = 1;
		}
	for (i = 0; i < str_len && dest_len < dest_sz - 1; i++)
		dest[dest_len++] = str[i];
	dest[dest_len] = '\0';

	return dest_len;
}
