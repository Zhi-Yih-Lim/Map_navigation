# Shortest-path finding simulation in a map with topographical features

## Motivation

This is a self-paced project aimed at familiarizing  myself with programming in C++ in an object-oriented fashion. Addtionally, I wanted an avenue to experiment with shortest-path finding algorithms in a sandbox enviroment of my own creation, to better understand how graph data structures are used in path-finding.

## Dependencies

This simulation uses the OpenCV library (4.5.5_2) to display the grid with topographical features and a player/vehicle/person within it. The `cmath` library is also used to calculate square-roots and exponents. The remaining dependencies ( i.e. stack, vector, queue, ... ) used in the simulation are part of the C++ standard library. The version of C++ used is C++11 and the compiler version is GCC 4.2.1.

## Running the code
With the dependencies in place, ensure that all `.h` and `.cpp` are in the same directory. In the terminal, ( Was using the terminal on a late 2013 MacBookPro ) enter the command : 
```
g++ $(pkg-config --cflags --libs */opencv4.pc) -std=c++11 main.cpp Cell.cpp Player.cpp Maze.cpp Vertex.cpp Edge.cpp -o mainProg

```
where `*` is the path on the local machine to the `opencv4.pc` file. The path was :
```
/usr/local/Cellar/opencv/4.5.5_2/lib/pkgconfig
```
on my laptop.  
Then, a `mainProg` executable file will be generated on the current working directory. In the terminal again, enter the following command :
```
./mainProg
```
to have the grid and player displayed, followed by the actuation of any key to have the shortest path from the player to the peak of the grid generated. Hit any key again to terminate the simulation.

## Results

### Before
![](/ResultImages/Before.png)

### After
![](/ResultImages/After.png)

## Resources
- [Basic drawings](https://docs.opencv.org/4.x/d7/da8/tutorial_table_of_content_imgproc.html) with OpenCV.
- [Pixel coloring](https://docs.opencv.org/3.4/d5/d98/tutorial_mat_operations.html) under the `Basic operations with images` section.
- Basic formatting of `.md` file from [gitHub](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax#uploading-assets).
- Mark-down [basic syntax](https://www.markdownguide.org/basic-syntax/#blockquotes-1).
