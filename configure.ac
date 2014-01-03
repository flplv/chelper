dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(chelper, 1.0)
AC_PROG_CC

AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL
AC_PROG_CXX

AC_LANG_PUSH([C++])
AC_CHECK_LIB([CppUTest], 
	     [cpputest_malloc],
             [HAVE_CPPUTEST=1],
             [[HAVE_CPPUTEST=0],
             AC_MSG_WARN([CppUTest not found, tests won't be built.])]
		)
AC_LANG_POP([C++])

AM_CONDITIONAL(COND_HAVE_CPPUTEST, [test x$HAVE_CPPUTEST = x1])

AC_CONFIG_FILES(Makefile
                test/Makefile
                lib/Makefile
                include/Makefile)
AC_OUTPUT
