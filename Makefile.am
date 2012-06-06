# Library.
lib_LTLIBRARIES = liblogcount.la
liblogcount_la_LIBADD = -lcrypto -lm
liblogcount_la_SOURCES = logcount.c
liblogcount_la_LDFLAGS = -version-info $(LOGCOUNT_LTVERSION)

include_HEADERS = logcount.h

# Unit tests
logcount_test_SOURCES = logcount_test.c
logcount_test_LDADD = liblogcount.la $(UNITTEST_LIBS)
TESTS = logcount_test
noinst_PROGRAMS = $(TESTS)

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
