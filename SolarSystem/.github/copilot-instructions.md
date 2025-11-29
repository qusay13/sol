# Copilot / AI Agent Instructions for SolarSystem

This file provides concise, actionable guidance for AI coding agents working on this codebase.

1) Project overview
- Purpose: a GLUT/OpenGL-based 3D Solar System simulation (C++). Entry point: `main.cpp`.
- Composition: `MainApp` composes managers (AudioManager, GameStateManager, WindowManager), `Camera`, `StarField`, `SolarSystem`, `Renderer`, and `InputHandler`.

2) Key files to read first
- `main.cpp` — program init + GLUT window creation.
- `include/MainApp.h` / `src/MainApp.cpp` — application lifecycle, GLUT callback registration, and component composition.
- `include/Renderer.h` / `src/Renderer.cpp` — OpenGL init, render loop, HUD and camera positioning logic.
- `include/SolarSystem.h` / `src/SolarSystem.cpp` — scene state, planets creation, update/draw.
- `include/Planet.h` / `src/Planet.cpp` — planet geometry, rings and moons (important for visuals).
- `include/InputHandler.h` / `src/InputHandler.cpp` — keyboard/mouse handling and menu hit-testing.

3) Big-picture architecture notes (why things are structured this way)
- `MainApp` is the composition root: it instantiates subsystems and registers static GLUT callbacks. The static `instance` pointer is used to forward callbacks to object methods.
- Rendering uses a single `Renderer` object which receives pointers to `StarField`, `SolarSystem`, and `Camera`. State is stored in those objects; `Renderer` reads state but does not own it.
- `SolarSystem` holds raw pointers to `Planet` objects and is responsible for their lifecycle. Memory ownership is manual (new/delete), and destructors free in reverse order.

4) Build, run, and clean (developer workflows)
- Dependencies: `g++`, OpenGL, GLUT (freeglut), `libsdl2-dev`, `libsdl2-mixer-dev`.
- Install example (Ubuntu/Debian):
  ```bash
  sudo apt-get install g++ freeglut3-dev libsdl2-dev libsdl2-mixer-dev
  ```
- Build: `make` (from project root). Produces `solar_system` executable.
- Run: `./solar_system` or `make run`.
- Clean: `make clean`.

5) Project-specific patterns and conventions
- Include style: headers are under `include/`; source files include them with `#include "../include/XYZ.h"` from `src/`.
- Object files: `Makefile` places compiled objects under `obj/src/*.o` using the pattern `$(OBJ_DIR)/%.o: %.cpp`.
- GLUT callbacks: registered as static methods on `MainApp` and forwarded to `instance` — modify or add callbacks by updating `MainApp::setupCallbacks()` and corresponding static wrappers.
- Camera focus semantics:
  - `focusedPlanet == -1` → focus on Sun
  - `focusedPlanet >= 0` → focus on that planet (index matches `SolarSystem::getPlanet(index)`)
  - `focusedPlanet == -2` → overview/free mode
- Menu and HUD coordinates are hard-coded for a window size of `800x600` (see `Renderer::renderHUD()` and `main.cpp` window init). If you change the default window size, update HUD/menu layout values.
- Mouse wheel: scroll events use GLUT button codes `3` and `4` (see `InputHandler::handleMouse`).

6) Common pitfalls & debugging tips
- GUI program — run in a desktop session (not headless). Use `gdb ./solar_system` for native debugging; set breakpoints in `MainApp`, `Renderer`, `SolarSystem`.
- Memory ownership is manual: watch for leaks when changing constructors/destructors. `MainApp` deletes members in its destructor in reverse creation order.
- If adding new source files, ensure they are in `src/` and `Makefile`'s wildcard `$(SRC_DIR)/*.cpp` will pick them up automatically; object path rule expects `.cpp` at repo root or `src/`.
- Be careful modifying rendering state machine (glEnable/glDisable) — `Renderer::initGL()` and `renderHUD()` toggle lighting/blending and must restore GL state consistently.

7) Suggested first tasks for contributors / agents
- Small fixes: adjust HUD text or menu positions in `src/Renderer.cpp` and `src/InputHandler.cpp` (menu hit boxes).
- Add CLI flags: if needed, modify `main.cpp` to parse `argv` before calling `glutInit` and pass flags to `MainApp`.
- Replace manual memory with smart pointers selectively (start with `MainApp` ownership) — but keep changes minimal and preserve deletion order.

8) Where to look for examples in this repo
- Camera math & focus logic: `src/Renderer.cpp` (method `getCameraPosition`).
- Planet data and rendering complexity: `src/SolarSystem.cpp` (planet initialization) and `src/Planet.cpp`.
- Input/menu hit testing: `src/InputHandler.cpp` (methods `handlePassiveMotion`, `handleMenuMouse`).

If any of these areas need more detail or you want a different focus (tests, CI, refactor plan), tell me which part to expand or update.
