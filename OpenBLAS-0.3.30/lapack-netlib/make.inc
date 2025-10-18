FC          = gfortran
override FFLAGS      = -O2 -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a -fno-tree-vectorize
FFLAGS_DRV  = -O2 -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a
POPTS       = -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a -pg -fno-inline
FFLAGS_NOOPT       = -O0 -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a
PNOOPT      = -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a -pg -fno-inline -O0
LDFLAGS     = -O2 -Wall -frecursive -fno-optimize-sibling-calls -fPIC -march=armv8-a -lpthread -lgfortran
CC          = cc
override CFLAGS      = -O2 -DMAX_STACK_ALLOC=2048 -Wall -DF_INTERFACE_GFORT -fPIC -DSMP_SERVER -DNO_WARMUP -DMAX_CPU_NUMBER=8 -DMAX_PARALLEL_NUMBER=1 -DBUILD_SINGLE=1 -DBUILD_DOUBLE=1 -DBUILD_COMPLEX=1 -DBUILD_COMPLEX16=1 -DVERSION="0.3.30" -march=armv8-a -UASMNAME -UASMFNAME -UNAME -UCNAME -UCHAR_NAME -UCHAR_CNAME -DASMNAME=_ -DASMFNAME=__ -DNAME=_ -DCNAME= -DCHAR_NAME="_" -DCHAR_CNAME="" -DNO_AFFINITY -I. -DHAVE_LAPACK_CONFIG_H
AR          = ar
ARFLAGS     =  -ru
RANLIB      = ranlib
LAPACKLIB   = ../../libopenblas_armv8p-r0.3.30.a
TMGLIB      = ../../../libopenblas_armv8p-r0.3.30.a
BLASLIB     = ../../../libopenblas_armv8p-r0.3.30.a
LAPACKELIB  = ../../../libopenblas_armv8p-r0.3.30.a
LAPACKLIB_P = ../libopenblas_armv8p-r0.3.30_p.a
SUFFIX      = o
PSUFFIX     = po
CEXTRALIB   = -lpthread -lgfortran
TIMER       = INT_ETIME
LOADER      = gfortran -pthread
BUILD_DEPRECATED      = 1
BUILD_SINGLE      = 1
BUILD_DOUBLE      = 1
BUILD_COMPLEX      = 1
BUILD_COMPLEX16      = 1
LAPACKE_WITH_TMG      = 1
SHELL = /bin/sh
PLAT = _LINUX
DRVOPTS  = $(NOOPT)
#ARCHFLAGS= $(ARFLAGS) -ru
#RANLIB   = ranlib

