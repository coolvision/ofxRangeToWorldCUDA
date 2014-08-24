ofxRangeToWorld
===================

Transformation of kinect range data into metric 3d space points, using CPU / GPU (CUDA), packaged as openFrameworks addon

Used as a part of a shape reconstruction project: https://github.com/coolvision/KinectShape

Example demo
------------
ofxRangeToWorldCUDA_example visualizes a mesh created from 3d points.
Control keys:
- "n": switch between kinect's color camera and normals map for the mesh texture
- up and down arrow keys: set mesh resolution

Build instructions (for the example app)
----------------------------------------
All underlying libraries and frameworks are cross-platform (Openframeworks, libfreenect, CUDA SDK), so the project is supposed to be cross-platform.
But for now, only makefile for linux is maintained, and it is tested only on Ubuntu 12.04.
Requirements:
- Openframewokls 0071 with dependencies installed
- CUDA 4.1 setup: SDK, toolkit, dev driver; nvcc is supposed to be in $PATH; path to SDK and toolkit should be specified in config.make
- libusb-dev intalled
- addons from ./all_addons directory pasted into OF_ROOT/addons (2do: should properly fork modified addons and add them as submodules)
- OF_ROOT set to Openframeworks path on config.make
- launch as root user, or use instructions on how to run OpenKinect without root privilegies (http://openkinect.org/wiki/Getting_Started#Ubuntu_Manual_Install)
