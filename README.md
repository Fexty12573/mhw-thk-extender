# mhw-thk-extender
Extender plugin for Monster Hunter World THK files.

# Build
Install [vcpkg](https://github.com/microsoft/vcpkg) and follow the Quick Start Guide.
Then install MinHook, and Json:
```
./vcpkg install minhook:x64-windows-static nlohmann-json:x64-windows-static
```

Finally open the solution in Visual Stuio and hit Build.

The solution contains 3 projects:
- The extender lib (implementation)
- The extender plugin (loaded when the game launches)
- An example on how to use
