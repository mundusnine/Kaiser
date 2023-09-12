# Kaiser
We never rest on our laurels

C based game engine. Tool and framework agnostic by design. Will integrate code and data hot-reload using engine-link.

## Tools:
Will use GLTF as intermediary format, where possible. The lower in the list a tool is, the lower in priority for the project it is. Open up issues for interest in a specific tool.

### 2D:
- [ ] [LDTK](https://ldtk.io/) (INPROGRESS)
- [ ] [Tiled](https://www.mapeditor.org/)
### 3D:
- [ ] [Total Editor 3](https://github.com/TheTophatDemon/Total-Editor-3)(using either gltf or the custom scene format)
- [ ] Godot editor using the GLTF exporter
- [ ] Source2 tools(using [ValveResourceFormat decompiler](https://valveresourceformat.github.io/))
- [ ] Trenchbroom(using either .obj export or [libmap](https://github.com/QodotPlugin/libmap))
- [ ] [Elit3D](https://github.com/christt105/Elit3D)

## Frameworks:
- [X] Uses raylib
- [ ] Use Kinc while retaining sane components from raylib. For audio should use Soloud.
- Users can add any framework by implementing a service provider
