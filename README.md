chelper
=======

What is it
----------

**chelper** is a extension to the stdc library. It offers generic and reusable modules based 
on the need of C programmers considering embedded applications. Most of the modules are
self contained, when dependencies exists the dependent module will be guard protected
by macros.

	Available Modules:
		Vector 
		Ring FIFO
		Fast Ring FIFO
		String 
		Signal Slot with no argument
		Signal Slot with two int arguments 
		Number
		Timeout (posix dependent)
		Log
	
	Unrecomended use Modules (Will be removed):
		Fatal - It is useless
		
		

How to run unit tests
---------------------

1) Decompress CppUTest.zip on repository root folder and make:

	/chelper$ unzip CppUTest.zip
	/chelper$ cd CppUTest
	/chelper/CppUTest$ make
	/chelper/CppUTest$ cd ..
	
2) Build the test target of chelper

	/chelper$ make dev_test
	
3) Now chelper will build and the tests will run automatically at the end of the build process.	


How to use	
----------

The **chelper** creates a static library that must be manually added to your build system aside
the headers files.

1) Build the static library:
	
	/chelper$ make dev_lib

2) Include the **include** folder in your compiler command (*CFLAGS += -I$(CHELPER_PATH)/include*)

3) Link the file **libchelper-dev.a** when building your application (*LDFLAGS += -L$(CHELPER_PATH)/lib -lchelper-dev*)
