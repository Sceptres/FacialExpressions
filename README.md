# Facial Expressions
## Description
This project loads a set of 35 face meshes (Wavefront OBJ files), 34 face meshes and 1 base mesh and blends them together to create new faces. In more detail, the `.weights` files under `src/resources/meshes/weights` represent every way to blend the meshes, meaning there is a total of 12 different blend faces. It is built in C++ using the OpenGL API along with the following libraries:
1. GLFW3
2. GLAD
3. GLM
4. TinyObjLoader

The app contains the following keyboard controls:
1. Press `p` on your keyboard to capture the screen into a ppm image
2. Press `b` to render the world in debug mode (Render all geometry as lines)
3. Press `esc` to close the window
4. Press the `up arrow key` to increase the blend id and see a new blend face mesh
5. Press the `down arrow key` to decrease the blend id and see previously rendered blend face mesh

## Setup
To setup the project, you need to setup the GLFW3, GLAD, GLM, and TinyObjLoader libraries. Follow the steps in the following link to setup GLFW3, GLAD, and other system specific dependencies, https://learnopengl.com/Getting-started/Creating-a-window. Furthermore, the `glad.c` file must be placed in the `src/` folder. You can use the official glm github page to install and setup the library https://github.com/g-truc/glm. For the TinyObjLoader library, you can visit the github repo here to see its setup https://github.com/tinyobjloader/tinyobjloader.

After setting up all the libraries, open `Makefile` and add your include and lib paths.
```Make
INCDIR = # Include dir that contains glfw3, glad, and GLM header files
LIBDIR = # Lib dir that contains glfw3, glad, and GLM library files
```

## How to run
To run this project, execute the `run.sh` shell script. This will build and start the application. You can also build the application yourself by running `make` command in the root directory of the project.
``` sh
make
```
After building the project, the executable will be found in the `src/` folder. For the executable to propery run the application, you must run the executable from within the `src/` folder.
```sh
cd src/
./FacialExpressions
```
