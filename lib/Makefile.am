#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libchelper.la

#######################################
# Build information for each library

# Sources for libChelper
libchelper_la_SOURCES = fatal.c log.c my_string.c number.c ring_fifo.c signalslot.c signalslot2.c timeout.c vector.c

# Linker options libTestProgram
libchelper_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libchelper_la_CPPFLAGS = -I$(top_srcdir)/include

