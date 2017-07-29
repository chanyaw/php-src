dnl $Id$
dnl config.m4 for extension mystr

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mystr, for mystr support,
dnl Make sure that the comment is aligned:
dnl [  --with-mystr             Include mystr support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(mystr, whether to enable mystr support,
Make sure that the comment is aligned:
[  --enable-mystr           Enable mystr support])

if test "$PHP_MYSTR" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mystr -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mystr.h"  # you most likely want to change this
  dnl if test -r $PHP_MYSTR/$SEARCH_FOR; then # path given as parameter
  dnl   MYSTR_DIR=$PHP_MYSTR
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mystr files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MYSTR_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MYSTR_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mystr distribution])
  dnl fi

  dnl # --with-mystr -> add include path
  dnl PHP_ADD_INCLUDE($MYSTR_DIR/include)

  dnl # --with-mystr -> check for lib and symbol presence
  dnl LIBNAME=mystr # you may want to change this
  dnl LIBSYMBOL=mystr # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYSTR_DIR/$PHP_LIBDIR, MYSTR_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MYSTRLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mystr lib version or lib not found])
  dnl ],[
  dnl   -L$MYSTR_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MYSTR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mystr, mystr.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
