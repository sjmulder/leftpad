leftpad
=======
Pad a string to a desired length. Library & CLI.

Key features:
 - Highly portable.
 - No dependencies: CLI needs only libc, library is freestanding!
 - Detailed man(1) documentation for both the CLI and library.

Testimonials
------------

> Couldn't you just printf with a variable format string?

 ~ kartoffelwaffel on Reddit

> Thanks, I hate it

 ~ not_a_novel_account on Reddit

CLI
---
**leftpad** *string* *length* [*padding*]

**leftpad** outputs *padding* (or spaces if omitted) and *string*,
where *padding* is repeated or cut off as needed to make for a minimum
final string of *length* characters.

For example, to pad the string "5581" to 16 characters:

    $ leftpad 5581 16 '*'
    ************5581

Using **leftpad** to repeat a string:

    $ leftpad '' 40 _-
    _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

Library
-------
    #include <stddef.h>     /* for size_t */
    #include <leftpad.h>

    size_t
    leftpad(
        const char *str,
        const char *padding,
        size_t min_len,
        char *dest,
        size_t dest_sz);

**leftpad()** writes *padding* (or spaces if NULL or empty) and *str*
to *dest*, where *padding* is repeated or cut off as needed to make
for a minimum final string length of *min_len*.

If *dest* is NULL or *dest_sz* 0, nothing is written. Otherwise, up to
*dest_sz* characters are written, including the \0 terminator, possibly
truncating the output.

Rreturns the length of the output string. If less than *dest_sz*, the
output has not been truncated.

For example, to pad the string "5581" to 16 characters, assuming *buf*
is a character array of sufficient size:

    leftpad("5581", "*", 16, buf, sizeof(buf));
    puts(buf); /* outputs: ************5581 */

Using **leftpad()** to repeat a string:

    leftpad(NULL, "_-", 40, buf, sizeof(buf));
    puts(buf); /* outputs: _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- */

Calling **leftpad()** without a buffer to find out the required buffer
size:

    size_t len = leftpad(some_str, " ", 10);
    char *buf = malloc(len+1); /* +1 for terminating NUL */
    leftpad(some_str, " ", 10, buf, len+1);

Building
--------
The CLI requires only the C standard library. The library has no
dependencies.

A Makefile is provided for Unix systems such as Linux, BSD, and macOS.
To build, test, install, and uninstall:

    make
    make check
    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]

**Note:** to run **leftpad** without installing, it may be needed to set
LD_LIBRARY_PATH as follows:

    $ LD_LIBRARY_PATH=. leftpad

The following files are installed:

    bin/leftpad
    lib/libleftpad.so
    lib/libleftpad.a
    include/leftpad.h
    man/man1/leftpad.1
    man/man3/leftpad.3

Author
------
Sijmen J. Mulder (<ik@sjmulder.nl>)
