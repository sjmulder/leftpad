DESTDIR   ?=
PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/man

CFLAGS += -Wall -Wextra

all: leftpad libleftpad.so libleftpad.a

check: leftpad tests
	LD_LIBRARY_PATH=. ./leftpad test 10 >/dev/null
	LD_LIBRARY_PATH=. ./tests

clean:
	rm -f leftpad tests libleftpad.so libleftpad.a
	rm -f leftpad.o main.o tests.o

install: all
	install -d $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(PREFIX)/lib
	install -d $(DESTDIR)$(PREFIX)/include
	install -d $(DESTDIR)$(MANPREFIX)/man1
	install -d $(DESTDIR)$(MANPREFIX)/man3
	install -m755 leftpad       $(DESTDIR)$(PREFIX)/bin
	install -m755 libleftpad.so $(DESTDIR)$(PREFIX)/lib
	install -m644 libleftpad.a  $(DESTDIR)$(PREFIX)/lib
	install -m644 leftpad.h     $(DESTDIR)$(PREFIX)/include
	install -m644 leftpad.1     $(DESTDIR)$(MANPREFIX)/man1
	install -m644 leftpad.3     $(DESTDIR)$(MANPREFIX)/man3

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/leftpad
	rm -f $(DESTDIR)$(PREFIX)/lib/libleftpad.so
	rm -f $(DESTDIR)$(PREFIX)/lib/libleftpad.a
	rm -f $(DESTDIR)$(PREFIX)/include/leftpad.h
	rm -f $(DESTDIR)$(MANPREFIX)/man1/leftpad.1
	rm -f $(DESTDIR)$(MANPREFIX)/man3/leftpad.3

leftpad: main.o libleftpad.so
	$(CC) $(LDFLAGS) -L. -o leftpad main.o -lleftpad

libleftpad.so: leftpad.o
	$(CC) $(LDFLAGS) -shared -nostdlib -o libleftpad.so leftpad.o

libleftpad.a: leftpad.o
	$(AR) $(ARFLAGS) libleftpad.a leftpad.o

leftpad.o: leftpad.c
	$(CC) $(CFLAGS) -c -fPIC -o leftpad.o leftpad.c

tests: tests.o libleftpad.so
	$(CC) $(LDFLAGS) -L. -o tests tests.o -lleftpad

leftpad.o:	leftpad.h
main.o:		leftpad.h
tests.o:	leftpad.h

.PHONY: all check clean install uninstall
