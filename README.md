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
		

How to build
------------

   Simply run autobuild.sh on the project root folder.
   ps: Autotools are used, make shure you have it fully installed.


How to use	
----------

The **chelper** install a libchelper.so and its includes on your system.
Link **chelper** with LDFLAGS += -lchelper, and check /usr/local/includes/chelper
for the headers available.

How to run the Tests
--------------------
The tests are automatically built, so you will need to have installed CppUTest,
if using ubuntu run sudo apt-get install CppUTest. Be aware that the build might break
without CppUTest installed. 

To run the tests cd into build/test/ and run ./chelpertest
