# OpenGL-UI-Base

A cross-platform C++ UI framework built on OpenGL and DevIL, featuring interactive UI elements such as buttons, sliders, checkboxes, text boxes, and image rendering.

## Features

- Custom UI elements: Button, Slider, CheckBox, TextBox, Image
- Uses [OpenGL](https://www.opengl.org/) for rendering
- Uses [DevIL](http://openil.sourceforge.net/) for image loading
- Cross-platform (Windows, Linux)
- Example usage and main loop included in [`main.cpp`](main.cpp)

## Build Instructions

### Linux

Run the build script:
```sh
./compile.sh
```

### Windows

Open `OpenGL-UI-Base.sln` in Visual Studio and build.

### Dependencies

- OpenGL (GL, GLUT, GLU)
- DevIL (IL, ILU, ILUT)
- All required DLLs and LIBs are in the `lib/` folder.

## Usage

Run the compiled binary:
```sh
./OpenGL-UI-Base
```
The main window will display interactive UI elements.

## UI Elements & Usage Examples

Below are examples of how to create and use each UI element in [`main.cpp`](main.cpp):

### Button

Creates a clickable button. The callback is called when the button is pressed.

```cpp
pGraphics::pButon buton(
    { 10, 10 },                // Position (x, y)
    { 100, 50 },               // Size (width, height)
    interface.graphics.blue,   // Initial color
    interface.graphics.cyan,   // Active color
    GLUT_BITMAP_TIMES_ROMAN_24,// Font
    interface.graphics.black,  // Text color
    "Button",                  // Text
    [](bool state) {           // OnClick callback
        printf("Buton state: %d\n", state);
    }
);
```

### TextBox

A text input field. The callback is called when Enter is pressed.

```cpp
pGraphics::pTextBox textBox(
    { 130, 10 },               // Position
    { 100, 40 },               // Size
    -1,                        // Max characters (-1 for unlimited)
    GLUT_BITMAP_TIMES_ROMAN_24,// Font
    interface.graphics.black,  // Outline color
    interface.graphics.blue,   // Inside color
    interface.graphics.purple, // Bar color
    interface.graphics.black,  // Text color
    [](std::string text) {     // OnEnter callback
        printf("TextBox text: %s\n", text.c_str());
    }
);
```

### CheckBox

A toggleable checkbox. The callback is called when the state changes.

```cpp
pGraphics::pCheckBox checkBox(
    { 260, 10 },               // Position
    { 30, 30 },                // Size
    GLUT_BITMAP_TIMES_ROMAN_24,// Font
    "Check #1",                // Label
    true,                      // Text orientation (true = right)
    interface.graphics.black,  // Text color
    interface.graphics.blue,   // Outline color
    interface.graphics.purple, // On color
    interface.graphics.yellow, // Off color
    [](bool state) {           // OnStateChange callback
        printf("CheckBox state: %d\n", state);
    }
);
```

### Image

Displays an image at a given position and size.

```cpp
pGraphics::pImage imageALT(
    { 10, 200 },               // Position
    { 100, 100 },              // Size
    "ALT TEXT",                // Alt text
    "images/imagep.png"        // Image path
);

pGraphics::pImage image(
    { 150, 200 },              // Position
    { 100, 100 },              // Size
    "ALT TEXT",                // Alt text
    "images/image.png"         // Image path
);
```

### Slider

A draggable slider for selecting a value. The callback is called when the value changes.

```cpp
pGraphics::pSlider slider(
    { 260, 50 },               // Position
    { 100, 50 },               // Size
    { 0.f, 100.f },            // Min/max values
    2,                         // Precision (decimal places)
    false,                     // Real (true for integer values)
    GLUT_BITMAP_TIMES_ROMAN_24,// Font
    false,                     // Text position (false = left)
    "Slider",                  // Label
    interface.graphics.blue,   // On color
    interface.graphics.yellow, // Off color
    interface.graphics.black,  // Outline color
    interface.graphics.white,  // Value text color
    interface.graphics.red,    // Label text color
    [](double value) {         // OnValueChange callback
        printf("Slider value: %f\n", value);
    }
);
```

## Customization

- UI element colors, positions, callbacks, and fonts are configurable.
- See [`main.cpp`](main.cpp) for full usage and integration.

## License

This project uses third-party libraries (OpenGL, DevIL) under their respective licenses.  

---

**Author:** Țuburlui Mihai  
**Contact:** tuburluimihaita@gmail.com  
**Repository:** [GitHub](https://github.com/MihaiHvH/OpenGL-UI-Base)
