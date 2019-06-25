/* leftpad.h - Copyright (c) 2019, Sijmen J. Mulder (see LICENSE.md) */

/*
 * leftpad() - pad a string to a desired length
 *
 * Writes `padding` (or spaces if NULL or empty) and `str` (if not NULL) to
 * `dest`, where `padding` is repeated or cut of as needed to make for a
 * minimum final string length of `min_len`.
 *
 * If `dest` is NULL or `dest_sz` 0, nothing is written. Otherwise, up to
 * `dest_sz` characters are written, including the \0 terminator, possibly
 * truncating the output.
 *
 * Returns the length of the output string. If less than `dest_sz`, the output
 * has not bene truncated.
 */
size_t leftpad(
    const char *str,
    const char *padding,
    size_t min_len,
    char *dest,
    size_t dest_sz);
