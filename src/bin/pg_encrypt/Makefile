# src/bin/pg_encrypt/Makefile

PGFILEDESC = "pg_encrypt - encrpt .pgpass"
PGAPPICON = win32

subdir = src/bin/pg_encrypt
top_builddir = ../../..
include $(top_builddir)/src/Makefile.global

OBJS = \
	$(WIN32RES) \
	pg_encrypt.o

all: pg_encrypt

pg_encrypt: $(OBJS) | 
	$(CC) $(CFLAGS)  $^ $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)

install: all installdirs
	$(INSTALL_PROGRAM) pg_encrypt$(X) '$(DESTDIR)$(bindir)/pg_encrypt$(X)'

installdirs:
	$(MKDIR_P) '$(DESTDIR)$(bindir)'

check:
	$(prove_check)

installcheck:
	$(prove_installcheck)

uninstall:
	rm -f '$(DESTDIR)$(bindir)/pg_encrypt$(X)'

clean distclean maintainer-clean:
	rm -f pg_encrypt$(X) $(OBJS)
	rm -rf pg_encrypt
