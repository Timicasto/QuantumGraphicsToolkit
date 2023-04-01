## Building Guidelines ~~(disqualified ver.)~~
...well, this documentation should be named "Environment Setup Guidelines"... 'cause this library doesn't require any *building*.
Yes, this is a pure-header library, but OpenGL just doesn't want us to get away with it... as it requires compile-time and runtime dependencies introduced as executables to the project.

### The start
It's actually quite easy to just include this library, as these headers are enough for us to get work done:
`include_directories(...../qgt)`

### And then...
The following dependencies are required:
`glfw-x11` (or `glfw-wayland`) `freetype2 glm mesa`

To include them in your project:
```
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

target_link_libraries(<project> Freetype::Freetype GL glfw)
```

### Something more annoying
Since GLFW's cross-platform is made possible by GLEW/GLAD/..., we would also need a compile-time dependency.
Here we'll be using [GLAD](https://glad.dav1d.de/).
Head over to that website and generate a customized GLAD loader: select gl version > 3.3 under the API section, set `Profile` to `Core` and check `Generate a loader` before clicking on `Generate`.

...with that you'll get an archive with a .c file... Yup, that's right:
```
add_executable(<project> main.cpp.... glad.c)
include_directories(.../KHR .../glad)
```
Just include it in your project and voila! Everything should be up and running now. If you fail to understand, just go ahead and use the `CMakeLists.txt` in this repo.

(btw, make sure that your CMake install has configured support for C++11 and above, and enable optimizations (`-O2` and above, except `-Ofast`) if possible for enhanced performance of STL related calls.
