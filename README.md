g4application
=============

A simple generic application for Geant 4. It works as a universal executable
for geant4 tasks. It provides a plugin API which is used to implement
specific behaviour (in one or more plugins in parallel).

Apart from this, g4application offers features that are not tightly connected
to plugin system but can make your life with Geant4 easier.

Main features
-------------
* typical macro-based / interactive workflow
* plugins
* configuration system - central configuration repository based on observer design pattern
* composite user action - these allow adding of more user actions of the same type

Plugin system
-------------
**TODO: describe**

How to build
------------
You will need:
* cmake
* geant4
* boost
* qt4 (probably should be reworked to compile without)

After building, you will obtain:
* g4 executable - this you will run
* libg4App.so shared library - you will need to link your plugins against this library (the aim is to remove this necessity)

Building tested on linux (Fedora Core 18, Scientific Linux 6.4), tests on other platforms are welcome.

History & Motivation
--------------------
2010-2012 I was developing two similar models at a same time and I wanted them to share
a lot of code. In the end, I made the application call the plugin instead of two application
using the same library.

2013: I hope that the application is universal enough to be used in other environments.

Contact
-------
I'd be happy to accept feature requests, cooperation, questions, bug reports...
Please write to jan.pipek AT gmail.com

Links
-----
* https://github.com/janpipek/g4application
* http://janpipek.github.io/g4application/

Other Useful Tools
------------------
scoring_browser - tool for the visualization of scoring files ( https://github.com/janpipek/scoring_browser )
