# RTv1


RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program. It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.

![alt text](https://github.com/NikoGardziella/RTv1/blob/main/Screen%20Shot%202022-10-26%20at%2010.28.57.png?raw=true)

## Installation

Clone or download this repository and run make in command line while in the root of the repository. This will build executable called RTv1. Makefile compiles SDL2 library from source files so building process might take some time.

## Usage

./RTv1 scene/[filename]
filename must contain path to a valid scene.
If the scene is not valid, RTv1 will write corresponding error on standard output.

## Ray tracing
When it comes to render 3 dimensions computer generated images there is 2 possible
approaches: “rasterization”, which is used by almost all graphic engines because of it’s
efficiency and “ray tracing.” The ray tracing method is more expensive and as a result
not adapted to real time but it produces a high degree of visual realism.

![alt text](https://github.com/NikoGardziella/RTv1/blob/main/Screen%20Shot%202022-10-26%20at%2010.10.01.png?raw=true)
