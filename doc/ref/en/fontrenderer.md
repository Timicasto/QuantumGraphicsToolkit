# Fonts and text
QGT currently contains two classes for rendering text on the screen: `FontRenderer` for "dynamic" rendering (allocates VRAM and free it in the next frame, repeat) and `StaticFontRenderer` for "static" rendering (will directly write data to VRAM).

## FontRenderer class in `FontRenderer.h`

### Public members:
* `GLUint: vao{}, tex{}`:
* `FT_Library: lib`: Freetype library
* `std::vector<std::unordered_map<wchar_t, RenderableCharacter>>: fonts`: A vector for storing fonts
* `Shader: s`: OpenGL shader used

### Construct:
#### via constructor:
`FontRenderer(Shader shader)`

Creates a new FontRenderer with shader `shader` (optional).
### member functions:
`size_t loadFont(const std::string& path, uint32_t mode, int size)`
> loads font file at `path` with size `size`.
>
> `mode` is for specifying the unicode range which will be loaded from the font. e.g.: 1 for ASCII characters, and 2 for CJK characters.

<br>

`void render(size_t font, const std::wstring& text, float x, float y, float scale, glm::vec3 color)`
> Renders text to the screen with font `font` (loaded with loadFont()) and text content `text`, placed in coordinate `(x,y)` with scale `scale` and RGB color tuple `color`.
 
--- 

## StaticFontRenderer class in `StaticFontRenderer.h`

### Public members:
* `GLUint: vao{}, tex{}`:
* `Shader: s`: OpenGL shader used
* `glm::vec3: color`: defines the color of the text in RGB
* `int: length{}`: length of the text stored

### Construct:
#### via constructor:
`StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, Shader sh, float x, float y, float scale, glm::vec3 c)`

Creates a new StaticFontRenderer, which maintains a text string with the desired font, location and style. (shader is optional)

It loads the font in `fontPath` with size `size` and the text content `text`, placed in coordinate `(x,y)` with scale `scale` and RGB color tuple `color` (or `c`).

> !! CAUT !! :: coordinates (x,y) originate from the **bottom left corner** of the canvas. Actually, the canvas could be seen as a 2-D coordinate system in mathematics.

### member functions:
`void render()`
> Renders the content stored in the StaticFontRenderer to the screen.

