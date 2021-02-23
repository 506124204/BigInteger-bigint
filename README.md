# BigInteger-bigint

form: 
# https://mattmccutchen.net/bigint/
# https://mattmccutchen.net/bigint/bigint-2010.04.30.zip
# https://mattmccutchen.net/bigint/bigint-2010.04.30.tar.bz2

#############

Matt McCutchen's Web Site → C++ Big Integer Library  (Top, History, Current issues, Resources, Bugs and enhancements, Legal, Bottom).  Email me about this page.
C++ Big Integer Library
Status: unmaintained; 2002-2010 (supersedes any conflicting remarks left on this page; see the home page for definitions)

This library has been unmaintained since 2010, and I recommend that people migrate to alternatives; nevertheless, many people still seem to be using it.  I'm no longer very interested in putting in the amount of maintenance work that a library like this deserves, but I'm open to doing some maintenance if you contact me and give me a good reason why you continue to use this library rather than the alternatives.  Alternatively, if someone else is maintaining a fork of this library, please let me know and I will link to it.  As of 2014-10-18, I have lost the mailing list configuration and subscriber database due to a server failure and am taking the opportunity to shut the list down unless and until there is a need for a mailing list again; the public archive remains available for now.

You can use this library in a C++ program to do arithmetic on integers of size limited only by your computer's memory.  The library provides BigUnsigned and BigInteger classes that represent nonnegative integers and signed integers, respectively.  Most of the C++ arithmetic operators are overloaded for these classes, so big-integer calculations are as easy as:

    #include "BigIntegerLibrary.hh"
    
    BigInteger a = 65536;
    cout << (a * a * a * a * a * a * a * a);
    
    (prints 340282366920938463463374607431768211456)
The code in sample.cc demonstrates the most important features of the library. To get started quickly, read the code and explanations in that file and run it. If you want more detail or a feature not shown in sample.cc, consult the actual header and source files, which are thoroughly commented.

This library emphasizes ease of use and clarity of implementation over speed; some users will prefer GMP, which is faster.  The code is intended to be reasonably portable across computers and modern C++ compilers; in particular, it uses whatever word size the computer provides (32-bit, 64-bit, or otherwise).

History[# Top]
This library originated from a barebones big-integer library I wrote in 2002 as part of a poorly conceived school science fair project in which I tested the performance of several cryptographic algorithms, including RSA.  Hence it is no accident that the library contains almost everything needed to implement RSA, though I knew nothing about side-channel attacks and never made an attempt to prevent them.  In 2004, I decided to clean up the library and make it public.  I'm thrilled that it has gotten so much use since then: for many users, the ease of integration into existing build systems and liberal license seemed to outweigh the terrible performance.  In fact, when I built LineageOS from source in 2017 to get the fix for BlueBorne before the fix made it into a binary release, I was astonished to see that the library had been bundled to implement a tiny feature of one of the applications.

Current issues[# Top]
Dennis Yew pointed out serious problems with ambiguities and unwanted conversions when mixing BigInteger/BigUnsigned and primitive integers.  These should all be fixed in version 2008.07.20 at the cost of breaking compatibility with existing code that uses the library.
Since version 2008.07.20, the library contains a test suite that runs under Valgrind.  If you run into this Valgrind bug like I did, you can run the testsuite without Valgrind by passing the environment variable NO_VALGRIND=1.
Resources[# Top]
Here is the library's source repository (using git version control).

Released versions of the library (please see the ChangeLog for the differences between versions):

File	Size	Modification time
bigint-2010.04.30.tar.bz2	27673	2010-04-30 21:37:03 +0000
bigint-2010.04.30.zip	39997	2010-04-30 21:37:03 +0000
bigint-2009.05.03.tar.bz2	27529	2009-05-03 20:55:26 +0000
bigint-2009.05.03.zip	39857	2009-05-03 20:55:26 +0000
New on 2008-01-30, changed on 2008-03-20!  I announce releases of the library on its Mailman list, bigint@mattmccutchen.net.  You can ask questions, report bugs, and otherwise discuss the library on this list.  Here is the list info page.  I would be delighted to hear from you if you like this library and/or find a good use for it.

NOTE: It is generally useless to ask me how to set up the library in your IDE because you know more about the IDE than I do (unless it's the Eclipse CDT).

Bugs and enhancements[# Top]
The library has been tested by me and others but is by no means bug-free.  If you find a bug, please report it, whether it comes in the form of compiling trouble, a mathematically inaccurate result, or a memory-management blooper (since I use Java, these are altogether too common in my C++).  I generally fix all reported bugs.  You are also welcome to request enhancements, but I am unlikely to do substantial amounts of work on enhancements at this point.

Legal[# Top]
I, Matt McCutchen, the sole author of the original Big Integer Library, waive my copyright to it, placing it in the public domain.  The library comes with absolutely no warranty.

Matt McCutchen's Web Site → C++ Big Integer Library  (Top, History, Current issues, Resources, Bugs and enhancements, Legal, Bottom).  Email me about this page.
Modification time of this page's main source file: 2020-09-23 15:12:24 +0000
Except where otherwise noted, Matt McCutchen waives his copyright to the content of this site.  This site comes with absolutely no warranty.  Why?
