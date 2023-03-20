## Window class in "window.h"

### Public members :
* `window: GLFWwindow*` :    a pointer to  GLFW window, you won't need to use it usually.
* `scaleMode: ScaleMode`:    scale mode of window: see details at `setScaleMode` function.
* `posMode: PosMode`:        position mode of window(coordinate system): see details at `setPosMode` function.
* `projection: glm::mat4`:   projection matrix of all elements in the window.

### construct:
#### via constructor
`Window(const std::string& title, size_t width, size_t height)`
> This is the simplest constructor. You need to pass the initial title and size expected. The library will create the window automatically based on default context.

<br><br>

`Window(const std::string& title, size_t width, size_t height, int majorVer, int minorVer, int profile, bool fwdCompat)`
> This is the prototype constructor of window. You need to provide complete information about context version besides the arguments required by the simplest constructor.<br>unfortunately, if this information is not valid, initialization of window fails.

<br><br>

#### via factory
> see details at [WindowFactory](./WindowFactory.md)

<br><br>

### other member fuctions

`bool shouldClose() const`
> After the close button of the window being clicked, it returns ture. This is usually used for deciding when the program exits main logic loop, starts recycling memory and close.

<br><br>

`void postToScreen() const`
> exchange the front and back cache of window: you need to do that after GPU rendered a frame every time. The content GPU rendered is saved in back cache. When the function is called, content in back cache is moved to front cache, then the content is displayed.

<br><br>

`void makeCurrent() const`
> select context of window: static operations on all windows and all render operations are all applied to windows called this function. (this is automatically done when windows are created)

<br><br>

`void setWindowScalable(bool val) const`
> allow or forbidden windows being scaled by user.

<br><br>

`void setVsync(bool val)`
> open or close Vsync<br>
> !! CAUT !! :: when Vsync is closed OpenGL is always trying to render more frame per second, no matter it reaches thousands or millions FPS, until it reached the limit of computer, while the CPUs of users are crying...<br>
> Stop bully modern computer hardware, they shouldn't be punished. :P

<br><br>

`void setScaleMode(ScaleMode s)`
> set the Scale Mode of window.<br>
> SCALE mode: scale all elements to fit screen (overlapping or other incidents that breaks typography never happens! In this mode, the typography is always consistent with your code!)<br>
> EXPAND mode: keep the elements size. Crop the existing elements or expend space to render new elements. (windows of chrome browser follows this logic)<br>
> !! CAUT !! :: EXPAND mode is not accessible in *_COORD Position Mode. Because it may lead to `std::runtime_error`.