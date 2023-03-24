## Quantum Graphics Toolkit 
Quantum Graphics Toolkit (or "QGT" for short) is a graphics library based on OpenGL. It is extremely flexible and versatile, aiming to make OpenGL GUIs easier to create.

You can always create a high performance GUI app with it or even construct a 2D game for a little more code.

**Do note that this project is in a very early stage of development, and only a limited subset of functionalities present in typical GUI frameworks are currently implemented.**

### Quickstart / Try it out
Install these libraries first: `glfw-x11` (or `glfw-wayland` if on Wayland), `freetype2`, `glm`, `mesa`. 

Then, clone this repository, `cd` into it and build `main.cpp` with your favorite build system (here we use `ninja`):
```bash
mkdir build
cd build
cmake -G Ninja ../
ninja
./QuantumGraphicsToolkit
```

### Resources
[For zh_CN README](./README_zh.md)<br>

[API Reference Manual (EN)](./doc/ref/en/intro.md)<br>
[API Reference Manual (ZH)](./doc/ref/zh/intro.md)
<br>

[Building instructions (EN)](./doc/ins/en/building.md)<br>
[Building instructions (ZH)](./doc/ins/zh/building.md)
<br>

[Example code (EN)](./doc/ex/en/intro.md)<br>
[Example code (ZH)](./doc/ex/zh/intro.md)
<br>

## Contributing

Contact [Telegram](t.me/Timicasto) or mailing to timicasto@gmail.com for more information.<br>
Will generally reply messages (in ~30 min) from 9:00PM to 5:00AM the next day (GMT +08:00)

## License
Affero GNU Public License version 3
