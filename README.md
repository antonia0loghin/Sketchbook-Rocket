# Sketchbook Rocket

A lightweight, high-performance 2D interactive game built with **C++** and **OpenGL 3.3 (Core Profile)**. Features custom vector asset parsing via **NanoSVG**, GLSL shader dynamic coloring, lerp-based mouse tracking, continuous texture scrolling, and a custom particle engine.

## Used Libraries:
* **Graphics API:** OpenGL 3.3 Core Profile
* **Wrangler \& Context:** GLEW + FreeGLUT
* **Math:** GLM (OpenGL Mathematics)
* **Assets \& Textures:** NanoSVG (SVG vector parsing to VBOs), SOIL (Texture loading + filtering)
* **Shaders:** GLSL 330 core (custom vert/frag shaders for entities \& scrolling bg)

## Game mechanics:
* **Launch**: Rocket rests in initial state on the launchpad until the first `LEFT\\\_CLICK` event triggers the main update/render loop.
* **Game movement**: Rocket lerps toward the mouse cursor coordinates frame-by-frame (`rocketPos += (targetPos - rocketPos) \\\* speed`). Dynamic rotation is derived via $atan2(\\Delta y, \\Delta x) - \\frac{\\pi}{2}$ 
* **Turbo Mode and Particles**: Holding `SPACEBAR` scales scrolling speed and triggers a particle system. Emitter calculates inverse vector direction ($-\\vec{dir}$) with random offset and velocity decay for the exhaust particles.
* **Infinite Scroller Pipeline:** Background texture wrapping ($GL\_REPEAT$) paired with vertical offset uniforms ($bgOffset$) in `bg.vert` creates an infinite scrolling pipeline. Foreground objects (stars, sun, trees) are composite-translated relative to the world variable $bgY$.
* **Runtime Chromatic Switching:** Fast uniform index updates (`codCol`) sent to `example.frag` switch RGB color vectors on the fly using `A` / `D` hotkeys.

## Screenshots:

### Scene 1 (Starting screen):

<img width="821" height="639" alt="image" src="https://github.com/user-attachments/assets/2150a793-271c-4a34-b0c6-7f239f687493" />


###Scene 2 (Rotating Rocket with Turbo Mode):
<img width="811" height="628" alt="image" src="https://github.com/user-attachments/assets/4bd9d137-4a7e-4f03-84fb-4ef5bfa37817" />


## Keybindings

|Input|Action|Technical Overview|
|-|-|-|
|**`Left Click`**|Launch Rocket|Sets `isFlying = true`, unlocks state update in timer loop|
|**`Mouse Motion`**|Vector Direction|Normalizes mouse screen coords to Normalized Device Coordinates (NDC $\[-1, 1]$)|
|**`SPACE` (Hold)**|Turbo Boost|Boosts frame step delta \& instantiates `Particula` structs into buffer vector|
|**`A` / `D`**|Swap Palette|Cycles `indexCuloare` $\[0..6]$ uniform passed directly to GLSL switch block|


## Project Architecture
```text
├── Sketchbook-Rocket/
│   ├── Proiect\\\_racheta.slnx          # Visual Studio Solution
│   └── Proiect\\\_racheta/              # Source root
│       ├── include/                  # GL/GLM/SOIL/NanoSVG headers
│       ├── lib/                      # x32 / x64 compiled libs \\\& DLLs
│       ├── main.cpp                  # Entry point, GLUT setup, callback binding
│       ├── renderer.cpp / .h         # Render loop, VAO/VBO state management, draw calls
│       ├── loaders.cpp / .h          # NanoSVG vector-to-VBO loader \\\& SOIL texture loader
│       ├── input\\\_management.cpp / .h # Mouse/Keyboard input handlers
│       ├── globals.cpp / .h          # Shared state, VBO IDs, math matrices
│       ├── bg.vert / bg.frag         # GLSL shader pair for infinite scrolling background
│       └── example.vert / example.frag # GLSL shader pair for foreground primitives
└── .gitignore                        # Git ignore rules
```


## Quickstart \& Build

1. Open `Proiect\\\_racheta.slnx` in **Visual Studio 2022+**.
2. Select target platform (`x32` or `x64`).
3. Build and run (`F5`). Include and Library paths use `$(ProjectDir)` relative paths—zero local setup required.



