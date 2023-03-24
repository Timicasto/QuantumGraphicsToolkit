## Window class in "window.h"

### Public members :
* `window: GLFWwindow*` :    a pointer to GLFW window, normally you won't need to use it.
* `scaleMode: ScaleMode`:    scale mode of window: see details at `setScaleMode` function.
* `posMode: PosMode`:        position mode of window(coordinate system): see details at `setPosMode` function.
* `projection: glm::mat4`:   projection matrix of all elements in the window.

### construct:
#### via constructor
`Window(const std::string& title, size_t width, size_t height)`
> This is the simplest constructor. You need to pass the initial title and size expected. The library will create the window automatically based on default context.

<br><br>

`Window(const std::string& title, size_t width, size_t height, int majorVer, int minorVer, int profile, bool fwdCompat)`
> This is the prototype constructor of window. You need to provide complete information about context version besides the arguments required by the simplest constructor.<br> Window initialization will fail should this information be invalid.

<br><br>

#### via factory
> see details at [WindowFactory](./WindowFactory.md)

<br><br>

### other member fuctions

`bool shouldClose() const`
> Returns true after the close button of the window is clicked. This is usually used for determining whether the program should exit the main logic loop, start recycling memory and close.

<br><br>

`void postToScreen() const`
> Swap the front and back buffer of window: you need to do that after GPU rendered a frame every time. The content GPU rendered is saved in back frame buffer. When the function is called, content in back buffer will be moved to front buffer before being displayed.

<br><br>

`void makeCurrent() const`
> Selects the context of window: static operations on all windows and all rendering operations are all applied to windows which called this function. (This is automatically done when windows are created.)

<br><br>

`void setWindowScalable(bool val) const`
> Allowing or disallowing windows to be scaled by user.

<br><br>

`void setVsync(bool val)`
> Enable or disable Vsync<br>
> !! CAUT !! :: When Vsync is closed OpenGL is always trying to render more frames per second, even when it reaches thousands or millions of FPS until the CPUs of users start crying... <br>
> *Stop abusing modern computer hardware! They did nothing wrong! :/*

<br><br>

`void setScaleMode(ScaleMode s)`
> Sets the scale mode of the window.<br>
> SCALE mode: scale all elements to fit screen (overlapping or other incidents that breaks typography never happens! In this mode, the typography is always consistent with your code.)<br>
> EXPAND mode: keep the size of elements. Crop the existing elements or expend space to render new elements. (This is the logic used by Chromium browsers in their windows.)<br>
> !! CAUT !! :: EXPAND mode is not available in *_COORD Position Mode and may lead to `std::runtime_error`.
