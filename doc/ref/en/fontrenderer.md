## StaticFontRenderer class in `StaticFontRenderer.h`

### Public members:
* `GLUint: vao{}, tex{}`:
* `Shader: s`: OpenGL shader used
* `glm::vec3: color`: defines the color of the text in RGB
* `int: length{}`: length of the text stored

### Construct:
#### via constructor:
`StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, float x, float y, float scale, glm::vec3 color)`

<br><br>

`StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, Shader sh, float x, float y, float scale, glm::vec3 c)`

Creates a new StaticFontRenderer, which maintains a text string with the desired font, location and style.

It loads the font in `fontPath` with size `size` and the text content `text`, placed in coordinate `(x,y)` with scale `scale` and RGB color tuple `color` (or `c`).

> !! CAUT !! :: coordinates (x,y) originate from the **bottom left corner** of the canvas. Actually, the canvas could be seen as a 2-D coordinate system in mathematics.

### member functions:
`void render()`
> Renders the content stored in the StaticFontRenderer to the screen.

