The latest version of [Dobby](https://github.com/jmpews/Dobby.git) is impossiable to compile.
To build Dobby, please run `git checkout 0932d69c320e786672361ab53825ba8f4245e9d3`
For more details, please see https://github.com/jmpews/Dobby/issues/257.

These pre-compiled objects use CMake options:
```cmake
option(DOBBY_GENERATE_SHARED "Build shared library" OFF)
option(DOBBY_DEBUG "Enable debug logging" OFF)
option(NearBranch "Enable near branch trampoline" ON)
option(FullFloatingPointRegisterPack "Save and pack all floating-point registers" OFF)
option(Plugin.SymbolResolver "Enable symbol resolver" ON)
option(Plugin.ImportTableReplace "Enable import table replace " ON)
option(Plugin.Android.BionicLinkerUtil "Enable android bionic linker util" ON)
option(DOBBY_BUILD_EXAMPLE "Build example" OFF)
option(DOBBY_BUILD_TEST "Build test" OFF)
add_subdirectory(dobby) # Compile Dobby
```