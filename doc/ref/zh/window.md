## Window.h 中的 Window 类

### 公共成员:
* `window: GLFWwindow*` :    一个指向GLFW窗口的指针，一般的时候你都不会用到它
* `scaleMode: ScaleMode`:    窗口的缩放模式 (详见 setScaleMode 函数)
* `posMode: PosMode`:        窗口的位置定义模式(窗口的座标系) : 详见 setPosMode 函数
* `projection: glm::mat4`:   窗口中所有元素的投影矩阵 一般的时候你并不需要自己修改它

### 构造:
#### 通过构造器
`Window(const std::string& title, size_t width, size_t height)`
> 这是一个窗口最简单的构造器 你需要传入窗口被创建时期望的窗口标题和窗口大小 库将会自动按默认上下文创建窗口

<br><br>

`Window(const std::string& title, size_t width, size_t height, int majorVer, int minorVer, int profile, bool fwdCompat)`
> 这是一个窗口的原型构造器 除了最简单的构造器需要的内容外你还需要提供完整的上下文版本信息... <br>不幸的是如果这些信息不匹配 窗口创建将失败

<br><br>

#### 通过工厂
> 详见 [WindowFactory](./WindowFactory.md)

<br><br>
## 其他成员函数

`bool shouldClose() const`
> 当窗口的 'X' 被点击过(用户请求关闭窗口)后  它开始返回true 这一般用于决定程序在何时退出主逻辑循环，开始回收内存并关闭

<br><br>

`void postToScreen() const`
> 交换窗口的前后缓冲区: 你需要在GPU渲染出每一帧后都这样做 GPU渲染出来的内容会在后缓冲区 这个函数被调用时 后缓冲区转移到前缓冲区 渲染的内容被显示

<br><br>

`void makeCurrent() const`
> 选定窗口上下文: 所有对窗口的全局静态操作 和所有的渲染操作 全部生效于最后makeCurrent()过的窗口 (窗口被创建时自动makeCurrent)

<br><br>

`void setWindowScalable(bool val) const`
> 允许或禁止窗口被用户用鼠标拖动缩放 (true 为允许)

<br><br>

`void setVsync(bool val)`
> 启用或关闭垂直同步
> !! CAUT !! :: 当垂直同步被关闭时 OpenGL总是会试图每秒渲染更多帧 不管现在已经到达了几千FPS还是几万FPS 它都会不停地试图渲染 直到达到计算机的瓶颈性能 然而这个时候用户的CPU往往已经在悲鸣了... <br>
> 停止欺负现代计算机硬件 它们不该被惩罚

<br><br>

`void setScaleMode(ScaleMode s)`
> 设置窗口的缩放模式：即窗口被缩放时会发生什么<br>
> SCALE模式：缩放所有渲染出的全部内容到适合屏幕 (绝对不会出现重叠等破坏排版的事情! 缩放模式下它的排版永远是你的代码希望的样子!)<br>
> EXPAND模式：保留现有元素的尺寸 裁剪现有元素或开辟新空间可用于渲染其他元素 (Chrome浏览器的窗口被缩放时就是这样的逻辑)<br>
> !! CAUT !! :: EXPAND模式在坐标模式为*_COORD下时不可用 这可能导致`std::runtime_error`