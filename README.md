<!-- [![header][header-url]][header-link] -->

# Noether

> Noether is a C++ and OpenGL based Renderer, Physics Engine, and Game Framework.

I've decided to take another shot at engine programming now that I have a slightly firmer grasp on some of the fundamentals, and more confidence in my ability to structure larger projects. The goal of this project is for me to take various pieces of games engines that I have developed in my spare time and bring them together into something resembling a complete work. Initially the goal will be to get a simple renderer up and running, alongside an ECS implementation that will act as the bedrock for me to expand upon.

I have chosen to roll my own maths library here, as opposed to running with something like glm. I'm picky about naming conventions and operator overloading, and I need a way to flex my maths brain again, so that's something I will be developing alongside this project. I will also be looking to use this framework as a basis to develop my own first attempt at a physics engine. Again, I'm not expecting to turn around and create something like Jolt, but I firmly believe that opening up the black box and getting your hands dirty is the best way to develop an intuition for these kinds of things. 

## Features

* Rendering
  * Model loading form .obj wavefront files.
  * Shader loading from file.
  * Material system.
  * Directional and point lighting using the Phong reflection model.
  * MSAA.
  * Skyboxes.
* General
  * Event & polling based input abstractions.
  * Variable frame-rate game loop with high-precision timing.
  * ImGUI drawing capability, easily accessible from client code.

## Installation

As of right now, this project only builds on MacOSX. To get started just clone the repo and run premake5 gmake on the root directory.

## Built With

* [GLFW](https://www.glfw.org/) - Desktop Platform Independant Windowing
* [DearIMGUI](https://github.com/ocornut/imgui) - Immediate-Mode GUI
