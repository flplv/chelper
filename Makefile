# Read the file below for comments
include Makerules.mk

export PATH := $(TGT_GCC_PATH):$(PATH)

printversions:
	@echo FWVersion: ${FIRWMARE_VERSION}
	@echo BuildTag: ${BUILDTAG}
	@echo

dev_test:
	make -f MakeDevTest.mk all
	
dev_test_lib:
	make -f MakeDevTest.mk all_no_tests
	
dev_lib:
	make -f MakeDevLib.mk all
	
tgt_lib:
	make -f MakeTgtLib.mk all
	
tgt_test:
	make -f MakeTgtTest.mk all_no_tests
	
all: printversions dev_lib

clean:
	make -f MakeDevLib.mk clean
	make -f MakeTgtLib.mk clean
	@rm lib -rf
	make -f MakeTgtTest.mk clean
	make -f MakeDevTest.mk clean
