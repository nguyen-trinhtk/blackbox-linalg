#ifndef _LINBOX_CONFIG_H
#define _LINBOX_CONFIG_H 1
 
/* linbox/config.h. Generated automatically at end of configure. */
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef __LINBOX_AC_APPLE_UNIVERSAL_BUILD */

/* Define whether to compile in DEBUG mode */
/* #undef __LINBOX_DEBUG */

/* Define that architecture uses big endian storage */
/* #undef __LINBOX_HAVE_BIG_ENDIAN */

/* define if the compiler supports basic C++11 syntax */
#ifndef __LINBOX_HAVE_CXX11 
#define __LINBOX_HAVE_CXX11  1 
#endif

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifndef __LINBOX_HAVE_DLFCN_H 
#define __LINBOX_HAVE_DLFCN_H  1 
#endif

/* Define if FLINT is installed */
/* #undef __LINBOX_HAVE_FLINT */

/* Define to 1 if you have the <float.h> header file. */
#ifndef __LINBOX_HAVE_FLOAT_H 
#define __LINBOX_HAVE_FLOAT_H  1 
#endif

/* Define if FPLLL is installed */
/* #undef __LINBOX_HAVE_FPLLL */

/* ps2pdf available as external program */
/* #undef __LINBOX_HAVE_GHOSTSCRIPT */

/* gnuplot available as external program */
/* #undef __LINBOX_HAVE_GNUPLOT */

/* Define if IML is installed */
/* #undef __LINBOX_HAVE_IML */

/* Define that compiler allows int128_t types */
#ifndef __LINBOX_HAVE_INT128 
#define __LINBOX_HAVE_INT128  1 
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef __LINBOX_HAVE_INTTYPES_H 
#define __LINBOX_HAVE_INTTYPES_H  1 
#endif

/* Define if LAPACK is available */
/* #undef __LINBOX_HAVE_LAPACK */

/* Define to 1 if you have the <limits.h> header file. */
#ifndef __LINBOX_HAVE_LIMITS_H 
#define __LINBOX_HAVE_LIMITS_H  1 
#endif

/* Define that architecture uses little endian storage */
#ifndef __LINBOX_HAVE_LITTLE_ENDIAN 
#define __LINBOX_HAVE_LITTLE_ENDIAN  1 
#endif

/* Define if MAPLE is installed */
/* #undef __LINBOX_HAVE_MAPLE */

/* Define to 1 if you have the <memory.h> header file. */
#ifndef __LINBOX_HAVE_MEMORY_H 
#define __LINBOX_HAVE_MEMORY_H  1 
#endif

/* Define if MPFR is installed */
/* #undef __LINBOX_HAVE_MPFR */

/* Define if MPI is available */
/* #undef __LINBOX_HAVE_MPI */

/* Define if NTL is installed */
/* #undef __LINBOX_HAVE_NTL */

/* Define if OpenCL is installed */
/* #undef __LINBOX_HAVE_OCL */

/* Define to 1 if you have the <pthread.h> header file. */
#ifndef __LINBOX_HAVE_PTHREAD_H 
#define __LINBOX_HAVE_PTHREAD_H  1 
#endif

/* Define if SACLIB is installed */
/* #undef __LINBOX_HAVE_SACLIB */

/* Define to 1 if you have the <stddef.h> header file. */
#ifndef __LINBOX_HAVE_STDDEF_H 
#define __LINBOX_HAVE_STDDEF_H  1 
#endif

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef __LINBOX_HAVE_STDINT_H 
#define __LINBOX_HAVE_STDINT_H  1 
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#ifndef __LINBOX_HAVE_STDLIB_H 
#define __LINBOX_HAVE_STDLIB_H  1 
#endif

/* Define to 1 if you have the <strings.h> header file. */
#ifndef __LINBOX_HAVE_STRINGS_H 
#define __LINBOX_HAVE_STRINGS_H  1 
#endif

/* Define to 1 if you have the <string.h> header file. */
#ifndef __LINBOX_HAVE_STRING_H 
#define __LINBOX_HAVE_STRING_H  1 
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#ifndef __LINBOX_HAVE_SYS_STAT_H 
#define __LINBOX_HAVE_SYS_STAT_H  1 
#endif

/* Define to 1 if you have the <sys/time.h> header file. */
#ifndef __LINBOX_HAVE_SYS_TIME_H 
#define __LINBOX_HAVE_SYS_TIME_H  1 
#endif

/* Define to 1 if you have the <sys/types.h> header file. */
#ifndef __LINBOX_HAVE_SYS_TYPES_H 
#define __LINBOX_HAVE_SYS_TYPES_H  1 
#endif

/* Define if tinyxml2 is installed */
/* #undef __LINBOX_HAVE_TINYXML2 */

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef __LINBOX_HAVE_UNISTD_H 
#define __LINBOX_HAVE_UNISTD_H  1 
#endif

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#ifndef __LINBOX_LT_OBJDIR 
#define __LINBOX_LT_OBJDIR  ".libs/" 
#endif

/* define is the version of Maple have access function to gmp data */
/* #undef __LINBOX_MAPLE_GMP_ACCESS */

/* Name of package */
#ifndef __LINBOX_PACKAGE 
#define __LINBOX_PACKAGE  "linbox" 
#endif

/* Define to the address where bug reports for this package should be sent. */
#ifndef __LINBOX_PACKAGE_BUGREPORT 
#define __LINBOX_PACKAGE_BUGREPORT  "linbox-use@googlegroups.com" 
#endif

/* Define to the full name of this package. */
#ifndef __LINBOX_PACKAGE_NAME 
#define __LINBOX_PACKAGE_NAME  "LinBox" 
#endif

/* Define to the full name and version of this package. */
#ifndef __LINBOX_PACKAGE_STRING 
#define __LINBOX_PACKAGE_STRING  "LinBox 1.7.0" 
#endif

/* Define to the one symbol short name of this package. */
#ifndef __LINBOX_PACKAGE_TARNAME 
#define __LINBOX_PACKAGE_TARNAME  "linbox" 
#endif

/* Define to the home page for this package. */
#ifndef __LINBOX_PACKAGE_URL 
#define __LINBOX_PACKAGE_URL  "http://www.linalg.org/" 
#endif

/* Define to the version of this package. */
#ifndef __LINBOX_PACKAGE_VERSION 
#define __LINBOX_PACKAGE_VERSION  "1.7.0" 
#endif

/* The size of `char', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF_CHAR 
#define __LINBOX_SIZEOF_CHAR  1 
#endif

/* The size of `int', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF_INT 
#define __LINBOX_SIZEOF_INT  4 
#endif

/* The size of `long', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF_LONG 
#define __LINBOX_SIZEOF_LONG  8 
#endif

/* The size of `long long', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF_LONG_LONG 
#define __LINBOX_SIZEOF_LONG_LONG  8 
#endif

/* The size of `short', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF_SHORT 
#define __LINBOX_SIZEOF_SHORT  2 
#endif

/* The size of `__int64_t', as computed by sizeof. */
#ifndef __LINBOX_SIZEOF___INT64_T 
#define __LINBOX_SIZEOF___INT64_T  8 
#endif

/* Define to 1 if you have the ANSI C header files. */
#ifndef __LINBOX_STDC_HEADERS 
#define __LINBOX_STDC_HEADERS  1 
#endif

/* Version number of package */
#ifndef __LINBOX_VERSION 
#define __LINBOX_VERSION  "1.7.0" 
#endif

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif
 
/* once: _LINBOX_CONFIG_H */
#endif
