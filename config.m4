dnl $Id$
dnl config.m4 for extension extdemo

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(extdemo, for extdemo support,
dnl Make sure that the comment is aligned:
dnl [  --with-extdemo             Include extdemo support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(extdemo, whether to enable extdemo support,
dnl Make sure that the comment is aligned:
dnl [  --enable-extdemo           Enable extdemo support])

if test "$PHP_EXTDEMO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-extdemo -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/extdemo.h"  # you most likely want to change this
  dnl if test -r $PHP_EXTDEMO/$SEARCH_FOR; then # path given as parameter
  dnl   EXTDEMO_DIR=$PHP_EXTDEMO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for extdemo files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       EXTDEMO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$EXTDEMO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the extdemo distribution])
  dnl fi

  dnl # --with-extdemo -> add include path
  dnl PHP_ADD_INCLUDE($EXTDEMO_DIR/include)

  dnl # --with-extdemo -> check for lib and symbol presence
  dnl LIBNAME=extdemo # you may want to change this
  dnl LIBSYMBOL=extdemo # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EXTDEMO_DIR/$PHP_LIBDIR, EXTDEMO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_EXTDEMOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong extdemo lib version or lib not found])
  dnl ],[
  dnl   -L$EXTDEMO_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(EXTDEMO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(extdemo, extdemo.c, $ext_shared)
fi
