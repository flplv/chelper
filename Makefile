# Read the file below for comments
include Makerules.mk

printversions:
	@echo LibVersion: ${FIRWMARE_VERSION}
	@echo BuildTag: ${BUILDTAG}
	@echo

dev_test:
	make -f MakeDevTest.mk all
		
dev_lib:
	make -f MakeDevLib.mk all

all: printversions dev_lib dev_test
	
clean:
	make -f MakeDevLib.mk clean
	make -f MakeDevTest.mk clean
	@rm lib -rf
