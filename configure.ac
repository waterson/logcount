m4_define([logcount_major], [0])
m4_define([logcount_minor], [0])
m4_define([logcount_patchleve], [0])

# Libtool shared library interface versions (current:revision:age)
# Update this value for every release!  (A:B:C will map to foo.so.(A-C).C.B)
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
m4_define([logcount_ltversion], [0:0:0])

AC_INIT([logcount], [logcount_major.logcount_minor.logcount_patchlevel])
AM_INIT_AUTOMAKE([-Wall -Werror])

LT_INIT
AC_SUBST([LIBTOOL_DEPS])
AC_CHECK_HEADERS([stddef.h openssl/md5.h])

AC_SUBST([LOGCOUNT_LTVERSION], logcount_ltversion)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
