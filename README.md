# FastSLAM_in_cpp

## What the hell is this?

This package contains the FastSLAM related C++ code for assignment 7 and 9 of "Robot Mapping" class taught by Dr. Cyrill Stachniss during the Winter term of 2013 at Albert-Ludwigs-Universität Freiburg, Germany. The course website is [here](http://ais.informatik.uni-freiburg.de/teaching/ws13/mapping/). 

The original software are written in MATLAB and come as frameworks for student to fill in the TODO "blanks". Of course, you don't have to do it here, since I'm not an instructor but a mere developer.

## Right! Tell me how to install this piece of software on my computer RIGHT NOW!

Please do sip your coffee and calm down or you need to hold my beer! 

The software runs on *Linux Ubuntu 18.04* hence it still runs on C++11 and Python 2.7.

First, make sure that you have the following modules installed in your computer or Docker container:

### Python end

#### matplotlibcpp

I am using Python 2.7's version of matplotlib, but maybe you can switch to its Python 3's counterpart, but may need to modify the CMakeLists accordingly.

First, check if you have matplotlib installed. Insert in the terminal
```
pip search matplotlib
```

You should find 

```
matplotlib (3.2.2)                  - Python plotting package
  INSTALLED: 2.2.5
  LATEST:    3.2.2
```
Otherwise, you need to issue the following command to install the module using your `pip`
```
sudo pip install matplotlib
```

#### cv2

The module is used to create a video film out of a series of images. You can choose to ignore to installing this module if you don't need to create any film as a souvenir of your final product. 

You can install the module using the command:

```
pip install opencv-python
```

NOTE: If you have installed ROS before, maybe you don't need to manually install the module.

### C++ end

Once you have the package cloned to your local end, `cd` to the root directory of this package, create a `build/` directory like such

```
cd <the_path>/<to_your>/FastSLAM_in_cpp
touch build
```

Then, compile the source codes under `build/` directory:

```
cmake ..
make
```

`cmake ..` for your first building, don't need to issue it afterwards. 
The CMake compiler platform will put the generated binaries (executables) in the `bin/` directory. 


#### Google test

This is the module for running Google test. If you don't want to compile the unit tests files nor have anything to do with these unit test file, just go ahead to `CMakeLists.txt` 

```
cd <the_path>/<to_your>/FastSLAM_in_cpp
vim CMakeLists 
```
Or open tihe file with any of your favorite text editors. In the file, look for

```
# UNIT TESTS
# ~~~~~~~~~~
```
Comment out or delete everything below and including those two lines. Yes! Do it! 

Alternatively, you can choose to install `gtest` module on your local end's environment. I am not an expert here, so I am offering a couple of references to get you started:

- [Getting started with Google Test (GTest) on Ubuntu – Erik Smistad](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)

- [Install gtest in Ubuntu](https://gist.github.com/Cartexius/4c437c084d6e388288201aadf9c8cdd5)

- [c++ - How to set up googleTest as a shared library on Linux - Stack Overflow](https://stackoverflow.com/questions/13513905/how-to-set-up-googletest-as-a-shared-library-on-linux)


## Now, tell me how to turn it on!

So to run the program, make sure that you've already built them first! Once you've everything compiled and sorted out, switch over to `bin/` directory.

```
cd ../bin
```

In it, you can see a bunch of binaries beginning with `test..`, let's ignore them by now, and run the `FastSLAM_node` using the command

```
./FastSLAM_node
```

At this point, the program may complain that it cannot find an `images/` directory. The easiest quick-and-dirty way to bypass the issue is actually creating an `images/` directory for the program to save the images. (My apology! I'll make the image saving an option to be toggle on or off)

```
cd ..
mkdir images
cd bin
```

Let's run the program again. Now you can see an animation window popping out and showing a brief anmation of the particle filter in action.

Voila! You just ran this particle filter program on your computer!

### What? Unit tests? Are they edible?

Yes! Safe and sound. Just kidding, but safe and sound can they be run. The unit tests 

## What if someone wants to contribute to this project, huh?

## Acknowledgement

## Author

If you have any question or suggestion, please contact:

* [Chau-Lin (Charly) Huang](huangc11@rpi.edu) - Rensselaer Polytechnic Institute, class of Fall 2020