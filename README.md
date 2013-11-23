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
* a few built-in user actions (see below)

Built-in user actions
---------------------
You can use a few user actions included in the application.
They are loaded using `/app/addAction <actionname>` command
* NumberingEventAction - prints a short status after each N events
* MemoryRunAction - prints info about memory consumption before/after run

Plugin system
-------------
**TODO: describe**

Loading a plugin
~~~~~~~~~~~~~~~~

    /app/plugin/load <somePlugin.so>

Examples
~~~~~~~~
There are a few example plugins that use most features of G4Application in the
examples/ subdirectory.

- simplePlugin : basic example that defines physics, geometry & generator
- httpPlugin : a simple integrated HTTP server informing about the application state


How to build
------------
You will need:
* cmake >= 2.6 (not tested for lower) 
* geant4 (9.6 used for development)
* boost > 0.49

Optional:
* qt4

After building, you will obtain:
* g4 executable - this you will run
* libg4Application.so shared library - you will need to link your plugins against this library (the aim is to remove this necessity)

Environment variables (alternatively can be set as CMake variables):
* G4APP_PATH - when you set this, the built libraries and executable will be copied there (optional). 
* G4APP_SOURCE_PATH - if you use the provided FindG4Application.cmake (when building your modules),
    this path is used for searching libraries and include directories of g4application (required in plugins).

Building tested on Linux (Fedora Core 18, Scientific Linux 6.4), tests on other platforms are welcome.

History & Motivation
--------------------
2010-2012: I was developing two similar models of Leksell Gamma Knife at a same time and I wanted them to share
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
scoring_browser - tool for the visualization of scoring files ( http://janpipek.github.io/scoring_browser/ )
