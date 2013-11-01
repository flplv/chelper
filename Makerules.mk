#  This makefile build to Dev (host pc where you are sitting).
#  
#  To build to Dev it must be straightforward. Although to build the tests for dev you will need
#  the CppUTest framework compiled.
#  
#  To build to Target, you need to configure the gcc bin folder path, using TGT_GCC_PATH
#  variable, also, if you want the tests to run on target, you need to cross build the CppUTest.
#  
#  Makefiles with Tgt sufix are used to build to target, while the ones with Dev sufix, build to
#  the host pc.
#  
#  By reading and editing the makefiles you must be able to configure and build the chelper
#  for your needs.

BUILDTAG = $(shell git describe --all --long | tr "-" " " | awk '{ print $$2 "-" $$3 }')
FIRWMARE_VERSION = $(shell cat lib_version.txt)-$(shell date --iso)

### TOOL CHAIN ###

CC=cc
AR=ar
STRIP=strip

#TGT_GCC_PATH = $(shell cat ../../host_cfg/gcc-tgt-path.txt)
TGT_GCC_PATH = 
TGT_CC= arm-arago-linux-gnueabi-gcc
TGT_AR= arm-arago-linux-gnueabi-ar
TGT_STRIP= arm-arago-linux-gnueabi-strip

### SOURCES ###

SOURCE_FOLDER = src

SRC_DIRS = \
	src 

TEST_SRC_DIRS = \
	test/mocks \
	test
	
### PROJECT ###

TARGET = chelper
CPPUTEST_HOME = ./CppUTest

### TEST DEV CFG ###

TEST_DEV_CFLAGS = \
		-I$(CPPUTEST_HOME)/include/ -Iinclude -Isrc -g \
		-D AUTO_GEN_BUILD_TAG='"${BUILDTAG}"' \
		-D AUTO_GEN_FIRWMARE_VERSION='"${FIRWMARE_VERSION}"' \
		-D SYSTEM_UNIT_TEST 

TEST_DEV_LDFLAGS =
TEST_DEV_LDLIBS =				

### DEV CFG ###
				
DEV_CFLAGS = \
		-Iinclude \
		-D AUTO_GEN_BUILD_TAG='"${BUILDTAG}"' \
		-D AUTO_GEN_FIRWMARE_VERSION='"${FIRWMARE_VERSION}"' \
		
DEV_LDFLAGS = -fPIC
DEV_LDLIBS =	
	
