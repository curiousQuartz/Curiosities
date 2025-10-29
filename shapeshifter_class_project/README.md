# ShapeShifter — Class project

Small shapeshifter game based on an old flash game created for a school project in 2019.

## Summary

This folder contains the working version of an OpenGL/GLUT student project (ShapeShifter game prototype).
Files included: `main.cpp`, `GamePlay.cpp` / `GamePlay.h`, `ShapeShifter.cpp` / `ShapeShifter.h`, `Door.cpp` / `Door.h`, `SpecialTiles.cpp` / `SpecialTiles.h`, and a `Makefile`.

The program renders a simple gameplay scene using legacy OpenGL and GLUT/freeglut. It uses immediate-mode OpenGL calls (glBegin/glVertex/glColor, matrix stack functions, etc.) and GLUT callbacks for input and the main loop.

## Prerequisites

- A C++ compiler with C++17 support (clang++ or g++ on macOS/Linux, MSVC or MinGW on Windows).
- OpenGL and a GLUT implementation (system GLUT on macOS, freeglut on Linux/Windows). On macOS the system OpenGL/GLUT frameworks are used by default.
- `make` (optional but recommended — a Makefile is included).

## Quick build & run

Please note I have only tested this on macOS using the makefile but have included the windows and linux instructions found as well.

### On macOS (recommended approach)

The included Makefile contains logic to link macOS frameworks. Build and run:

```bash
make clean
make
./shapeshifter
```

If you prefer a single clang++ command:

```bash
clang++ -std=c++17 -Wall -pedantic -DGL_SILENCE_DEPRECATION *.cpp -framework OpenGL -framework GLUT -o shapeshifter
./shapeshifter
```

Notes for macOS:
- The code uses legacy OpenGL which Apple has deprecated. The Makefile and the example command define `GL_SILENCE_DEPRECATION` to suppress deprecation warnings.
- If you installed FreeGLUT via Homebrew and prefer to use it, adjust the build to use `pkg-config --cflags --libs freeglut` or add Homebrew include/library paths (`/opt/homebrew` or `/usr/local`).

### On Linux (Debian/Ubuntu example)

Install dependencies, then build:

```bash
sudo apt update
sudo apt install build-essential libglu1-mesa-dev freeglut3-dev mesa-common-dev pkg-config
make clean
make
./shapeshifter
```

Or compile directly with pkg-config:

```bash
g++ -std=c++17 -Wall -pedantic *.cpp -o F19_V375_P1_LindzonAdira $(pkg-config --cflags --libs freeglut) -lGL -lGLU
./shapeshifter
```

### On Windows

Two common workflows:

1) MSYS2 / MinGW-w64

Install MSYS2 and the mingw-w64 toolchain and freeglut packages; in a MinGW-w64 shell:

```bash
# (run in MSYS2 MinGW64 shell)
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-freeglut mingw-w64-x86_64-pkg-config
g++ -std=c++17 -Wall *.cpp -o shapeshifter -lfreeglut -lglu32 -lopengl32
./shapeshifter.exe
```

2) Microsoft Visual Studio

- Create a new Win32/Console or Empty project and add the .cpp/.h files.
- Link against `opengl32.lib` and a GLUT/freeglut library (or use vcpkg to install freeglut and integrate it).
- Set language standard to C++17.

## Makefile behavior

- The included `Makefile` in this folder attempts to detect Darwin (macOS) and link frameworks (`-framework OpenGL -framework GLUT`) there, and falls back to `-lGL -lGLU -lglut` on other Unix-like OSes.
- If your environment differs (e.g., you want to use Homebrew freeglut), either edit the Makefile or compile with the explicit commands shown above.

## Troubleshooting

- "ld: library 'GL' not found" on macOS: use the framework link approach (see macOS instructions above) or edit the Makefile to use macOS frameworks.
- Missing header `GL/glut.h` or `GL/freeglut.h`: install the development package for freeglut (Linux) or ensure your include paths point to Homebrew install location (macOS: `/opt/homebrew/include` or `/usr/local/include`).
- Deprecation warnings on macOS: they are safe for this homework code; add `-DGL_SILENCE_DEPRECATION` to CXXFLAGS to silence them (the Makefile already does this).
- If the Makefile reports "missing separator": open the Makefile and ensure each recipe command line starts with a literal tab character (not spaces).

## Files in this folder

- `GamePlay.*` — main gameplay logic and program entry points
- `ShapeShifter.*` — player/shape rendering and logic
- `Door.*` — door rendering / interactions
- `SpecialTiles.*` — special tile types and rendering
- `Makefile` — build helper (contains macOS detection)
