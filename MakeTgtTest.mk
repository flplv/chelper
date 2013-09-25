include Makerules.mk

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = $(TARGET)-tgt-test
TARGET_LIB = \
	lib/lib_$(COMPONENT_NAME).a

CPPUTEST_OBJS_DIR = obj_tgt_test
	
TEST_TARGET = \
	$(COMPONENT_NAME)

#--- Inputs ---#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

CXX = arm-arago-linux-gnueabi-g++
CC = arm-arago-linux-gnueabi-gcc
AR = arm-arago-linux-gnueabi-ar
LD = arm-arago-linux-gnueabi-ld

CPPUTEST_LIB = $(CPPUTEST_HOME)/lib/libCppUTest_Target.a

CPPUTEST_USE_EXTENSIONS = N
 
CPPUTEST_USE_STD_CPP_LIB = Y
CPPUTEST_USE_MEM_LEAK_DETECTION = Y

CPPUTEST_CPPFLAGS += ${TEST_TGT_CFLAGS} 
		
CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_CFLAGS += -Wextra 

CPPUTEST_LDFLAGS += $(TEST_TGT_LDFLAGS)

LD_LIBRARIES += $(TEST_TGT_LDLIBS) -lrt -lpthread -lm 

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
