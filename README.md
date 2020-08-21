# IRTG Soft Tissue Robotics: Introduction to Dynamics Animation and Robotics Toolbox (DART)

This tutorial is dedicated to the International Research Training Group (IRTG) SoftTissueRobotics. The focus of this tutorial is to give an introduction in the multibody-physics simulation framework [DART](https://dartsim.github.io/).
But before we go ahead and create our own physical worlds, we need to install some components.

These are
* Windows Subsystem for Linux (WSL)
* A Windows X Server
* DART
* Some knowledge about how to build and execute C++ programs in the WSL

Please note, this Readme assumes you have a Windows computer.
If you have a Linux system you are probably already knowing what you are doing.

## WSL installation
We need the windows subsystem for linux to run DART.
You can find install instructions [here](https://docs.microsoft.com/de-de/windows/wsl/install-win10).

## X SERVER installation
To visualize the physics engine we need an windows X Server in order to forward the display output from the WSL to Windows.
Download and install (via your Windows system) a windows X-server.
You can find the VcXsrv Windows X Server wich we recommend to use [here](https://sourceforge.net/projects/vcxsrv/).

## DART Installation instructions
Find the DART install instructions [here](https://dartsim.github.io/install_dart_on_ubuntu.html).
You can try to install DART with apt

```bash
sudo apt-add-repository ppa:dartsim/ppa
sudo apt update
sudo apt install libdart6-all-dev
```

In case this does not work (happend to me already) make sure you have a clean system

```sh
sudo apt remove libdart*
```

Then follow the instructions to install [DART from source](https://dartsim.github.io/install_dart_on_ubuntu.html#install-dart-from-source).
Just to be sure, install all optional dependencies.


## DART Tutorial

This tutorial is derived from the DART tutorials and examples that come with the installation of DART which you can find under:
[dart/tutorials](https://github.com/dartsim/dart/blob/master/tutorials) and [dart/examples](https://github.com/dartsim/dart/blob/master/examples).

Note DART's copyright notice:

Copyright (c) 2011-2016, Humanoid Lab, Georgia Tech Research Corporation
Copyright (c) 2016-2017, Personal Robotics Lab, Carnegie Mellon University
Copyright (c) 2011-2019, Graphics Lab, Georgia Tech Research Corporation
Copyright (c) 2017-2019, Personal Robotics Lab, University of Washington
Copyright (c) 2017-2019, Open Source Robotics Foundation
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


### Build Your Tutorial

Make sure you are in the tutorial's subdirectory.

```sh
cd your/workspace/directory/hello_dart
```

Then create a build directory and build the executable.

```sh
mkdir build
cd build
cmake ..
make
```

### Execute Instructions

Forward your Display output from the WSL to Windows.
First start the X Server on your windows system.
Then in the WSL console type:

```sh
export DISPLAY=:0
```

Launch the executable from the build directory:

```sh
cd helloDART/build
./hello_DART
```

Follow the instructions detailed in the console.

### Tutorial instructions

In this tutorial you will learn to

*   create a simple world in DART (`hello_dart`)
*   create a body in this world (`hello_dart`)
*   import more complex robot structures in the physics engine (`hello_panda`)
*   simulate collisions between bodies (`hello_collisions`)

For each of the tutorials you find a separate subdirectory with the instructions for the tutorial as a `tutorial.md` file.
