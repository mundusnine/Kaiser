# Editor:
- Do [this](https://nitter.net/MikeDiskett/status/1705420794980184412)
- Have a way to share low level commands between Editor and Runtime.
- Use [Im3D](https://github.com/john-chapman/im3d) for gizmos
- Use [JSON schema](https://json-schema.org/) to allow users to automate the generation of importers with [quicktype](https://github.com/glideapps/quicktype/) or [online](https://app.quicktype.io/)
- Like USD, have a way to report [atomic changes](https://jsonapi.org/ext/atomic/)

# Engine:

- [ ] For Kinc provider integrate  [Soloud](https://github.com/jarikomppa/soloud)
- [ ] Create raylib provider
- [ ] Investigate using [SlimRaster](https://github.com/HardCoreCodin/SlimRaster)
    - [ ] Implemente a way to debug shaders in with SlimRaster and a way to have shaders be available in glsl i.e. fake_glsl.h
- [ ] Create kinc provider
    - [ ] Add 3D capabilities
    - [ ] Use krink for 2d
Investigate hot-reloading the generated code as a dll using [cr](https://github.com/fungos/cr)
    - For more background info have a look [here](https://fungos.github.io/cr-simple-c-hot-reload/)