# opengl-lab-env
C++11 and OpenGL based application base for developing apps.

# Requirements
1. Visual Studio 2017 or newer (Windows) or CMake 3+ (Linux, MacOS).
2. Compiler with support for lambda functions (C++11), such as VS 2017.
  
# Visual Studio Users
1. Open `vstudio\lab-env.sln`
2. Work either in the example app project, or create a new project with the same settings as example app.

GLM math library is included by default in the example app project.

# CMake Users
1. Configure and Generate project by using either a CMake GUI tool, or by executing `cmake -S {PATH_TO_SOURCE_ROOT} -B {PATH_TO_BUILD_FOLDER}`. Select Generator based on your preferences. Add `-DCMAKE_BUILD_TYPE=Debug` if you intend to debug your application.
    * Make sure you generate everything by calling cmake from the root directory of the repository (`opengl-lab-env/`).
2. Build project by using the generated project files (`make` from the build folder if you are using Unix Makefiles (default unless otherwise specified))
3. Executables will be placed in the `bin` folder

# Usage
The lab environment contains two classes, Window and App. Override the App class for your project to implement your own update loop. The Window class is used to open a window and connect input handlers to it. 

This is done by assigning a lambda function to a callback matching the input you require. It is possible to have more than one window open at a time, although one must select which window to render to using the function called Window::MakeCurrent prior to doing any GL calls.

## Common problems
* Q: Build log says Windows SDK version was not found
    - A: Right click the project in the solution explorer and click `Retarget projects`, then select a version.
* Q: Running CMake on Linux says some libraries are missing
    - A: Try installing them with `sudo apt-get install libgl1-mesa-dev mesa-common-dev xorg-dev libglu1-mesa-dev` or equivalent for your distribution.


---
---

# CMake instructions
Put your laboration in the folder titled 'projects'. It must be accompanied with its own CMakeLists.txt which is used to generate a project/solution. Then run CMake in the root of the project, there should be a target in your project matching the name of your lab.