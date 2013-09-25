include Makerules.mk

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = $(TARGET)-dev-test
TARGET_LIB = \
	lib/lib_$(COMPONENT_NAME).a

CPPUTEST_OBJS_DIR = obj_dev_test
	
TEST_TARGET = \
	$(COMPONENT_NAME)

#--- Inputs ---#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

CPPUTEST_USE_EXTENSIONS = N
 
CPPUTEST_USE_STD_CPP_LIB = Y
CPPUTEST_USE_MEM_LEAK_DETECTION = Y

CPPUTEST_CPPFLAGS += ${TEST_DEV_CFLAGS} 
		
CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_CFLAGS += -Wextra 

CPPUTEST_LDFLAGS += $(TEST_DEV_LDFLAGS)

LD_LIBRARIES += $(TEST_DEV_LDLIBS) -lrt -lpthread -lm 

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
