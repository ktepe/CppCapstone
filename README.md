# CPPND: Capstone REST API Implementation for Sailboat Pricing

## by Kemal Tepe, [ketepe@gmail.com](ketepe@gmail.com)

This is a Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Capstone Project illustrates a REST (Restfull API) using Microsoft's Casablanca libraries. The project is primarily developed for a demonstation of how well the principles learned in the Udacity C++ Nanodegree Program and may not have all the functionalities.


## Dependencies for Running Locally

* cmake >= 3.9
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros

* In addition to above following libraries needs to be installed
* [CPP Rest sdk libraries](https://github.com/microsoft/cpprestsdk), which can be installed with [`sudo apt-get install libcpprest-dev`]

in Linux Ubuntu (20.04) distribution.
* [JSON CPP libraries], which can be installed by using `sudo apt-get install libjsoncpp-dev` in Linux Ubuntu (20.04) distribution.

 
## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run the Server with: `./Server`
5. Run the Client with: `./Client'

## Running and Expected Behavior