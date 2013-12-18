include  $(top_srcdir)/PreRules.am

#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=chelper-test

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=chelpertest

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
chelpertest_SOURCES= test_main.cpp fast_ring_fifo_test.cpp log_test.cpp my_string_text.cpp ring_fifo_test.cpp signalslot_test.cpp timeout_test.cpp vector_test.cpp 

# Linker options for a.out
chelpertest_LDFLAGS = -L$(top_builddir)/lib -lchelper -lCppUTest

# Compiler options for a.out
chelpertest_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib -include CppUTest/MemoryLeakDetectorNewMacros.h -DSYSTEM_UNIT_TEST
chelpertest_CXXFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/lib -include CppUTest/MemoryLeakDetectorNewMacros.h -DSYSTEM_UNIT_TEST