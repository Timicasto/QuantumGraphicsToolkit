## 构建指南 ~~(不合格版)~~

其实比起叫构建指南这篇文档更应该被叫做「环境搭建指南」... 因为这个离谱的库是不需要构建的！<br>
如我们所见... 这是一个纯头文件库 它不需要构建 但是OpenGL似乎不太愿意让我们好好地喝掉这碗粥...<br>
是的 它需要编译时和运行时依赖 而且还是直接引进项目可执行的！...
<br>

## 一切的开端
好吧那么只是引用这个库其实非常简单... 一个目录的头文件就足以我们做任何事情了<br>
` include_directories(...../qgt) `<br>

## 至于其他的事情嘛...
（语气突然正式<br>
依赖系统软件包：`glfw-x11 | glfw-wayland & freetype2 & glm & mesa`
然后我们还要在项目中引入这些软件包...

```cmake
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

target_link_libraries(<project> Freetype::Freetype GL glfw)
```
### 还有一点更恼人的
因为GLFW是用GLEW/GLAD等实现了跨平台... 所以我们还会多出一个编译时依赖<br>
此项目使用的是[GLAD](https://glad.dav1d.de)<br>
打开上面超链接中的在线服务 语言设置为C/C++ 在API选项中选择3.3以上的 `gl` 版本 然后将 `Profile` 设置为 `Core` 并保证下方的 `Generate a Loader` 被勾选<br>
然后你得到了一个压缩包 并惊奇地发现里面居然有一个.c文件<br><br>

恐怕你的设想没有错 其实就是...
```cmake
add_executable(<project> main.cpp.... glad.c)
include_directories(.../KHR .../glad)
``` 
<br>
把它们全部塞进项目里..

<br><br>
然后一切就应该可以顺利地运行了！如果你还是没能理解一切的话... 这个repo的根目录里面也就有一份为你们准备的示例CMakeLists 改一改拿去用就好啦...
<br>
oh顺带一提 记得保证自己的CMake配置了C++ 11以上的标准版本 并尽可能开启 -O2或以上 -Ofast以下的优化 可以更好地保证STL部分调用的性能
