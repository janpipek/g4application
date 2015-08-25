g4application
=============

A library and a simple generic application for Geant4. It works as a universal executable
for geant4 tasks. It provides a component and plug-in API to plug in
specific behaviour (in one or more plug-ins in parallel).

Apart from this, g4application offers features that are not tightly connected
to plugin system but can make your life with Geant4 easier.

Main features
-------------
* typical macro-based / interactive workflow
* components
* plugins
* configuration system - central configuration repository based on observer design pattern
* composite geometry
* composite user action - these allow adding of more user actions of the same type
* a few built-in user actions (see below)

Component system
----------------
...

Plug-in system
-------------
Plug-ins of g4application are separate dynamic libraries that are
loaded at runtime. Each plug-in can contain one or more components
that provide physics, particle generator
or geometry and define custom behaviour when various stages of application are
entered.

The plug-in project has to include a class inheriting from `g4::Plugin` and export it using `MAKE_G4_PLUGIN` macro. See examples for details.

Loading a plugin:

    /plugin/open <somePlugin.so>           # Opens the DLL
    /plugin/loadAll somePlugin             # Use all components from the plug in
    /plugin/load somePlugin someComponent  # Use a single component
    /plugin/listComponents somePlugin      # Print all component names from the plugin

There are a few example plug-ins that use most features of G4Application in the
`examples` subdirectory.

- simplePlugin : basic example that defines physics, geometry & generator
- httpPlugin : a simple integrated HTTP server informing about the application state

Built-in components
-------------------
* DefaultWorld - provides a world physical volume
* EventNumberLogging - prints event numbers (with configurable frequency)
* MemoryLogging - prints memory usage before and after the run
* ReferencePhysicsList - provides one of the lists known to `G4PhysListFactory` specified by its name
* GPS - provides GPS (i.e. `G4GeneralParticleSource`) to be configured using its commands

Configuration
-------------
...

How to build
------------
You will need:

* cmake >= 2.6 (not tested for lower)
* geant4 10.0+ ( 10.1 currently used for development, compiled with C++11 turned on)
* boost > 0.49
* C++11-ready compiler
* Qt4 (should work without in the future)

After building, you will obtain:
* g4 executable - this you will run
* libg4Application.so shared library - you will need to link your plugins against this library (the aim is to remove this necessity)

Environment variables (alternatively can be set as CMake variables):

* G4APP_PATH - when you set this, the built libraries and executable will be copied there (optional).
* G4APP_SOURCE_PATH - if you use the provided FindG4Application.cmake (when building your modules),
    this path is used for searching libraries and include directories of g4application (required in plugins).

Building tested on Linux (Fedora Core 18 & 20, Scientific Linux 6.4, Ubuntu 14.04), tests on other platforms are welcome.

History & motivation
--------------------
2010-2012: I was developing two similar models of Leksell Gamma Knife at a same time and I wanted them to share a lot of code.
In the end, I made the application call the plug-ins
instead of two application using the same library.

2013: I hope that the application is universal enough to be used in other environments.

2014: All my simulations for Ph.D. thesis (successfully defended ;-)) were based on g4application.

2015: Complete API redesign, only Geant4 10 is supported (see branch **geant9** for older version).

Known issues
------------
* See GitHub Issues page.

Related projects
----------------
- **g4application-dicom**: voxel geometries built from DICOM data. Implemented as a plug-in. https://github.com/janpipek/g4application-dicom

- **pyg4app**: Python scripts to dynamically generate macro files in a somewhat
structured manner. https://github.com/janpipek/pyg4app

- **g4application-gammaknife**: not yet published model of Leksell Gamma Knife Perfexion.

Contact
-------
I'd be happy to accept feature requests, cooperation, questions, bug reports...
Please write to jan.pipek AT gmail.com
