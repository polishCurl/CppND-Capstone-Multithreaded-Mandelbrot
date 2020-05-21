# C++ Nanodegree: Mandelbrot set viewer
This project is the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Mandelbrot set viewer allows interactive visualization of the [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set). Main computation is done asynchronously to the event loop and is split between a number of parallel threads.

Once the program is launched. The vizualization can be controlled using the following keys (no need to use <kbd>Shift</kbd>):
| _Key_         | _Action_          |
|---------------|-------------------|
|<kbd>Esc</kbd> | Quit              |
|<kbd>←</kbd>   | Move left         |  
|<kbd>↑</kbd>   | Move up           |
|<kbd>→</kbd>   | Move right        |
|<kbd>↓</kbd>   | Move down         |
|<kbd>+</kbd>   | Zoom in           | 
|<kbd>-</kbd>   | Zoom out          |
|<kbd>></kbd>   | Increase accuracy |
|<kbd><</kbd>   | Decrease accuracy |
|<kbd>r</kbd>   | Reset view        |

You can also use <kbd>Mouse</kbd> to move around.

A number of statistics are displayed on the title bar. They are updated every second.

<img src="mandelbrot.gif"/>


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`.

## Top-level directory layout
```bash
.
├── src                           # source files.
├── cmake                   
|   └── FindSDL2_image.cmake      # finds SDL2 library image
├── CMakeLists.txt                # build config
├── mandelbrot.gif                # program demo         
└── README.md
```

## Class Structure
```bash
src      
├── barrier.cpp             # cyclic thread barrier
├── barrier.h           
├── controller.cpp          # user control
├── controller.h        
├── main.cpp 
├── mandelbrot_viewer.cpp   # top-level class, interactive viewer
├── mandelbrot_viewer.h
├── mandelbrot.cpp          # mandelbrot computation logic
├── mandelbrot.h 
├── point.cpp               # sample point
├── point.h  
├── renderer.cpp            # renders mandelbrot set     
└── renderer.h
```



## Rubric points met

### Loops, Functions, I/O

| Point                                                                                          | Proof           | 
|------------------------------------------------------------------------------------------------|-----------------|
| The project demonstrates an understanding of C++ functions and control structures.             | all             |
| The project reads data from a file and process the data, or the program writes data to a file. | -               |
| The project accepts user input and processes the input.                                        | -               |

### Object Oriented Programming

| Point                                                                            | Proof                              | 
|----------------------------------------------------------------------------------|------------------------------------|
| The project uses Object Oriented Programming techniques.                         | all                                |
| Classes use appropriate access specifiers for class members.                     | all                                |
| Class constructors utilize member initialization lists.                          | mandelbrot.cpp, renderer.cpp       |
| Classes abstract implementation details from their interfaces.                   | barrier.cpp, mandelbrot_viewer.cpp |
| Classes encapsulate behavior.                                                    | mandelbrot.cpp                     |
| Classes follow an appropriate inheritance hierarchy.                             | -                                  |
| Overloaded functions allow the same function to operate on different parameters. | -                                  |
| Derived class functions override virtual base class functions.                   | -                                  |
| Templates generalize functions in the project.                                   | -                                  |

### Memory Management

| Point                                                                                     | Proof                 | 
|-------------------------------------------------------------------------------------------|-----------------------|
| The project makes use of references in function declarations.                             | controller.cpp        |
| The project uses destructors appropriately.                                               | mandelbrot.cpp        |   
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | mandelbrot_viewer.cpp |
| The project follows the Rule of 5.                                                        | all                   |
| The project uses move semantics to move data, instead of copying it, where possible.      | -                     |
| The project uses smart pointers instead of raw pointers.                                  | mandelbrot.h          |

### Concurrency

| Point                                        | Proof           |
|----------------------------------------------|-----------------|
| The project uses multithreading.             | mandelbrot.cpp  |
| A promise and future is used in the project. | -               |
| A mutex or lock is used in the project.      | barrier.cpp     |
| A condition variable is used in the project. | barrier.cpp     |  