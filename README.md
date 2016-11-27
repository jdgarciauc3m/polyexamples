# polyexamples

This repo contains examples of different approaches of polymorphism with a very simple example. The example is writing programs for reading, writing, and performing computations on an scene composed by a number of figures.

## Included solutions

The different directories contain:
* **shape**: A simple solution with an scene as a collection of rectangles.
* **shapegen**: The scene is templated so that a scene may be a collection of rectangles or a collection of circles, but not both.
* **shapeoo**: Classical Object Oriented solution. Rectangles and circles are part of a hierarchy (with shape as base class) and a scene is a collection of pointers to shapes.
* **shapehgen**: Highly inspired by Sean Parent's talk (inheritance is base class of evil). Rectangle and circle are independent classes with no common base. Shape class provides value semantics and a scene contains a collection of shapes.
* **shapehgenopt**: An evolution of previous one with the addition of small object optimization.

## How to compile and run

Each directory contains their corresponding Cmake files.

For each directory:

1. Enter the corresponding directory.
1. Create a new directory named `build`.
1. `cd build`
1. `cmake ..`
1. `make`

Remember that you can `cmake ..`to edit compiler options. In particular do not forget that for performance comparisons is important to set the `Release` build mode.

If you want to run your own performance measurements, you can make use of simple shell scripts under directory `scripts`.

## Contact

If you have any issue with the code, please contact me at josedaniel.garcia@uc3m.es.
