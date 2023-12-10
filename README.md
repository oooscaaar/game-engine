<h1 align="center">
  OxEngine - 3D Game Engine written in C++
</h1>

Developed for the [Master's Degree in Advanced Programming for AAA Video Games](https://www.talent.upc.edu/ing/estudis/formacio/curs/201200/advanced-programming-aaa-video-games/)</br>
The game engine is under development. It features:
- Loading geometry
- Inspecting geometry
- Tweaking some engine and geometry attributes
- Scaling models

## How to use the engine
Run the engine executable file. It will load automatically the model of a house.
### Load Models
Drag the model.gLTF file to the engine window
### Camera controls
W -> Move FRONT</br>
A -> Move LEFT</br>
S -> Move RIGHT</br>
D -> Move BACK</br>
Q -> Move UP</br>
E -> Move DOWN</br>

F -> Focus the camera around the geometry</br>
Mouse Wheel -> ZoomIn / ZoomOut</br>
Right Click (Hold) -> Add free look (Can be combined with movement)</br>
SHIFT (Hold) -> Duplicates movement speed</br>
Alt + Left click Orbit the object</br>

### Extra features
- Adjust texture filtering mode (MAG/MIN filters)

## Libraries used (Until today)
- [SDL 2](https://www.libsdl.org/download-2.0.php)
- [Glew](https://github.com/nigels-com/glew)
- [MatGeoLib](https://github.com/juj/MathGeoLib)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [TinyGLTF](https://github.com/syoyo/tinygltf)

## License
[MIT](./LICENSE)

## Repository
[OxEngine Github Repository](https://github.com/oooscaaar/game-engine/)
